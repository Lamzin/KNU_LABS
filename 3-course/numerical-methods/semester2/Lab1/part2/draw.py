import numpy as np
import matplotlib.pyplot as plt
from numpy import e, sin, cos, log


file = open('expressions.txt', 'r')
leftBound = float(file.readline())
rightBound = float(file.readline())
origin_expression = file.readline()
approximation1 = file.readline()
approximation2 = file.readline()

n = int(file.readline())
approximations = []
ts = []
for i in range(0, n):
    l = float(file.readline())
    r = float(file.readline())
    s = file.readline()
    ts.append(np.arange(l, r, 0.003))
    approximations.append(s)


def graphic(x, f):
    return eval(f.replace('^', '**').replace('\n', ''))

t = np.arange(leftBound, rightBound, 0.003)

params = [
    t, graphic(t, origin_expression), 'b--',
    # t, graphic(t, approximation1), 'y',
    # t, graphic(t, approximation2), 'r'
]

for i in range(0, n):
    params.append(ts[i])
    params.append(graphic(ts[i], approximations[i]))
    params.append('g')


plt.figure(1)
plt.plot(*params)
plt.show()