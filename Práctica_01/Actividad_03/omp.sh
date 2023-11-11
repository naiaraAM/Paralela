#!/bin/bash

num_programs=4
program_names=("MatMul.c" "MatMul_omp_directives.cpp" "MatMul_omp_runtime.cpp" "MatMul_omp_reduction.cpp")
matrix_size=200

# Nombre del archivo donde se guardarán los resultados
output_file="resultados_max_"
output_file+=$1
output_file+="_omp.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING OVER $1 THREADS---"

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    matrix_size=200  # Reset matrix_size before each program run
    case $i in 
        0)
            gcc ${program_names[i]}
        ;;
        1 | 2 | 3)
            export OMP_NUM_THREADS=$1
            g++ -std=c++11 -fopenmp ${program_names[i]}
        ;;
    esac
    while [ $matrix_size -le 1500 ]  # Use the correct comparison operators
    do
        output=$(./a.out $matrix_size 1)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        echo "Duration: $duration"
        # Guarda el resultado en el archivo de salida
        echo $duration >> $output_file
        matrix_size=$((matrix_size + 50))  # Increment matrix_size
    done
done

echo "Resultados guardados en $output_file"
