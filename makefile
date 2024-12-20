### ------ Setting up the compiling of C files ------ ###
#Compiler for C files
CC = gcc

# Compiling flags
CFLAGS = -Wall -O2

# Libraries
LIBS = -lm

# Output
OUT = -o

### ------ Setting up the compiling of Python files ------ ###
# Python interpreter - use your own. 
PYTHON =  C:/Users/Titouan/Anaconda3/python.exe

# Specification of C files names and their relative paths
C_FILE= Code/ecosystem_simulation.c

# Specification of the name of our Python files
PYTHON_FILE_1 = Code/visualisation_temperature_impact.py
PYTHON_FILE_2 = Code/visualisation_pollution.py
PYTHON_FILE_3 = Code/visualisation_acidite.py
PYTHON_FILE_4 = Code/regressionlineaire.py


### ------ Order of compiling files ------ ###
all: compile_c run_python_1 run_python_2 run_python_3 run_python_4 clean

### --- Line command (target) to compile the C file --- ###
compile_c: $(C_FILE)
	$(CC) $(C_FILE) $(CFLAGS) $(LIBS) $(OUT) $(basename $(C_FILE))


### --- Target to run the Python files --- ###
run_python_1:
	$(PYTHON) $(PYTHON_FILE_1)

run_python_2:
	$(PYTHON) $(PYTHON_FILE_2)

run_python_3:
	$(PYTHON) $(PYTHON_FILE_3)

run_python_4:
	$(PYTHON) $(PYTHON_FILE_4)



# Clean target to remove compiled files
clean:
	rm -f $(basename $(C_FILE))
