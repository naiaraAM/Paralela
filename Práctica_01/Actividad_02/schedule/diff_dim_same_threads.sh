#!/bin/bash

num_programs=3
program_names=("MatMul_omp_Mul_Inf_static.cpp" "MatMul_omp_Mul_Inf_dynamic.cpp" "MatMul_omp_Mul_Inf_guided.cpp")
matrix_size=200

# Nombre del archivo donde se guardarán los resultados
output_file="results_dim.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING ---"

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    matrix_size=200  # Reset matrix_size before each program run
    export OMP_NUM_THREADS=2
    g++ -std=c++11 -fopenmp ${program_names[i]}
    while [ $matrix_size -le 1500 ]  # Use the correct comparison operators
    do
        output=$(./a.out $matrix_size 1 2)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        echo "Duration: $duration"
        # Guarda el resultado en el archivo de salida
        echo $duration >> $output_file
        matrix_size=$((matrix_size + 50))  # Increment matrix_size
    done
done

echo "Resultados guardados en $output_file"
