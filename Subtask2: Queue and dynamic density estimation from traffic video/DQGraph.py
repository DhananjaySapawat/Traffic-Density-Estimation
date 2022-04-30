from matplotlib import pyplot as plt
from matplotlib import style

import pandas as pd

data = pd.read_csv('out.txt',sep=',',header=None)
data = pd.DataFrame(data)
t = data[0]
x = data[1]
y = data[2]

p1 = plt.plot(t,x,label='Queue Density')
p2 = plt.plot(t,y,label='Dynamic Density')
plt.legend();
plt.ylabel('Density')
plt.xlabel('Time (in Seconds)')

ax2 = plt.twinx()
ymin, ymax = ax2.get_ylim()
ax2.set_ylim(ymin, ymax)
ax2.vlines([98, 278], ymin=ymin, ymax=ymax, color='green', linestyle=':')
ax2.vlines([182, 351], ymin=ymin, ymax=ymax, color='red', linestyle=':')
savegraph  = "QueueDensityVsDynamicDensity.png"
plt.savefig(savegraph )
plt.show()
a = False
