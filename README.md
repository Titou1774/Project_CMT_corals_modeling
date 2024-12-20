# Computational Methods and Tools - Project : Modeling the impact of temperature and anthropogenic activity on a coral ecosystem

## Project description

This program simulates in first the impact of temperature on a coral reef in Gili Island. In a second time, the program simulate a release of pollutants and how it impacts the corals.

The program will:
1. Apply a function that solve a differential system of equations, that save results in a CSV file ("ecosystem_simulation_results.csv")
2. Simulate the release of CO2 in atmosphere and how it's affect the pH of the ocean and save the results in 3 CSV files ("*C02_terrain.csv*", "*acidite_terrain.csv*", "*valeurs_uniques_pH_sante.csv*") in "*ecosystem_simulation.c*"
3. Plot the results of the CSV file ("*ecosystem_simulation_results.csv*") in the following python file: "*visualisation_modele.py*"
4. Plot the results of the two CSV files ("*C02_terrain.csv*" and "*acidite_terrain.csv*") in the following python files: "*visualisation_pollution.py*" and "*visualisation_acidite.py*" respectively
5. Apply linear regression method on datas collected in the CSV file ("*valeurs_uniques_pH_sante.csv*") and plot it in following python file: "*regressionlineaire.py*"
6. All graphs results obtained, and key figures will be saved in "*Ouptut*" as .png

## Project structure

- As the data used were few in number, it was quicker to write them directly to the code. We mention them in the code. 
- "*Internal*" contains files used for passing information between C and Python. They are automatically edited by the program and should not be manually modified (.csv files)
- "*Code*" contains program code
- "*Output*" contains saved .png files

### Inputs and Outputs

Inputs:
- As the data used were few in number, it was quicker to write them directly to the code. We mention them in the code.

Internal files:
- "*Internal/ecosystem_simulation_results.csv*", is a comma-delimited file.
- "*Internal/CO2_terrain.csv*", 1 column and 10'000 rows file.
- "*Internal/acidite_terrain.csv*", 1 column and 10'000 rows file.
- "*Internal/valeurs_uniques_pH_sante.csv*", is a comma-delimited file.

Outputs:
- "*Output*" contains several image files, each has a custom name of format: "*Name.png*". Do **not** delete this type of file.
- "*C02_atmosphere_figure.png*" is an image file, showing the C02 concentration in the atmosphere
- "*pH_water_figure.png*" is an image file, showing the pH of water
- "*observation_results.png*" is an image file, plotting the datas collected for linear regression
- "*final_curve.png*" is an image file, plotting the relation between coral health and the pH of water, after the linear regression

## Implementation details

**Overview:**

- The simulation is handled by C. It directly outputs the results of computation into a CSV file.
- Python reads CSV file values, which contains parameters and plot CSV contents.
- The simulation is handled by C. It directly outputs the results of computation into 3 other CSV file ( "*Internal/CO2_terrain.csv*" , "*Internal/acidite_terrain.csv*" , "*Internal/valeurs_uniques_pH_sante.csv*" ).
- 2 Python program reads  "*Internal/CO2_terrain.csv*" and "*Internal/acidite_terrain.csv*" respectively, which contains parameters selected by the user and plot CSV contents.
- The last Python program reads"*Internal/valeurs_uniques_pH_sante.csv*", make the linear regression  with the Numpy module and plot the results.

**Structure**: In the directory "*Code/*" are located:
 
- "*functions_humanimpact.c*"
    - Imports "*functions_humanimpact.h*" as a module
    - Performs computations only via functions

- "determination_temperature_pH.c"
    - Performs computations only via functions

- "*implementation_equa_diff.c*"
    - Import "*determination_temperature_pH.h*" as module
    - Export results in the CSV: "*ecosystem_simulation_results.csv*"
    - Performs compuatations via functions and via "*determination_temperature_pH.c*"

- "*ecosystem_simulation.c*"
    - Main code
    - Imports "*functions_humanimpact.c*","*determination_temperature_pH.c*", "*implementation_equa_diff.c*" as modules.
    - Export results in CSV: "*C02_terrain.csv*, "*acidite_terrain.csv*", "*valeurs_uniques_pH_sante.csv*"
  
- "*visualisation_temperature_impact.py*"
    - Reads in the CSV "*Internal/ecosystem_simulation_results.csv*".
    - Plots results in a separate window.
    - Saves key plots to directory "*Output*".
    
- "*visualisation_pollution.py*"
    - Reads in the CSV "*Internal/C02_terrain.csv*".
    - Plots results in a separate window.
    - Saves key plots to directory "*Output*".

- "*visualisation_acidite.py*"
    - Reads in the CSV "*Internal/acidite_terrain.csv*" and make the pH figure(see report)
    - Plots results in a separate window.
    - Saves key plots to directory "*Output*".

- "*regressionlineaire.py*"
    - Reads in the CSV "*Internal/valeurs_uniques_pH_sante.csv*" and compute the model"
    - Plots results in a separate window.
    - Saves key plots to directory "*Output*".



## Instructions

To reproduce results in the report, four steps should be followed:
1. Navigate to the "*ecosystem_simulation.c*" function located in the "*Code*" directory. The function contains commented instructions for the user to modify input parameters. Modify as desired.
2. Navigate to the makefile to ensure the Python interpreter selected is yours.
3. Open the terminal from the project root directory (location of this README.md file). You can check this is the case by typing:
    ```
    ls
    ```
    The terminal should return:
    ```
    Code    Data    Internal    README.md   Results    makefile
    ```
4. Run the following line in the terminal:
    ```
    make
    ```
The program will run automatically, and will open two plotting windows in full screen. Once you close them , the program cleans up compiled filed files and terminates automatically.

## Requirements

Versions of Python and C used are as follows.
```
$ python --version
Python 3.12.4

$ gcc --version
(Rev3, Built by MSYS2 project) 13.2.0

The Python libraries utilized were the following:
```
pandas 2.2.2 py312h0158946_0

numpy 1.26.4 py312hfd52020_0  
numpy-base 1.26.4 py312h4dde369_0

subprocess 2.4

matplotlib 3.9.3 pypi_0 pypi
matplotlib-inline 0.1.6 py312haa95532_0 

csv 1.0
```

## Credits

### Data

The data files "*Rhine_DO_Palmrainbrücke.csv*", "*Rhine_Flowrate_Rheinhalle.csv*"  and "*Rhine_Watertemperature_Palmrainbrucke.csv*" come from the [Swiss Federal Bureau for the Environment](https://www.bafu.admin.ch/bafu/en/home/topics/water/state/data/obtaining-monitoring-data-on-the-topic-of-water/hydrological-data-service-for-watercourses-and-lakes.html).

The data file "*Rhine_depth.csv*" comes from the [French eauFrance](hydro.eaufrance.fr).

The data file "*Rhine_windspeeds.txt*" comes from the [Swiss Federal Office of Meteorology](https://www.meteoswiss.admin.ch/services-and-publications/service/weather-and-climate-products/data-portal-for-teaching-and-research.html).

### Formulae

The function tracking dissolved oxygen relies on the [Streeter-Phelps](https://en.wikipedia.org/wiki/Streeter%E2%80%93Phelps_equation) equation, taken from Pearson's *[Introduction to Environmental Engineering and Science](https://www.pearson.com/en-gb/subject-catalog/p/introduction-to-environmental-engineering-and-science-pearson-new-international-edition/P200000004949/9781292025759)*.

The function tracking pollutant concentrations is based on the Van Genuchten equation, solved by Jin & al in *[Mitigation of impact of a major benzene spill into a river](https://www.sciencedirect.com/science/article/pii/S0043135420300257)*.

