#!/bin/bash

program_name="MatMul_omp_Mul_Inf_dynamic.cpp"
num_iters=5

# Nombre del archivo donde se guardarán los resultados
output_file="results_block_dynamic.txt"
threads=8

# Borra el archivo si ya existe
rm -f $output_file

echo "--- Executing $program_name ---"
g++ -std=c++11 -fopenmp $program_name

for ((i = 0; i < 2; i++))
do
    echo "Threads: $threads"
    export OMP_NUM_THREADS=$threads
    for ((j = 24; j <= 75; j++))
    do
        total_duration=0
        for ((k = 0; k < num_iters; k++))
        do
            output=$(./a.out 1500 $j)
            duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
            echo "Duration ($threads, $j, $k): $duration"
            
            total_duration=$(echo "$total_duration + $duration" | bc)
        done

        average_duration=$(echo "scale=6; $total_duration / $num_iters" | bc)
        echo "Average duration: $average_duration"
        echo "$j $average_duration" >> $output_file
    done
    threads=16 
done

echo "Resultados guardados en $output_file"

rm a.out

python3 graphic_block_dynamic.py
