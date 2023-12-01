#!/bin/bash

num_programs=2
program_names=("MatMul_threads_Mul_Inf.cpp" "MatMul_omp_Mul_Inf.cpp")
matrix_size=200
t_sec=()
output_file="resultados.txt"
counter=0

rm -f $output_file

echo "--- RUNNING ---"

gcc MatMul.c

while [ $matrix_size -le 1500 ]
do
    output=$(./a.out $matrix_size 1)
    duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
    t_sec[$counter]=$duration
    counter=$((counter + 1))
    matrix_size=$((matrix_size + 50))
done

for ((i = 0; i < num_programs; i++))
do
    echo "--- Executing ${program_names[i]} ---"
    matrix_size=200  # Reset matrix_size before each program run
    case $i in 
        0)
            g++ -std=c++11 -pthread ${program_names[i]}
        ;;
        1)
            g++ -std=c++11 -fopenmp ${program_names[i]}
        ;;
    esac
    counter=0
    while [ $matrix_size -le 1500 ]
    do
        output=$(./a.out $matrix_size 1 8)
        duration=$(echo "$output" | grep "Duration" | awk '{print $2}')
        speed_up=$(echo "scale=4; ${t_sec[$counter]} / $duration" | bc)
        echo "Speed up: $speed_up"
        echo $speed_up >> $output_file
        matrix_size=$((matrix_size + 50))
        counter=$((counter + 1))
    done
done
rm a.out
echo "--- DONE ---"
python3 graphic.py