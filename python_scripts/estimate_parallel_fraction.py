import pandas as pd
from scipy.optimize import curve_fit

data = pd.read_csv("../output/performance.csv")

# Speedup Calculation
base_time_critical = data["Time"][0]

data["Speedup"] = base_time_critical / data["Time"]

# Amdahl's Law Function
def amdahl(N, P):
    return 1 / ((1 - P) + (P / N))

# Curve Fitting
popt, _ = curve_fit(amdahl, data["Threads"], data["Speedup"])
P_estimated = popt[0]

print(f"Estimated Parallelizable Fraction: {P_estimated:.4f}")
