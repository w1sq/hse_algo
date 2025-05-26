import csv
import subprocess

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

EXECUTABLE = "./tester"
TYPES = ["random", "reverse", "almost"]
SIZES = [100, 200, 500, 1000, 1500, 2000, 2500, 3000]
MINLEN, MAXLEN = 10, 200

SORTS = [
    ("QuickSort", 0),
    ("MergeSort", 1),
    ("StringQuickSort", 2),
    ("StringMergeSort", 3),
    ("MSDRadixSort", 4),
    ("MSDRadixSortWithCutoff", 5),
]
CUTOFF = 74
REPEATS = 5

results = []

for type_ in TYPES:
    for size in SIZES:
        for sort_name, sort_type in SORTS:
            times = []
            cmps = []
            for _ in range(REPEATS):
                args = [
                    EXECUTABLE,
                    type_,
                    str(size),
                    str(MINLEN),
                    str(MAXLEN),
                    str(sort_type),
                ]
                if sort_type == 5:
                    args.append(str(CUTOFF))
                print(f"Running: {' '.join(args)}")
                try:
                    proc = subprocess.run(
                        args, capture_output=True, text=True, check=True
                    )
                    time_ms, cmp_count = proc.stdout.strip().split()
                    times.append(float(time_ms))
                    cmps.append(int(cmp_count))
                except Exception as e:
                    print(f"Error running {' '.join(args)}: {e}")
            avg_time = np.median(times)
            avg_cmp = np.median(cmps)
            results.append([type_, size, sort_name, avg_time, avg_cmp])

with open("results.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["Type", "Size", "Sort", "Time_ms", "CmpCount"])
    writer.writerows(results)

print("Results saved to results.csv")

df = pd.read_csv("results.csv")

for type_ in TYPES:
    plt.figure(figsize=(10, 6))
    for sort_name, _ in SORTS:
        subset = df[(df["Type"] == type_) & (df["Sort"] == sort_name)]
        plt.plot(subset["Size"], subset["Time_ms"], marker="o", label=sort_name)
    plt.title(f"Sorting Time vs Size ({type_})")
    plt.xlabel("Array Size")
    plt.ylabel("Time (ms)")
    plt.legend()
    plt.grid(True)
    plt.savefig(f"images/time_vs_size_{type_}.png")
    plt.show()

    plt.figure(figsize=(10, 6))
    for sort_name, _ in SORTS:
        subset = df[(df["Type"] == type_) & (df["Sort"] == sort_name)]
        plt.plot(subset["Size"], subset["CmpCount"], marker="o", label=sort_name)
    plt.title(f"Symbol Comparisons vs Size ({type_})")
    plt.xlabel("Array Size")
    plt.ylabel("Symbol Comparisons")
    plt.legend()
    plt.grid(True)
    plt.savefig(f"images/cmp_vs_size_{type_}.png")
    plt.show()

subset = df[(df["Type"] == "random") & (df["Size"] == 3000)]
print(f"### Эмпирические данные (random, n=3000)\n")
print("| Алгоритм | Время, мс | Сравнений |")
for _, row in subset.iterrows():
    name = (
        row["Sort"]
        .replace("MSDRadixSort", "MSD Radix Sort")
        .replace("StringQuickSort", "String QuickSort")
        .replace("StringMergeSort", "String MergeSort")
    )
    print(f"| {name} | {row['Time_ms']:.2f} | {int(row['CmpCount']):,} |")
