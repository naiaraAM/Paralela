#include <thread>
#include <stdlib.h>
#include <iostream>
#include <chrono>

#define RAND rand() % 100

// Function definition
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);
void Escribir_Matriz (float *M, int dim);
void Multiplicar_Matrices (float *A, float *B, float *C, int dim, int num_threads);


int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 1300;
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

    auto start = std::chrono::high_resolution_clock::now();

    Multiplicar_Matrices(A, B, C, dim, num_threads);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "[Duration] " << duration.count() << " seconds" << std::endl;

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

void Multiplicar_Matrices (float *A, float *B, float *C, int dim, int num_threads)
{
	int i, j, k;

    #pragma omp parallel private (i, j, k) shared (A, B, C, dim) num_threads(num_threads)
	{
		// part without data
		#pragma omp for
		for (i=0; i < dim; i++)
			for (j=0; j < dim; j++)
				C[i*dim+j] = 0.0;

		// part with data
		#pragma omp for
		for (i=0; i < dim; i++)
			for (j=0; j < dim; j++)
				for (k=0; k < dim; k++)
					C[i*dim+j] += A[i*dim+k] * B[j+k*dim];
	}
} 