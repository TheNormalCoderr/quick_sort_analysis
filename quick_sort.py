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

# ---- Create theoretical n log n benchmark ----
nlogn = [n * math.log2(n) for n in sizes]

# Scale benchmark to match first data point
scale_factor = first_pivot[0] / nlogn[0]
benchmark = [x * scale_factor for x in nlogn]

plt.figure(figsize=(10, 6))

plt.plot(sizes, first_pivot, linewidth=2.5, marker='o', markersize=4)
plt.plot(sizes, random_pivot, linewidth=2.5, linestyle='--', marker='s', markersize=4)
plt.plot(sizes, benchmark, linestyle=':', linewidth=3)

plt.xlabel("Array Size", fontsize=12)
plt.ylabel("Average Time (microseconds)", fontsize=12)
plt.title("QuickSort: First Pivot vs Random Pivot vs n log n Benchmark", fontsize=14)

plt.legend(["First Pivot", "Random Pivot", "n log n Benchmark"])
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()