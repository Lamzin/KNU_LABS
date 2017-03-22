import numpy as np
import matplotlib.pyplot as plt
from numpy import e, sin, cos, log


file = open('expressions.txt', 'r')
leftBound = float(file.readline())
rightBound = float(file.readline())
origin_expression = file.readline()
approximation1 = file.readline()
approximation2 = file.readline()


def graphic(x, f):
    return eval(f.replace('^', '**').replace('\n', ''))

t = np.arange(leftBound, rightBound, 0.01)

plt.figure(1)
plt.plot(
    t, graphic(t, origin_expression), 'g', 
    t, graphic(t, approximation1), 'y', 
    t, graphic(t, approximation2), 'r' 
)
plt.show()