import csv
import matplotlib.pyplot as plt
import numpy as np


#DATASET
x_liste = []
y_liste = []

#ph and health 
with open("Internal/valeurs_uniques_pH_sante.csv", mode="r") as file:
    reader = csv.reader(file)

    for row in reader:
        x_liste.append(float(row[0]))
        y_liste.append(float(row[1]))

x = np.array(x_liste)
y = np.array(y_liste)

x = x.reshape((len(x_liste),1))
y = y.reshape((len(y_liste),1))

#Plotting our observations
plt.scatter(x,y)
plt.savefig('Output/single_values_corals(pH)')
plt.show()

#Normalize the x axe, the range is too small. If we don't do this step, the red curve will not satsying our observations
x_mean = np.mean(x)
x_std = np.std(x)
x = (x - x_mean) / x_std

#MATRICE X, a mx2 matrix, m the number of observations, first column is our values of pH, and the second column is full of one
X = np.hstack((x, np.ones(x.shape)))

#MATRICE THETA, a 2x1 matrix, with a and b that we want estimate
theta = np.ones((2,1))

#MODELE (Y = ax + b)
def model(A1, A2):
    return A1@A2

#MEAN SQUARED ERROR
def error_moyenne(X,y,theta):
    m = len(y)
    return 1/(2*m)*np.sum((model(X,theta)-y)**2)

#GRADIENTS
def gradient(X,theta,y):
    m = len(y)
    return (1/m)*np.transpose(X)@(model(X,theta)-y)

def gradient_descendant(X,theta, y,alpha, n):
    for i in range(0,n):
        theta = theta -alpha*gradient(X,theta,y)
        
    return theta

#Final curve, with a and b estimated
theta_final = gradient_descendant(X,theta,y, 0.001, 10000) # alpha=0.001, number of iterations n = 10000
courbe_finale = model(X,theta_final)

# To make the x axe as the beginning
x = (x*x_std)+x_mean

#print the values of final a and b
print(theta_final)
#Plotting our model
plt.scatter(x,y)
plt.plot(x,courbe_finale, c = "r")
plt.savefig("Output/linear_regression_corals_pH")
plt.show()

