from matplotlib import pyplot as plt
from matplotlib import style
import sys
from numpy import genfromtxt
graph  = "../baseline.txt"
graph1 = "outputresolution1.txt"
graph2 = "outputresolution2.txt"
graph3 = "outputresolution3.txt"
graph4 = "outputresolution4.txt"
graph5 = "outputresolution5.txt"
graph10 = "outputresolution10.txt"
graph20 = "outputresolution20.txt"
data= genfromtxt(graph, delimiter=",", names=["x", "y"])
data1= genfromtxt(graph1, delimiter=",", names=["x", "y"])
data2= genfromtxt(graph2, delimiter=",", names=["x", "y"])
data3= genfromtxt(graph3, delimiter=",", names=["x", "y"])
data4= genfromtxt(graph4, delimiter=",", names=["x", "y"])
data5= genfromtxt(graph5, delimiter=",", names=["x", "y"])
data10= genfromtxt(graph10, delimiter=",", names=["x", "y"])
data20= genfromtxt(graph20, delimiter=",", names=["x", "y"])
p1 = plt.plot(data['x'], data['y'],label='Baseline')
p1 = plt.plot(data1['x'], data1['y'],label='outputresolution1')
p1 = plt.plot(data2['x'], data2['y'],label='outputresolution2')
p1 = plt.plot(data3['x'], data3['y'],label='outputresolution3')
p1 = plt.plot(data4['x'], data4['y'],label='outputresolution4')
p1 = plt.plot(data5['x'], data5['y'],label='outputresolution5')
p1 = plt.plot(data10['x'], data10['y'],label='outputresolution10')
p1 = plt.plot(data20['x'], data20['y'],label='outputresolution20')
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