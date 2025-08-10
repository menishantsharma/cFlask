#!/bin/bash

# This is loadgen script. Just run
declare -a URLS=("http://localhost:9999/arithmetic/prime?num=999999937" "http://localhost:9999/pingpong?str=Nishant" "http://localhost:9999/arithmetic/fibonacci?num=500000")
declare -a thread_pool_sizes=(1 3 5)
declare -a concurrency_levels=(1 2 3 4 5 6 7 8 9 10)

itr=1
for URL in ${URLS[@]}; do
    output_file="./plots/loadtest$itr.data"

    echo "Load Test Results: $URL" > "$output_file"
    echo "--------------------------------------" >> "$output_file"
    
    for thread_pool_size in ${thread_pool_sizes[@]}; do
        sleep 4
        ./flask 9999 "$thread_pool_size" &
        
        echo "Thread Pool Size: $thread_pool_size" >> "$output_file"
        for concurrency in "${concurrency_levels[@]}"; do
            sleep 2
            result=$(ab -n 5000 -c "$concurrency" "$URL" 2>&1)
            requests_per_second=$(echo "$result" | grep "Requests per second:" | awk '{print $4}')
            echo "Concurrency: $concurrency, Requests per second: $requests_per_second" >> "$output_file"
            echo "Concurrency: $concurrency, Requests per second: $requests_per_second"
        done
        pkill -f "flask"
        echo "" >> "$output_file" 
    done
    echo "Load test complete. Results saved in $output_file."
    sleep 2
    python3 plot.py "./plots/loadtest$itr.data"
    itr=$((itr + 1))
done
