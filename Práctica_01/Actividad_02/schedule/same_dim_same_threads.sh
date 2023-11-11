#!/bin/bash

num_programs=3
program_names=("MatMul_omp_Mul_Inf_static.cpp" "MatMul_omp_Mul_Inf_dynamic.cpp" "MatMul_omp_Mul_Inf_guided.cpp")

# Nombre del archivo donde se guardarán los resultados
output_file="results_threads.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING ---"

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    g++ -std=c++11 -fopenmp ${program_names[i]}
    for ((j = 1; j <= 8; j++))
    do
        export OMP_NUM_THREADS=$j
        echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
        output=$(./a.out 1100 1 $j)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        echo "Duration: $duration"
        echo $duration >> $output_file
    done    
done

echo "Resultados guardados en $output_file"
