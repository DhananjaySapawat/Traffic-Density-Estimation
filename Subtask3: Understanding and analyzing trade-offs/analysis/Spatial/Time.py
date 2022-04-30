from matplotlib import pyplot as plt
from matplotlib import style
from numpy import genfromtxt
graph = "SpatialTime.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'])
plt.legend();
plt.ylabel('Time')
plt.xlabel('No Of Pthread')
savegraph = "PthreadVsTime.png"
plt.savefig(savegraph)
plt.show()