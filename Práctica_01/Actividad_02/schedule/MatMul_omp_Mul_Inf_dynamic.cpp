#include <thread>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <omp.h>

#define RAND rand() % 100

// Function definition
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);
void Escribir_Matriz (float *M, int dim);
void Multiplicar_Matrices_Inf(float *A, float *B, float *C, int dim, int block_size);

int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 1300;
    float *A, *B, *C;

	if (argc == 4) // beacuse of script, code reutilization
	{
		dim = atoi (argv[1]);
		block_size = atoi (argv[2]);
	}

    A = (float *) malloc (dim * dim * sizeof(float));
    B = (float *) malloc (dim * dim * sizeof(float));
    C = (float *) malloc (dim * dim * sizeof(float));

    Init_Mat_Inf (dim, A);
    Init_Mat_Sup (dim, B);

    double start = omp_get_wtime();

    Multiplicar_Matrices_Inf(A, B, C, dim, block_size);

    double end = omp_get_wtime();

	printf("[Duration] %lf seconds\n", end - start);

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

void Multiplicar_Matrices_Inf (float *A, float *B, float *C, int dim, int block_size)
{
	int i, j, k;

	int max_threads = omp_get_max_threads();
	printf("Max threads: %d\n", max_threads);

    #pragma omp parallel private (i, j, k) shared (A, B, C, dim, block_size) num_threads(max_threads)
	{
		#pragma omp for collapse(2) schedule(dynamic, block_size)
		for (i=0; i < dim; i++)
			for (j=0; j < dim; j++)
				C[i*dim+j] = 0.0;

		#pragma omp for collapse(2) schedule(dynamic, block_size) // necessary to be collapse(2)
		for (i=1; i < dim; i++)
			for (j=1; j < dim; j++)
				for (k=0; k < i; k++)
					C[i*dim+j] += A[i*dim+k] * B[j+k*dim];
	}	
}