# imports
import math

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# get access to data
filepath = "data/monte_carlo_results.csv"
df = pd.read_csv(filepath)

###################################################################
# Understand the dataset
###################################################################

row_count = df.shape[0]
col_count = df.shape[1]
col_types = df.dtypes
nan_cell_count = df.isna().sum().sum()

print("===================\nBASIC DATASET INFO\n====================")
print(
    f"Row count: {row_count}\n"
    f"Col count: {col_count}\n\n"
    f"Col Headers | Col Types\n{col_types}\n\n"
    f"NaN cell count: {nan_cell_count}"
)
print("-------------------------------")

mathematical_summary = pd.DataFrame(
    {
        "mean": df.mean(),
        "std_dev": df.std(),
        "min": df.min(),
        "max": df.max(),
    }
)

print(mathematical_summary)

###################################################################
# Understand the distributions
###################################################################

n_cols = 3
n_rows = math.ceil(col_count / n_cols)

fig, axes = plt.subplots(n_rows, n_cols)
axes = axes.flatten()

for ax, col in zip(axes, df.columns):
    ax.boxplot(df[col].dropna())
    ax.set_title(col)

plt.tight_layout()

###################################################################
# Investigate what drives the option price
###################################################################

price_features = {
    "spot": df["spot"],
    "strike": df["strike"],
    "volatility": df["volatility"],
    "rate": df["rate"],
}

fig, axes = plt.subplots(2, 2)

for ax, (name, values) in zip(axes.flatten(), price_features.items()):
    ax.scatter(values, df["price"])
    ax.set_title(f"{name} vs price")

plt.tight_layout()

print("\nCorrelations")

correlation_coefficients = (
    df[list(price_features)]
    .corrwith(df["price"])
    .sort_values(key=abs, ascending=False)
    .to_dict()
)

print(correlation_coefficients)
print("\n")

###################################################################
# Compare Monte Carlo against Black-Scholes
###################################################################

df["abs_error"] = (df["price"] - df["bs_price"]).abs()

avg_abs_error = df["abs_error"].mean()
max_abs_error = df["abs_error"].max()

print(
    f"Average absolute error: {avg_abs_error}\n"
    f"Largest absolute error: {max_abs_error}\n"
)

error_features = {
    "spot": df["spot"],
    "strike": df["strike"],
    "volatility": df["volatility"],
    "rate": df["rate"],
}

fig, axes = plt.subplots(2, 2)

for ax, (name, values) in zip(axes.flatten(), error_features.items()):
    ax.scatter(values, df["abs_error"])

    a, b = np.polyfit(values, df["abs_error"], 1)
    x_line = np.linspace(values.min(), values.max(), 100)

    ax.plot(x_line, a * x_line + b, color="red")
    ax.set_title(f"{name} error")

plt.tight_layout()

###################################################################
# Monte Carlo convergence
###################################################################

###################################################################

plt.show()
