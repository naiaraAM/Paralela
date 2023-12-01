#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define NUM_THREADS 8

void fgauss (int *, int *, int, int);

int main(int argc, char *argv[]) {

   double start = omp_get_wtime();
   FILE *input_file;
   FILE *out;
   int i, j, size, seq = 80;
   int **pixels, **filtered;

   if (argc == 2) seq = atoi (argv[1]);

   input_file = fopen("movie.in", "rb");
   if (input_file == NULL) {
      perror("movie.in");
      exit(EXIT_FAILURE);
   }

   out = fopen("movie_omp_v2.out", "wb");
   if (out == NULL) {
      perror("movie.out");
      exit(EXIT_FAILURE);
   }

   int width, height;

   fread(&width, sizeof(width), 1, input_file); // leer del archivo
   fread(&height, sizeof(height), 1, input_file); // leer del archivo

   fwrite(&width, sizeof(width), 1, out); // escribir en archivo
   fwrite(&height, sizeof(height), 1, out); // escribir en archivo


   pixels = (int **) malloc (seq * sizeof (int *)); // reservar espacio
   filtered = (int **) malloc (seq * sizeof (int *)); // reservar espacio

   for (i = 0; i < seq; i++)
   {
      pixels[i] = (int *) malloc((height+2) * (width+2) * sizeof(int)); // guardar puntero, se puede paralelizar
      filtered[i] = (int *) malloc((height+2) * (width+2) * sizeof(int)); // guardar puntero, se puede paralelizar
   }

   #pragma omp parallel shared(pixels, input_file, height, width) private(size) num_threads(NUM_THREADS)
   {
      #pragma omp single
      {
         i = 0;
         do
         {
            #pragma omp task depend(out: pixels[i], i) firstprivate(i)
            {
               size = fread(pixels[i], (height + 2) * (width + 2) * sizeof(int), 1, input_file);
               printf("size: %d\n", i);
               #pragma omp task depend(in : pixels[i], i) depend(out: filtered[i])
               {
                  fgauss (pixels[i], filtered[i], height, width);
                  printf("pixels: %d\n", i);
               }
            }
            i++;
         } while (!feof(input_file) && i < seq);
      }
   }

   for (int i = 0; i < seq; i++) // loop para guardar los datos filtrados en orden
   {
      fwrite(filtered[i], (height+2) * (width + 2) * sizeof(int), 1, out);
      printf("filtered: %d\n", i);
   }

   for (i = 0; i < seq; i++) 
   {
      free (pixels[i]);
      free (filtered[i]);
   }
   free(pixels); // liberar memoria
   free(filtered); // liberar memoria

   fseek(out, 0, SEEK_END);
   printf("SIZE OF OUTPUT FILE: %ld\n", ftell(out));

   fclose(out);
   fclose(input_file);
   double end = omp_get_wtime();
   printf("TIME v2: %f\n", end-start);

   return EXIT_SUCCESS;
}

void fgauss (int *pixels, int *filtered, int heigh, int width)
{
	int y, x, dx, dy;
	int filter[5][5] = {1, 4, 6, 4, 1, 4, 16, 26, 16, 4, 6, 26, 41, 26, 6, 4, 16, 26, 16, 4, 1, 4, 6, 4, 1};
	int sum;

	for (x = 0; x < heigh+2; x++) {
		for (y = 0; y < width+2; y++)
		{		
			sum = 0;
			for (dx = 0; dx < 5; dx++)
				for (dy = 0; dy < 5; dy++)
					if (((x+dx-2) >= 0) && ((x+dx-2) < width) && ((y+dy-2) >=0) && ((y+dy-2) < heigh))
						sum += pixels[(x+dx-2)*width+(y+dy-2)] * filter[dx][dy];
			filtered[x*width+y] = (int) sum/273;
		}
	}
}