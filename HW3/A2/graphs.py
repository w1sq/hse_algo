from pathlib import Path

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.style.use("default")
plt.rcParams["figure.figsize"] = (12, 6)
plt.rcParams["font.size"] = 12
plt.rcParams["axes.grid"] = True
plt.rcParams["grid.alpha"] = 0.3


def plot_performance_comparison(df, output_dir):
    array_types = df["array_type"].unique()
    thresholds = df[df["algorithm"] == "hybrid"]["threshold"].unique()

    for arr_type in array_types:
        plt.figure(figsize=(12, 6))

        # График для стандартного MergeSort
        standard_data = df[
            (df["algorithm"] == "standard") & (df["array_type"] == arr_type)
        ]
        plt.plot(
            standard_data["size"],
            standard_data["time"],
            label="Standard MergeSort",
            linewidth=2,
        )

        # Графики для гибридного MergeSort
        colors = plt.cm.viridis(np.linspace(0, 1, len(thresholds)))
        for threshold, color in zip(thresholds, colors):
            hybrid_data = df[
                (df["algorithm"] == "hybrid")
                & (df["array_type"] == arr_type)
                & (df["threshold"] == threshold)
            ]
            plt.plot(
                hybrid_data["size"],
                hybrid_data["time"],
                label=f"Hybrid (threshold={threshold})",
                linestyle="--",
                color=color,
            )

        plt.title(
            f'Sorting Performance Comparison\n{arr_type.replace("_", " ").title()} Arrays'
        )
        plt.xlabel("Array Size")
        plt.ylabel("Time (microseconds)")
        plt.legend(bbox_to_anchor=(1.05, 1), loc="upper left")
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(
            output_dir / f"sorting_comparison_{arr_type}.png",
            dpi=300,
            bbox_inches="tight",
        )
        plt.close()


def main():
    output_dir = Path("visualization_results")
    output_dir.mkdir(exist_ok=True)

    df = pd.read_csv("sorting_results.csv")
    plot_performance_comparison(df, output_dir)


if __name__ == "__main__":
    main()
