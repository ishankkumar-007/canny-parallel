#!/bin/bash

# Define directories
OUT_DIR="./csv"

# Create bin directory if not exists
mkdir -p "$OUT_DIR"

g++ -fopenmp main.cpp canny.cpp HashMap.cpp

# Output CSV file
CSV_FILE="$OUT_DIR/performance.csv"
echo "Threads,Time" > "$CSV_FILE"

# Run experiments
for threads in 1 2 4 6 8 10 12 16 20 32 64
# for threads in 80 96 128 192 256 512 1024
do
    export OMP_NUM_THREADS=$threads
    OUTPUT=$(./a.out chess.pgm 100 1)
    TIME=$(echo "$OUTPUT" | grep -oP 'Total time\s*:\s*\K[0-9.]+')
    echo "$threads,$TIME" >> "$CSV_FILE"
done

echo "Completed! Data stored in $CSV_FILE"
