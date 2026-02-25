import matplotlib.pyplot as plt
import math

sizes = []
first_pivot = []
random_pivot = []

with open("quicksort_comparison.txt", "r") as f:
    next(f)
    for line in f:
        s, t1, t2 = line.strip().split()
        sizes.append(int(s))
        first_pivot.append(float(t1))
        random_pivot.append(float(t2))

# ---- Benchmarks ----
n_square = [n**2 for n in sizes]
nlogn = [n * math.log2(n) for n in sizes]

# Scale benchmarks
scale_n2 = first_pivot[0] / n_square[0]
benchmark_n2 = [x * scale_n2 for x in n_square]

scale_nlogn = random_pivot[0] / nlogn[0]
benchmark_nlogn = [x * scale_nlogn for x in nlogn]

# ---- Create one window with two graphs ----
fig, axs = plt.subplots(2, 1, figsize=(8, 10))

# Graph 1: First Pivot vs n²
axs[0].plot(sizes, first_pivot)
axs[0].plot(sizes, benchmark_n2)
axs[0].set_title("First Pivot vs n² Benchmark")
axs[0].set_xlabel("Array Size")
axs[0].set_ylabel("Average Time (microseconds)")
axs[0].legend(["First Pivot", "n² Benchmark"])
axs[0].grid(True)

# Graph 2: Random Pivot vs n log n
axs[1].plot(sizes, random_pivot)
axs[1].plot(sizes, benchmark_nlogn)
axs[1].set_title("Random Pivot vs n log n Benchmark")
axs[1].set_xlabel("Array Size")
axs[1].set_ylabel("Average Time (microseconds)")
axs[1].legend(["Random Pivot", "n log n Benchmark"])
axs[1].grid(True)

plt.tight_layout()
plt.show()