#!/bin/bash
program_name=("heated_plate.c" "heated_plate_omp.c")
m_size=100

# Nombre del archivo donde se guardarán los resultados
output_file=("tiempo_threads.txt" "escalability_strong.txt" "escalability_weak.txt")

# Borra el archivo si ya existe
rm -f ${output_file[$1]}

echo "--- RUNNING ---"
g++ -std=c++11 -fopenmp ${program_name[0]} -o sec
g++ -std=c++11 -fopenmp ${program_name[1]} -o omp

t_sec=$(./sec $m_size $m_size| grep "Wallclock time" | awk '{print $4}')


case $1 in
    0)
        for ((i = 1; i < 17; i++))
        do
            echo "--- $i threads ---"
            ./omp $i | grep "Wallclock time" | awk '{print $4}' >> ${output_file[$1]}
        done
    ;;
    1)
        for ((i = 1; i < 9; i++))
        do
            echo "--- $i threads ---"
            t_par=$(./omp $i | grep "Wallclock time" | awk '{print $4}')
            speedup=$(echo "scale=4; $t_sec/$t_par" | bc)
            echo $speedup >> ${output_file[$1]}
        done
    ;;
    2)
        for ((i = 1; i < 9; i++))
        do
            m_size=100
            echo "--- $i threads ---"
            m_size=$((m_size * i))
            t_sec=$(./sec $m_size $m_size| grep "Wallclock time" | awk '{print $4}')
            t_par=$(./omp $i $m_size $m_size| grep "Wallclock time" | awk '{print $4}')
            speedup=$(echo "scale=4; $t_sec/$t_par" | bc)
            echo $speedup >> ${output_file[$1]}
        done
    ;;
esac

rm sec
rm omp
rm a.out

python3 graphic.py $1