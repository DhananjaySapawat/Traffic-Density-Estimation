from matplotlib import pyplot as plt
from matplotlib import style
from numpy import genfromtxt
graph = "SubsamplingError.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'])
plt.legend();
plt.ylabel('Error')
plt.xlabel('FrameDrop')
savegraph = "FrameDropVsError.png"
plt.savefig(savegraph)
plt.show()