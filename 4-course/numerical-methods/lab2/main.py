# -*- coding: utf-8 -*-


import matplotlib.pyplot as plt
import numpy as np

from sympy import *
from scipy import integrate


x = Symbol('x')


def get_task_variable():
    n = 10
    a, b = 0., 1.
    koef = [2., 4., 3., 7., 1.,]

    u = koef[0] * sin(koef[1] * x) + koef[2] * cos(koef[3] * x) + koef[4]
    k = 1. + x**x
    q = 1.
    f = -diff(k * diff(u, x), x) + q * u

    u = lambdify(x, u, 'numpy')
    k = lambdify(x, k, 'numpy')
    q = lambdify(x, q, 'numpy')
    f = lambdify(x, f, 'numpy')

    mu = [u(a), u(b)]
    return n, a, b, u, k, q, f, mu


def a0(k, n, a, b, i):
    delta = (b - a) / (n - 1.)
    xi0 = a + delta * (i - 1)
    xi1 = a + delta * i
    return delta / (integrate.quad(lambda x: 1. / k(x), xi0, xi1, limit=200))[0]


def d0(q, n, a, b, i):
    delta = (b - a) / (n - 1.)
    xi05 = a + delta * (i - 0.5)
    xi15 = a + delta * (i + 0.5)
    return (integrate.quad(q, xi05, xi15, limit=200))[0] / delta


def phi0(f, n, a, b, i):
    delta = (b - a) / (n - 1.)
    xi05 = a + delta * (i - 0.5)
    xi15 = a + delta * (i + 0.5)
    return (integrate.quad(f, xi05, xi15, limit=200))[0] / delta


def draw(a, b, u, u_approximation_points):
    n = len(u_approximation_points)
    h = (b - a) / (n - 1.)
    xs = [a + i * h for i in range(n)]
    plt.plot(xs, [u(x) for x in xs])
    plt.plot(xs, u_approximation_points)
    plt.show()


def main():
    n, a, b, u, k, q, f, mu = get_task_variable()

    matrix = [[0 for j in range(n + 1)]for i in range(n + 1)]
    matrix[0][0] = 1
    matrix[n][n] = 1

    h = (b - a) / (n - 0.)
    for i in range(1, n):
        print(i)
        _ai0 = a0(k, n, a, b, i)
        _ai1 = a0(k, n, a, b, i + 1)
        _di = d0(q, n, a, b, i)
        matrix[i][i - 1] = _ai0 / (h * h)
        matrix[i][i] = (-_ai0 - _ai1) / (h * h) - _di
        matrix[i][i + 1] = _ai1 / (h * h)

    b_array = [0 for i in range(n + 1)]
    b_array[0] = mu[0]
    b_array[n] = mu[1]
    for i in range(1, n):
        print(i)
        _phi0 = phi0(f, n, a, b, i)
        b_array[i] = -_phi0

    c_array = np.linalg.solve(np.array(matrix), np.array(b_array))
    for i in range(n + 1):
        x = a + i * h
        print('{:10.5f}: {:10.5f} | {:10.5f} | {:10.5f}'.format(x, u(x), c_array[i], u(x) - c_array[i]))

    draw(a, b, u, c_array)


if __name__ == "__main__":
    main()
