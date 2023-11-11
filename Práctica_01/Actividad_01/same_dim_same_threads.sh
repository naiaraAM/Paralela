#!/bin/bash

num_programs=2
program_names=("MatMul_threads.cpp" "MatMul_omp.cpp")
matrix_size=1300

# Nombre del archivo donde se guardarán los resultados
output_file="resultados_2.txt"

# Borra el archivo si ya existe
rm -f $output_file

echo "--- RUNNING ---"

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    case $i in 
        0)
            g++ -std=c++11 -pthread ${program_names[i]}
            for ((j = 1; j <= 8; j++))
            do
                output=$(./a.out $matrix_size 1 $j)
                duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
                echo "Duration: $duration"
                echo $duration >> $output_file
            done
        ;;
        1)
            g++ -std=c++11 -fopenmp ${program_names[i]}
            for ((j = 1; j <= 8; j++))
            do
                output=$(./a.out $matrix_size 1 $j)
                duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
                echo "Duration: $duration"
                echo $duration >> $output_file
            done
        ;;
    esac
done

echo "Resultados guardados en $output_file"
rm a.out

python3 graphic_same.py