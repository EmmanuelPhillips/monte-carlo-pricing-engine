import pandas as pd

filepath = r"data/monte_carlo_results.csv"
df = pd.read_csv(filepath)

print(df.head())
