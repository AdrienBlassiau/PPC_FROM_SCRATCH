import matplotlib.pyplot as plt
import numpy as np
from statistics import mean, variance, stdev, pstdev

t = np.arange(4., 70., 1)

h = [6,5,17,11,25,11,81,205,437,100,1110,26,4067,861,541,565,20,29,409,3184,38,246,628,135,2565,548,6362,126,62,51,474,1581,82,1211,1636,39,40779,51,289873,62,67,425,20107,2886,6456,2790,318,195,242,4193,934507,770,6963,13871,58,1243,82,88,70,7691,5808,455,1667,316,269,26692]

fig, ax = plt.subplots()

plt.plot(t,h, "o:", markersize=4)

plt.yscale("log")

plt.title("Nombre de branchements en fonction de la taille de l'instance de n-Reines")
plt.xlabel("Taille de l'instance de n-Reines")
plt.ylabel("Nombre de branchements")
plt.show()