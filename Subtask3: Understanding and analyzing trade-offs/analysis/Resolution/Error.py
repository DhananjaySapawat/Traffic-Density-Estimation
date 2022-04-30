from matplotlib import pyplot as plt
from matplotlib import style
from numpy import genfromtxt
graph = "ResolutionError.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'])
plt.legend();
plt.ylabel('Error')
plt.xlabel('Factor')
savegraph = "FactorVsError.png"
plt.savefig(savegraph)
plt.show()