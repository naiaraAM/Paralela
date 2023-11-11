#!/bin/bash

num_programs=4
program_names=("MatMul_threads_Mul.cpp" "MatMul_threads_Mul_Inf.cpp" "MatMul_omp_Mul.cpp" "MatMul_omp_Mul_Inf.cpp")

# Nombre del archivo donde se guardarán los resultados
output_file="resultados_2.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING ---"

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    matrix_size=200  # Reset matrix_size before each program run
    case $i in 
        0 | 1)
            g++ -std=c++11 -pthread ${program_names[i]}
            for ((j = 1; j <= 8; j++))
            do
                output=$(./a.out 1100 1 $j)
                duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
                echo "Duration: $duration"
                echo $duration >> $output_file
            done
        ;;
        2 | 3)
            g++ -std=c++11 -fopenmp ${program_names[i]}
            for ((j = 1; j <= 8; j++))
            do
                export OMP_NUM_THREADS=$j
                output=$(./a.out 1100 1)
                duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
                echo "Duration: $duration"
                echo $duration >> $output_file
            done
        ;;
    esac
done

echo "Resultados guardados en $output_file"
