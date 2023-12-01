#include <thread>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <float.h>
#include <mutex>
#include <chrono>

#define RAND rand() % 100
#define NUM_THREADS 2

// Function definition
void Init_Mat_Sup (int dim, float *M);
void Init_Mat_Inf (int dim, float *M);
void Escribir_Matriz (float *M, int dim);
void Multiplicar_Matrices (float *A, float *B, float *C, int dim, int row_start, int row_end);
void Calcula_Maximo(float *M, int row_start, int row_end);

std::mutex max_mutex;
float max = FLT_MIN;

int main (int argc, char ** argv)
{

    int block_size = 1;
    int dim = 1500;
    int num_threads = 8;
    float *A, *B, *C;

    if (argc == 3)
	{
		dim = atoi (argv[1]);
		//block_size = atoi (argv[2]);
        num_threads = atoi (argv[2]);
	}

    A = (float *) malloc (dim * dim * sizeof(float));
    B = (float *) malloc (dim * dim * sizeof(float));
    C = (float *) malloc (dim * dim * sizeof(float));

    // Initialize matrix
    Init_Mat_Sup (dim, A);
    Init_Mat_Inf (dim, B);

    int row_start[num_threads];
    int row_end[num_threads];
    int rows_per_thread = dim / num_threads;
    
    for (int i = 0; i < num_threads; i++)
    {
        row_start[i] = i * rows_per_thread;
        row_end[i] = (i + 1) * rows_per_thread;
        if (i == (num_threads - 1)) // last thread
        {
            row_end[i] = dim; // last row
        }
    }

    std::thread threads[num_threads]; // create threads
    
    for (auto i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(Multiplicar_Matrices, A, B, C, dim, row_start[i], row_end[i]);
    }
     for (auto &thread : threads)
    {
        thread.join();
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(Calcula_Maximo, C, row_start[i], row_end[i]);
    }
     for (auto &thread : threads)
    {
        thread.join();
    }
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

void Calcula_Maximo(float *M, int row_start, int row_end)
{
    for (int i = row_start; i < row_end; i++)
    {
        max_mutex.lock();
        if (M[i] > max)
        {
            max = M[i];
        }
        max_mutex.unlock();
    }
}