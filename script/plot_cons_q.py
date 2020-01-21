import matplotlib.pyplot as plt
import numpy as np
from statistics import mean, variance, stdev, pstdev

t2 = np.arange(4., 26., 1)

h1e = np.array([27,16,172,43,877,334,976,518,3067,1366,26496,20281,160713,91223,743230,48185,None,179593,None,None,None, None]).astype(np.double)
h1emask = np.isfinite(h1e)
h2e = np.array([27,16,172,43,877,334,976,518,3067,1366,26496,20281,160713,91223,743230,48185,None,179593,None,None,None, None]).astype(np.double)
h2emask = np.isfinite(h2e)
h3e = np.array([6,6,12,8,21,16,29,17,42,32,312,208,1404,813,5569,380,None,1329,None,3727,None,6760]).astype(np.double)
h3emask = np.isfinite(h3e)
h4e = np.array([6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]).astype(np.double)
h4emask = np.isfinite(h4e)

plt.plot(t2[h1emask], h1e[h1emask], "o:", markersize=4)
plt.plot(t2[h2emask], h2e[h2emask], "o:", markersize=4)
plt.plot(t2[h3emask], h3e[h3emask], "o:", markersize=4)
plt.plot(t2[h4emask], h4e[h4emask], "o:", markersize=4)
plt.yscale("log")
plt.title("Nombre de branchements en fonction de la taille de l'instance de n-Reines")
plt.legend(['backtrack','MAC à la racine','MAC','forward checking'])
plt.xlabel("Taille de l'instance de n-Reines")
plt.ylabel("Nombre de branchements")
plt.show()



t2 = np.arange(4., 26., 1)

h1f = np.array([0.000015,0.000020,0.000236,0.000089,0.001342,0.001023,0.002371,0.002487,0.014347,0.007437,0.148728,0.132868,1.272667,0.824917,8.048099,0.592508,None,3.149670,None,None,None,None]).astype(np.double)
h1fmask = np.isfinite(h1f)
h2f = np.array([0.000013,0.000012,0.000147,0.000052,0.001396,0.000885,0.002351,0.001608,0.012132,0.005972,0.158814,0.131573,1.325804,0.876470,8.211434,0.625517,None,3.176926,None,None,None,None]).astype(np.double)
h2fmask = np.isfinite(h2f)
h3f = np.array([0.000045,0.000072,0.000367,0.000392,0.001865,0.001818,0.004438,0.005413,0.011448,0.011833,0.097573,0.082577,0.599555,0.409720,2.936227,0.267910,None,1.040721,None,3.631266,None,8.751230]).astype(np.double)
h3fmask = np.isfinite(h3f)
h4f = np.array([0.000012,0.000012,0.000050,0.000025,0.000263,0.000096,0.000228,0.000147,0.000609,0.000393,0.005507,0.004455,0.034903,0.023129,0.173954,0.012548,1.000657,0.061925,9.234654,0.147900,2.623281,0.335950]).astype(np.double)
h4fmask = np.isfinite(h4f)

plt.plot(t2[h1fmask], h1f[h1fmask], "o:", markersize=4)
plt.plot(t2[h2fmask], h2f[h2fmask], "o:", markersize=4)
plt.plot(t2[h3fmask], h3f[h3fmask], "o:", markersize=4)
plt.plot(t2[h4fmask], h4f[h4fmask], "o:", markersize=4)
plt.yscale("log")
plt.title("Temps de calcul en fonction de la taille de l'instance de n-Reines")
plt.legend(['backtrack','MAC à la racine','MAC','forward checking'])
plt.xlabel("Taille de l'instance de n-Reines")
plt.ylabel("Temps de calcul (en s)")
plt.show()
