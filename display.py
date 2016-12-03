import sys
content = open(sys.argv[1], 'r').read()
vectors = content.split('\n')
del vectors[-1]


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

i = 0
while i < len(vectors):
    v1 = map(lambda x: float(x), vectors[i].split(" "))
    v2 = map(lambda x: float(x), vectors[i + 1].split(" "))
    ax.plot([v1[0], v2[0]], [v1[1], v2[1]], zs = [v1[2], v2[2]]);
    i += 2

plt.show()



