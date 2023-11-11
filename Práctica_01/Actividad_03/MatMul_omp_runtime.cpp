#include <thread>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <float.h>
#include <omp.h>

#define RAND rand() % 100
#define NUM_THREADS 2

// Function definition
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);
void Escribir_Matriz (float *M, int dim);
void Multiplicar_Matrices (float *A, float *B, float *C, int dim);
float Calcula_Maximo (float *M, int dim);


int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 5;
    float *A, *B, *C;

	if (argc == 3)
	{
		dim = atoi (argv[1]);
		block_size = atoi (argv[2]);
	}

    A = (float *) malloc (dim * dim * sizeof(float));
    B = (float *) malloc (dim * dim * sizeof(float));
    C = (float *) malloc (dim * dim * sizeof(float));

    Init_Mat_Sup (dim, A);
    Init_Mat_Inf (dim, B);

    Multiplicar_Matrices(A, B, C, dim);
    clock_t start = clock();

	float max = Calcula_Maximo(C, dim);

    clock_t end = clock() - start;
	double duration = ((double) end) / CLOCKS_PER_SEC;

	printf("[Max] %f\n", max);
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
				M[i * dim + j] = 0.0;
			else
				M[i * dim + j] = RAND;
		}
    }
}

void Init_Mat_Inf (int dim, float *M)
{
    int i,j,m,n,k;

	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (j >= i)
				M[i * dim + j] = 0.0;
			else
				M[i * dim + j] = RAND;
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

void Multiplicar_Matrices (float *A, float *B, float *C, int dim)
{
	int i, j, k;

    #pragma omp parallel private (i, j, k) shared (A, B, C, dim)
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

float Calcula_Maximo(float *M, int dim)
{
	float max = FLT_MIN;
	omp_lock_t lock;
	omp_init_lock(&lock);
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < dim * dim; i++)
		{
			omp_set_lock(&lock);
			{
				if (M[i] > max)
				{
					max = M[i];
				}
			}
			omp_unset_lock(&lock);
		}
	}
	omp_destroy_lock(&lock);
	return max;
}