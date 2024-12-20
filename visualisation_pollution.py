import numpy as np
import matplotlib.pyplot as plt


filename = 'Internal/C02_terrain.csv'
data = np.loadtxt(filename) 
    
# Reshaping the data into a 100x100 array

terrain = data.reshape((100,100))

# Creating the plot
plt.figure(figsize=(8, 8))
im = plt.imshow(terrain, cmap='viridis', origin='lower', aspect='equal')

# Adding a color bar with a label
cbar = plt.colorbar(im)
cbar.set_label("Concentration de CO2 [ppm]", fontsize=12)

# Adding labels and a title
plt.title("Concentration de CO2 dans l'atmosphère", fontsize=14)
plt.xlabel("X", fontsize=12)
plt.ylabel("Y", fontsize=12)

# Customizing the ticks
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

plt.savefig('Output/pollution_visualisation')
plt.show()
