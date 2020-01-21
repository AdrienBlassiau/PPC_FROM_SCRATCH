import matplotlib.pyplot as plt
import numpy as np
from statistics import mean, variance, stdev, pstdev

t2 = np.arange(6)

h1g = np.array([26,5417,239,11,23,95]).astype(np.double)
h1gmask = np.isfinite(h1g)
h2g = np.array([26,5417,239,11,23,95]).astype(np.double)
h2gmask = np.isfinite(h2g)
h3g = np.array([26,5417,239,11,23,95]).astype(np.double)
h3gmask = np.isfinite(h3g)
h4g = np.array([26,5417,239,11,23,95]).astype(np.double)
h4gmask = np.isfinite(h4g)
h5g = np.array([26,5417,239,11,23,95]).astype(np.double)
h5gmask = np.isfinite(h5g)


plt.plot(t2[h1gmask], h1g[h1gmask], "o:", markersize=4)
plt.plot(t2[h2gmask], h2g[h2gmask], "o:", markersize=4)
plt.plot(t2[h3gmask], h3g[h3gmask], "o:", markersize=4)
plt.plot(t2[h4gmask], h4g[h4gmask], "o:", markersize=4)
plt.plot(t2[h5gmask], h5g[h5gmask], "o:", markersize=4)
plt.yscale("log")
plt.title("Nombre de branchements en fonction du graphe choisi")
plt.legend(['min_val','max_val','random','supp','dsupp'])
plt.xlabel("Graphe choisi")
plt.ylabel("Nombre de branchements")
plt.show()



t2 = np.arange(6)

h1h = np.array([0.000638,0.036617,0.003463,0.000029,0.000104,0.002353]).astype(np.double)
h1hmask = np.isfinite(h1h)
h2h = np.array([0.000172,0.035449,0.003380,0.000029,0.000103,0.002130]).astype(np.double)
h2hmask = np.isfinite(h2h)
h3h = np.array([0.000143,0.034934,0.003424,0.000031,0.000104,0.002662]).astype(np.double)
h3hmask = np.isfinite(h3h)
h4h = np.array([0.000154,0.037650,0.003406,0.000056,0.000103,0.002289]).astype(np.double)
h4hmask = np.isfinite(h4h)
h5h = np.array([0.000811,0.522236,0.071742,0.000063,0.000408,0.026116]).astype(np.double)
h5hmask = np.isfinite(h5h)

plt.plot(t2[h1hmask], h1h[h1hmask], "o:", markersize=4)
plt.plot(t2[h2hmask], h2h[h2hmask], "o:", markersize=4)
plt.plot(t2[h3hmask], h3h[h3hmask], "o:", markersize=4)
plt.plot(t2[h4hmask], h4h[h4hmask], "o:", markersize=4)
plt.plot(t2[h5hmask], h5h[h5hmask], "o:", markersize=4)
plt.yscale("log")
plt.title("Temps de calcul en fonction du graphe choisi")
plt.legend(['min_val','max_val','random','supp','dsupp'])
plt.xlabel("Graphe choisi")
plt.ylabel("Temps de calcul (en s)")
plt.show()
