#!/bin/bash

num_programs=4
program_names=("MatMul_omp_single.cpp" "MatMul_omp_directives.cpp" "MatMul_omp_runtime.cpp" "MatMul_omp_reduction.cpp")
matrix_size=200

# Nombre del archivo donde se guardarán los resultados
output_file="resultados_max_"
output_file+=$1
output_file+="_omp.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING OVER $1 THREADS---"
export OMP_NUM_THREADS=$1

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    matrix_size=200  # Reset matrix_size before each program run
    g++ -std=c++11 -fopenmp ${program_names[i]}
    while [ $matrix_size -le 1500 ]  # Use the correct comparison operators
    do
        output=$(./a.out $matrix_size $1)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        echo "Duration: $duration"
        # Guarda el resultado en el archivo de salida
        echo $duration >> $output_file
        matrix_size=$((matrix_size + 50))  # Increment matrix_size
    done
done

rm -r a.out

python3 ./graphic_omp.py $1