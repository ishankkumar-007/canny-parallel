import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv("../csv/performance.csv")

# Speedup Calculation
base_time = data["Time"][0]

data["Speedup"] = base_time / data["Time"]

# Plot Speedup
plt.figure(figsize=(10, 6))
plt.plot(data["Threads"], data["Speedup"], marker='o', label="Canny Edge Detection without power")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup")
plt.title("Speedup vs Threads")
plt.legend()
plt.grid()
plt.savefig("../csv/speedup_plot.png")
plt.show()
