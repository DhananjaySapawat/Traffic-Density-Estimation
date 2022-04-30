from matplotlib import pyplot as plt
from matplotlib import style
import sys
from numpy import genfromtxt
graph = sys.argv[1]
if(graph[6:8]=="su"):
 graph = "/home/dhananjay/Desktop/Assignment1/analysis/SubSampling/"+graph
else:
 graph = "/home/dhananjay/Desktop/Assignment1/analysis/Resolution/"+graph
data1 = genfromtxt(graph, delimiter=",", names=["x", "y"])

p1 = plt.plot(data1['x'], data1['y'],label='Queue Density')
plt.legend();
plt.ylabel('Density')
plt.xlabel('Time (in Seconds)')

ax2 = plt.twinx()
ymin, ymax = ax2.get_ylim()
ax2.set_ylim(ymin, ymax)
ax2.vlines([98, 278], ymin=ymin, ymax=ymax, color='green', linestyle=':')
ax2.vlines([182, 351], ymin=ymin, ymax=ymax, color='red', linestyle=':')


savegraph = graph[:-3]+"png"
plt.savefig(savegraph)
plt.show()