#include <thread>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define RAND rand() % 100
#define NUM_THREADS 2

// Function definition
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);
void Escribir_Matriz (float *M, int dim);
void Multiplicar_Matrices (float *A, float *B, float *C, int dim, int row_start, int row_end);


int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 1100;
    int num_threads = 2;
    float *A, *B, *C;

    if (argc == 4)
	{
		dim = atoi (argv[1]);
		block_size = atoi (argv[2]);
        num_threads = atoi (argv[3]);
	}

    A = (float *) malloc (dim * dim * sizeof(float));
    B = (float *) malloc (dim * dim * sizeof(float));
    C = (float *) malloc (dim * dim * sizeof(float));

    Init_Mat_Sup (dim, A);
    Init_Mat_Inf (dim, B);
    //std::cout << "Matriz A\n";
    //Escribir_Matriz(A, dim);
    //std::cout << "Matriz B\n";
    //Escribir_Matriz(B, dim);

    int row_start[num_threads];
    int row_end[num_threads];

    int rows_per_thread = dim / num_threads;
    //printf("Assigned rows per thread: %d\n", rows_per_thread);
    for (int i = 0; i < num_threads; i++)
    {
        //printf("Thread %d\n", i);
        row_start[i] = i * rows_per_thread;
        row_end[i] = (i + 1) * rows_per_thread;
        if (i == (num_threads - 1)) // last thread
        {
            row_end[i] = dim; // last row
        }
        //printf("Start is %d and end %d\n", row_start[i], row_end[i]);
    }

    std::thread threads[num_threads];
    clock_t start = clock();
    for (auto i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(Multiplicar_Matrices, A, B, C, dim, row_start[i], row_end[i]);
    }
    for (auto i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }
    clock_t end = clock() - start;
    double duration = (double) end / (double) CLOCKS_PER_SEC;
    //Escribir_Matriz(C, dim);

    printf("[Duration] %f\n", duration);

    free(A);
    free(B);
    free(C);
}


void Init_Mat_Sup (int dim, float *M)
{
    int i, j, m, n, k;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++) {
			if (j <= i)
				M[i*dim+j] = 0.0;
			else
//				M[i*dim+j] = j+1;
				M[i*dim+j] = RAND;
		}
    }
}

void Init_Mat_Inf (int dim, float *M)
{
    int i,j,m,n,k;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (j >= i)
				M[i*dim+j] = 0.0;
			else
//				M[i*dim+j] = j+1;
				M[i*dim+j] = RAND;
		}
	}
}

void Escribir_Matriz (float *M, int dim)
{
	int i, j;

	for (i=0; i < dim; i++)
	{
		for (j=0; j < dim; j++)
			fprintf (stdout, "%.1f ", M[i*dim+j]);
		fprintf (stdout,"\n");
	}

   printf ("\n");
}

void Multiplicar_Matrices (float *A, float *B, float *C, int dim, int row_start, int row_end)
{
	int i, j, k;

	for (i = row_start; i < row_end ; i++)
		for (j = 0; j < dim; j++)
			C[i * dim + j] = 0.0;

	for (i = row_start; i < row_end; i++)
		for (j = 0; j < dim; j++)
			for (k = 0; k < dim; k++)
				C[i * dim + j] += A[i * dim + k] * B[j + k * dim];
} 