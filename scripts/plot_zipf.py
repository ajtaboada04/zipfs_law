import matplotlib.pyplot as plt
import numpy as np

# Load data from file
ranks, frequencies = np.loadtxt("output.txt", usecols=(0, 1), unpack=True)

# Plot in log-log scale
plt.figure(figsize=(10, 6))
plt.loglog(ranks, frequencies, marker="o", linestyle="none")
plt.xlabel("Rank (log scale)")
plt.ylabel("Frequency (log scale)")
plt.title("Zipf's Law Plot")
plt.grid(True)
plt.show()
