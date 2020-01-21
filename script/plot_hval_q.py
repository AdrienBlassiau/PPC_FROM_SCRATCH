import matplotlib.pyplot as plt
import numpy as np
from statistics import mean, variance, stdev, pstdev

## HVAR Q

t1 = np.arange(4., 26., 1)

h1a  = [0.000054,0.000060,0.000219,0.000121,0.000817,0.000420,0.001006,0.000320,0.000823,0.000409,0.005720,0.004519,0.035852,0.022784,0.172694,0.015400,0.946574,0.044666,9.253148,0.150800,2.586551,0.333891]
h2a  = [0.000013,0.000012,0.000049,0.000024,0.000175,0.000094,0.000229,0.000148,0.000607,0.000356,0.005531,0.004451,0.034466,0.023264,0.175218,0.012392,0.948906,0.045069,9.355007,0.150084,2.636359,0.380820]
h3a  = [0.000013,0.000013,0.000049,0.000025,0.000174,0.000135,0.000228,0.000150,0.000655,0.000359,0.005516,0.004440,0.034385,0.023328,0.180399,0.012414,1.053826,0.050820,9.203361,0.153319,2.632579,0.344389]
h4a  = [0.000012,0.000011,0.000065,0.000024,0.000176,0.000095,0.000227,0.000179,0.000644,0.000363,0.005991,0.004551,0.034622,0.022996,0.183296,0.013247,0.983752,0.044865,9.354257,0.150303,2.678401,0.342694]
h5a  = [0.000021,0.000020,0.000114,0.000050,0.000596,0.000314,0.001081,0.000651,0.003577,0.002224,0.040131,0.035219,0.305199,0.188494,1.549811,0.114114,8.881329,0.436948,101.276123,1.605790,27.035839,3.989814]

fig, ax = plt.subplots()

plt.plot(t1,h1a, "o:", markersize=4)
plt.plot(t1,h2a, "o:", markersize=4)
plt.plot(t1,h3a, "o:", markersize=4)
plt.plot(t1,h4a, "o:", markersize=4)
plt.plot(t1,h5a, "o:", markersize=4)
plt.yscale("log")
plt.title("Temps de calcul en fonction de la taille de l'instance de n-Reines")
plt.legend(['min_val','max_val','random','supp','dsupp'])
plt.xlabel("Taille de l'instance de n-Reines")
plt.ylabel("Temps de calcul (en s)")
plt.show()


h1b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]
h2b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]
h3b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]
h4b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]
h5b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]
h6b = [6,5,19,7,53,21,53,24,111,54,875,605,4378,2488,17625,1116,84400,3449,703200,10128,167430,19096]

plt.plot(t1, h1b, "o:", markersize=4)
plt.plot(t1, h2b, "o:", markersize=4)
plt.plot(t1, h3b, "o:", markersize=4)
plt.plot(t1, h4b, "o:", markersize=4)
plt.plot(t1, h5b, "o:", markersize=4)
plt.plot(t1, h6b, "o:", markersize=4)
plt.yscale("log")
plt.title("Nombre de branchements en fonction de la taille de l'instance de n-Reines")
plt.legend(['min_val','max_val','random','supp','dsupp'])
plt.xlabel("Taille de l'instance de n-Reines")
plt.ylabel("Nombre de branchements")
plt.show()