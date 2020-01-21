import matplotlib.pyplot as plt
import numpy as np
from statistics import mean, variance, stdev, pstdev

t2 = np.arange(7)

h1g = np.array([96,198022,5146,23,50,105,216]).astype(np.double)
h1gmask = np.isfinite(h1g)
h2g = np.array([96,198022,5146,23,50,105,216]).astype(np.double)
h2gmask = np.isfinite(h2g)
h3g = np.array([26,627,75,12,24,48,96]).astype(np.double)
h3gmask = np.isfinite(h3g)
h4g = np.array([26,5417,239,11,23,47,95]).astype(np.double)
h4gmask = np.isfinite(h4g)

plt.plot(t2[h1gmask], h1g[h1gmask], "o:", markersize=4)
plt.plot(t2[h2gmask], h2g[h2gmask], "o:", markersize=4)
plt.plot(t2[h3gmask], h3g[h3gmask], "o:", markersize=4)
plt.plot(t2[h4gmask], h4g[h4gmask], "o:", markersize=4)
plt.yscale("log")
plt.title("Nombre de branchements en fonction du graphe choisi")
plt.legend(['backtrack','MAC à la racine','MAC','forward checking'])
plt.xlabel("Graphe choisi")
plt.ylabel("Nombre de branchements")
plt.show()



t2 = np.arange(7)

h1h = np.array([0.006513,7.655711,0.207228,0.000066,0.000645,0.006911,0.051676]).astype(np.double)
h1hmask = np.isfinite(h1h)
h2h = np.array([0.001302,7.503747,0.219145,0.000041,0.000429,0.005321,0.028921]).astype(np.double)
h2hmask = np.isfinite(h2h)
h3h = np.array([0.007773,0.484858,0.130803,0.000580,0.005025,0.046757,0.360347]).astype(np.double)
h3hmask = np.isfinite(h3h)
h4h = np.array([0.000173,0.035371,0.003409,0.000029,0.000103,0.000451,0.002160]).astype(np.double)
h4hmask = np.isfinite(h4h)

plt.plot(t2[h1hmask], h1h[h1hmask], "o:", markersize=4)
plt.plot(t2[h2hmask], h2h[h2hmask], "o:", markersize=4)
plt.plot(t2[h3hmask], h3h[h3hmask], "o:", markersize=4)
plt.plot(t2[h4hmask], h4h[h4hmask], "o:", markersize=4)
plt.yscale("log")
plt.title("Temps de calcul en fonction du graphe choisi")
plt.legend(['backtrack','MAC à la racine','MAC','forward checking'])
plt.xlabel("Graphe choisi")
plt.ylabel("Temps de calcul (en s)")
plt.show()