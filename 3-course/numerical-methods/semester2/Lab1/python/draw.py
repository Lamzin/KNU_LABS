import numpy as np
import matplotlib.pyplot as plt
from numpy import e, sin, cos, log

origin_expression = '1.000000 * log(x) + 1.000000 * cos(0.500000 * x)'

approximation_expression = ' + (0.240838)*(e^(0*x)) + (0.350893)*(e^(1*x)) + (-0.043723)*(e^(2*x)) + (0.002305)*(e^(3*x)) + (-0.000044)*(e^(4*x))'


def origin(x):
    print type(x)
    return eval(origin_expression.replace('^', '**'))

def approximation(x):
    return eval(approximation_expression.replace('^', '**'))


def normalize_expression(s):
    return s.replace('^', '**').replace('e', 'numpy.e').replace('log', 'numpy.log').replace('sin', 'numpy.sin').replace('cos', 'numpy.cos')

print normalize_expression(approximation_expression)
print normalize_expression(origin_expression)

t = np.arange(1.0, 3.0, 0.01)

plt.figure(1)
plt.plot(t, origin(t), 'g', t, approximation(t), 'y')
plt.show()