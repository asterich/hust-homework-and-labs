#!/bin/bash

num_files=8
num_lines=10000000
min_value=1
max_value=10000

# 创建并写入随机数到文件
for file_index in $(seq 1 $num_files); do
    output_file="random_numbers_${file_index}.txt"
    echo "Generating $output_file"
    for ((i = 0; i < num_lines; i++)); do
        echo $((RANDOM % max_value + min_value)) >> "$output_file"
    done
done

echo "Finished generating $num_files files."