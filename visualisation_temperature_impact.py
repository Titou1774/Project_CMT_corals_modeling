
import matplotlib.pyplot as plt
import pandas as pd

# Reading the CSV file of the impact of temperature

data = pd.read_csv("Internal/ecosystem_simulation_results.csv")


# Adjusting years
start_year = 2020
end_year = 2040
time = [t + start_year for t in data["Time"]]

# Create the figure and subplots
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 10))

# First subplot: Coral biomasses and temperature
ax1.plot(time, data["C"], label="Corals (acropora)", color="red")
ax1.set_xlim(start_year, end_year)
ax1.set_xlabel("Time [years]")
ax1.set_ylabel(r'Biomass [kg m$^{-2}$]', color="black")
ax1.tick_params(axis='y', labelcolor="black")
ax1.set_title("Dynamics of Coral Populations and Temperature")
ax1.grid()
ax1.legend(loc="upper left")

# Adding temperature on the first subplot
ax1_temp = ax1.twinx()
ax1_temp.plot(time, data["Temperature"], label="Temperature (°C)", color="gold", linestyle="--")
ax1_temp.axhline(y=30, color='black', linestyle=':', linewidth=2, label="Critical Temperature for Acropora (30°C)")
ax1_temp.set_ylabel("Temperature [°C]", color="black")
ax1_temp.tick_params(axis='y', labelcolor="black")
ax1_temp.legend(loc="upper right")

# Second subplot: Other species biomasses and temperature
ax2.plot(time, data["W"], label="Wrasses", color="blue")
ax2.plot(time, data["A"], label="Anemones", color="green")
ax2.plot(time, data["S"], label="Starfish", color="purple")
ax2.set_xlim(start_year, end_year)
ax2.set_xlabel("Time [years]")
ax2.set_ylabel(r'Biomass [kg m$^{-2}$]', color="black")
ax2.tick_params(axis='y', labelcolor="black")
ax2.set_title("Dynamics of Other Species and Temperature")
ax2.grid()
ax2.legend(loc="upper left")

# Adding temperature on the second subplot
ax2_temp = ax2.twinx()
ax2_temp.plot(time, data["Temperature"], label="Temperature (°C)", color="gold", linestyle="--")


# We can eventually put the critical temperature for other species but this a little bit too fat for reading the graph

#ax2_temp.axhline(y=32.5, color='blue', linestyle=':', linewidth=2, label="Critical Temperature for Wrasses (32.5°C)")
#ax2_temp.axhline(y=32, color='green', linestyle=':', linewidth=2, label="Critical Temperature for Anemones (32°C)")
#ax2_temp.axhline(y=31.5, color='purple', linestyle=':', linewidth=2, label="Critical Temperature for Starfish (31.5°C)")


ax2_temp.set_ylabel("Temperature [°C]", color="black")
ax2_temp.tick_params(axis='y', labelcolor="black")
ax2_temp.legend(loc="upper right")

# Spacing adjustment and saving
plt.tight_layout()
plt.savefig("Output/visualisation_ecosystem_simulation_results.png")
plt.show()
