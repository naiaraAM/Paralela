/************************************************************/
/* Nombre:                                                  */
/* Práctica:                                                */
/* Fecha:                                                   */
/************************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <float.h>

#define RAND rand() % 100

/************************************************************/
void Init_Mat_Sup(int dim, float *M);
void Init_Mat_Inf(int dim, float *M);
void Multiplicar_Matrices(float *A, float *B, float *C, int dim);
void Multiplicar_Matrices_Inf(float *A, float *B, float *C, int dim);
void Escribir_Matriz(float *M, int dim);
float Calcula_Maximo(float *M, int dim);
/************************************************************/

int main (int argc, char ** argv)
{
	int block_size = 1, dim=5;
	float *A, *B, *C;

/* Lectura de parámetros de entrada */
/* Usage: ./MatMul [dim] [block_size]*/
	if (argc == 3)
	{
		dim = atoi (argv[1]);
		block_size = atoi (argv[2]);
	}

	A = (float *) malloc (dim * dim * sizeof (float));
	B = (float *) malloc (dim * dim * sizeof (float));
	C = (float *) malloc (dim * dim * sizeof (float));

	Init_Mat_Inf (dim, A);
	Init_Mat_Inf (dim, B);

	Multiplicar_Matrices_Inf (A, B, C, dim);
	Escribir_Matriz (C, dim);

 	free(A);
	free(B);
	free(C);

  	exit (0);
}

void Init_Mat_Sup (int dim, float *M)
{
	int i,j,m,n,k;

	for (i = 0; i < dim; i++) {
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

void Multiplicar_Matrices (float *A, float *B, float *C, int dim)
{
	int i, j, k;

	// part without data
	for (i=0; i < dim; i++)
		for (j=0; j < dim; j++)
			C[i*dim+j] = 0.0;

	// part with data
	for (i=0; i < dim; i++)
		for (j=0; j < dim; j++)
			for (k=0; k < dim; k++)
				C[i*dim+j] += A[i*dim+k] * B[j+k*dim];
} 

void Multiplicar_Matrices_Sup (float *A, float *B, float *C, int dim)
{
	int i, j, k;

	for (i=0; i < dim; i++)
		for (j=0; j < dim; j++)
			C[i*dim+j] = 0.0;

	for (i=0; i < (dim-1); i++)
		for (j=0; j < (dim-1); j++)
			for (k=(i+1); k < dim; k++)
				C[i*dim+j] += A[i*dim+k] * B[j+k*dim];
} 

void Multiplicar_Matrices_Inf (float *A, float *B, float *C, int dim)
{
	int i, j, k;

	for (i=0; i < dim; i++)
		for (j=0; j < dim; j++)
			C[i*dim+j] = 0.0;

	for (i=1; i < dim; i++)
		for (j=1; j < dim; j++)
			for (k=0; k < i; k++)
				C[i*dim+j] += A[i*dim+k] * B[j+k*dim];
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

float Calcula_Maximo(float *M, int dim)
{
  float max=FLT_MIN;
  for(int i=0;i<dim*dim;i++)
  {
    if(M[i]>max)
    {
      max=M[i];
    }
  }
  return max;
}
