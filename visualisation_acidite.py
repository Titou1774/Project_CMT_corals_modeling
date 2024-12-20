import numpy as np
import matplotlib.pyplot as plt

# Loading data from the file
filename = "Internal/acidite_terrain.csv"
data = np.loadtxt(filename)

# Reshaping the data into a 100x100 array
terrain = data.reshape((100, 100))

# Creating the plot
plt.figure(figsize=(8, 8))
im = plt.imshow(terrain, cmap='viridis', origin='lower', aspect='equal')

# Adding a color bar with a label
cbar = plt.colorbar(im)
cbar.set_label("pH of water", fontsize=12)

# Adding labels and a title
plt.title("Acidity of the water field", fontsize=14)
plt.xlabel("X", fontsize=12)
plt.ylabel("Y", fontsize=12)

# Customizing the ticks
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

plt.savefig('Output/acidity_visualisation')
plt.show()


