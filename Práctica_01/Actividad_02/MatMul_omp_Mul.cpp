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
void Multiplicar_Matrices (float *A, float *B, float *C, int dim);


int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 200;
    float *A, *B, *C;

	if (argc == 3 or argc == 4)
	{
		dim = atoi (argv[1]);
		block_size = atoi (argv[2]);
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

    clock_t start = clock();

    Multiplicar_Matrices(A, B, C, dim);

    clock_t end = clock() - start;
	double duration = ((double) end) / CLOCKS_PER_SEC;
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