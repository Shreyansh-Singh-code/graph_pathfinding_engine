import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

RESULTS = Path("../results")

df = pd.read_csv(RESULTS / "benchmark_results.csv")

summary = (
    df.groupby("Algorithm")
      .agg(
        AvgTime=("TimeMs", "mean"),
        AvgExpanded=("Expanded", "mean"),
        AvgDistance=("Distance", "mean")
      )
      .reset_index()
)

optimal = summary.loc[
    summary["Algorithm"] == "Dijkstra",
    "AvgDistance"
].iloc[0]

summary["PathInflation(%)"] = (
    (summary["AvgDistance"] - optimal)
    / optimal
) * 100

summary["Speedup"] = (
    summary.loc[
        summary["Algorithm"] == "Dijkstra",
        "AvgTime"
    ].iloc[0]
    / summary["AvgTime"]
)

summary.to_csv(
    RESULTS / "benchmark_summary.csv",
    index=False
)

plt.rcParams["figure.figsize"] = (10,6)

# ---------------- Runtime ----------------

plt.figure()

plt.bar(
    summary["Algorithm"],
    summary["AvgTime"]
)

plt.ylabel("Average Runtime (ms)")
plt.title("Runtime Comparison")

plt.tight_layout()

plt.savefig(
    RESULTS / "runtime_comparison.png",
    dpi=300
)

plt.close()

# ---------------- Expanded Nodes ----------------

plt.figure()

plt.bar(
    summary["Algorithm"],
    summary["AvgExpanded"]
)

plt.ylabel("Average Expanded Nodes")
plt.title("Search Space Comparison")

plt.tight_layout()

plt.savefig(
    RESULTS / "expanded_nodes.png",
    dpi=300
)

plt.close()

# ---------------- Path Inflation ----------------

plt.figure()

plt.bar(
    summary["Algorithm"],
    summary["PathInflation(%)"]
)

plt.ylabel("Path Inflation (%)")
plt.title("Solution Quality")

plt.tight_layout()

plt.savefig(
    RESULTS / "path_quality.png",
    dpi=300
)

plt.close()

# ---------------- Speedup ----------------

plt.figure()

plt.bar(
    summary["Algorithm"],
    summary["Speedup"]
)

plt.ylabel("Speedup vs Dijkstra")
plt.title("Relative Speedup")

plt.tight_layout()

plt.savefig(
    RESULTS / "speedup.png",
    dpi=300
)

plt.close()

print(summary)
print("\nSaved plots to results/")