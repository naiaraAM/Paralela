#!/bin/bash

program_name=("MatMul_omp_Mul_Inf_dynamic.cpp")

# Nombre del archivo donde se guardarán los resultados
output_file="results_block.txt"

# Borra el archivo si ya existe
rm -f $output_file

    echo "--- Executing ${program_name} ---"
    g++ -std=c++11 -fopenmp ${program_name}
    export OMP_NUM_THREADS=4
    for ((j = 1; j <= 500; j+=10))
    do
        output=$(./a.out  $j)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        echo "Duration: $duration"
        echo $duration >> $output_file
    done    

echo "Resultados guardados en $output_file"
