import matplotlib.pyplot as plt
import re
import sys
import os

if len(sys.argv) < 2:
    print("Usage: plot.py <filename>")
    sys.exit(1)

data = {}

filename = sys.argv[1]

with open(filename, 'r') as file:
    current_thread_pool = None

    for line in file:
        if "Thread Pool Size" in line:
            current_thread_pool = int(re.search(r'\d+', line).group())
            data[current_thread_pool] = {"concurrency" : [], "requests_per_second": []}

        elif "Concurrency" in line:
            concurrency = int(re.search(r'Concurrency: (\d+)', line).group(1))
            requests_per_second = float(re.search(r'Requests per second: ([\d.]+)', line).group(1))

            data[current_thread_pool]["concurrency"].append(concurrency)
            data[current_thread_pool]["requests_per_second"].append(requests_per_second)

plt.figure(figsize=(10,6))

for thread_pool_size, values in data.items():
    plt.plot(values["concurrency"], values["requests_per_second"], label=f'Threadpoolsize = {thread_pool_size}')

plt.xlabel("Concurrency requests")
plt.ylabel("Throughput (Results/second)")
plt.title("Load vs Throughput plot")
plt.legend()
plt.grid()
plt.tight_layout()

imgname = os.path.splitext(filename)[0] + ".jpg"

plt.savefig(imgname)