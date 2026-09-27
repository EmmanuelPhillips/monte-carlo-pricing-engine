import pandas as pd

filepath = r"data/monte_carlo_results.csv"
df = pd.read_csv(filepath)

# get initial info to understand the dataset
# NB: i could have done this using just .describe(), but its more interesting to do it this way
row_count = df.shape[0]
col_count = df.shape[1]
col_headers = df.columns.tolist()
col_types = (
    df.dtypes
)  # this also prints the headers so no need to actually print col_headers variable
nan_cell_count = df.isna().sum().sum()

print("===================\nBASIC DATASET INFO\n====================")
print(
    f"Row count: {row_count}\nCol count: {col_count}\n\nCol Headers | Col Types \n{
        col_types
    }\n\nNaN cell count: {nan_cell_count}"
)
print("-------------------------------")

mathematical_summary = pd.DataFrame(
    {"mean": df.mean(), "std_dev": df.std(), "min": df.min(), "max": df.max()}
)
print(mathematical_summary)
