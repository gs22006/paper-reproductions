import sys
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


def main(csv_path: str, out_dir: str) -> None:
    out = Path(out_dir)
    out.mkdir(parents=True, exist_ok=True)

    df = pd.read_csv(csv_path)

    for experiment, xcol, fname in [
        ("by_n", "n", "alg1_vs_dp_by_n.png"),
        ("by_wmax", "w_max", "alg1_vs_dp_by_wmax.png"),
    ]:
        sub = df[df["experiment"] == experiment].copy()
        if sub.empty:
            continue
        grouped = sub.groupby(["algo", xcol], as_index=False)["time_ms"].median()

        plt.figure(figsize=(8, 5))
        for algo, g in grouped.groupby("algo"):
            g = g.sort_values(xcol)
            plt.plot(g[xcol], g["time_ms"], marker="o", label=algo)
        plt.xlabel(xcol)
        plt.ylabel("median time (ms)")
        plt.title(f"Algorithm 1 vs baseline DP ({experiment})")
        plt.legend()
        plt.tight_layout()
        plt.savefig(out / fname, dpi=160)
        plt.close()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python plot_alg1.py <csv_path> <out_dir>")
        raise SystemExit(1)
    main(sys.argv[1], sys.argv[2])
