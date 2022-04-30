from matplotlib import pyplot as plt
from matplotlib import style
from numpy import genfromtxt
graph = "SubsamplingTime.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'])
plt.legend();
plt.ylabel('Time')
plt.xlabel('FrameDrop')
savegraph = "FrameDropVsTime.png"
plt.savefig(savegraph)
plt.show()