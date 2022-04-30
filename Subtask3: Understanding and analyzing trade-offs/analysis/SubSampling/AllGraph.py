from matplotlib import pyplot as plt
from matplotlib import style
import sys
from numpy import genfromtxt
graph  = "../baseline.txt"
graph1 = "outputsubsampling1.txt"
graph2 = "outputsubsampling2.txt"
graph3 = "outputsubsampling3.txt"
graph4 = "outputsubsampling4.txt"
graph5 = "outputsubsampling5.txt"
graph10 = "outputsubsampling10.txt"
graph20 = "outputsubsampling20.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
data1= genfromtxt(graph1, delimiter=",", names=["x", "y"])
data2= genfromtxt(graph2, delimiter=",", names=["x", "y"])
data3= genfromtxt(graph3, delimiter=",", names=["x", "y"])
data4= genfromtxt(graph4, delimiter=",", names=["x", "y"])
data5= genfromtxt(graph5, delimiter=",", names=["x", "y"])
data10= genfromtxt(graph10, delimiter=",", names=["x", "y"])
data20= genfromtxt(graph20, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'],label='Baseline')
p1 = plt.plot(data1['x'], data1['y'],label='subsampling1')
p1 = plt.plot(data2['x'], data2['y'],label='subsampling2')
p1 = plt.plot(data3['x'], data3['y'],label='subsampling3')
p1 = plt.plot(data4['x'], data4['y'],label='subsampling4')
p1 = plt.plot(data5['x'], data5['y'],label='subsampling5')
p1 = plt.plot(data10['x'], data10['y'],label='subsampling10')
p1 = plt.plot(data20['x'], data20['y'],label='subsampling20')
plt.legend();
plt.ylabel('Density')
plt.xlabel('Time (in Seconds)')

ax2 = plt.twinx()
ymin, ymax = ax2.get_ylim()
ax2.set_ylim(ymin, ymax)
ax2.vlines([98, 278], ymin=ymin, ymax=ymax, color='green', linestyle=':')
ax2.vlines([182, 351], ymin=ymin, ymax=ymax, color='red', linestyle=':')


savegraph = "AllSubsampling.png"
plt.savefig(savegraph)
plt.show()