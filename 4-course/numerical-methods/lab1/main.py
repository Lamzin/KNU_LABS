# -*- coding: utf-8 -*-


import math
import matplotlib.pyplot as plt
import numpy as np

from methods import Galerkin


def draw(a, b, functions):
    xs = np.arange(a, b, (b - a)/100.)
    ys = [plt.plot(xs, [f(x) for x in xs]) for f in functions]
    plt.show()


def get_task_variable():
    n = 5
    a, b = 0, 5

    m_koef = [2, 1, 1.5, 0.5, 5]
    k_koef = [2, 1, 4]
    q_koef = [2, 1, 4]
    p_koef = [2, 1, 4]
    alpha_koef = [1, 1]

    u = [
        lambda x: m_koef[0]*math.sin(m_koef[1]*x) + m_koef[2]*math.cos(m_koef[3]*x) + m_koef[4],
        lambda x: m_koef[0]*m_koef[1]*math.cos(m_koef[1] * x) - m_koef[2]*m_koef[3]*math.sin(m_koef[3]*x),
        lambda x: -m_koef[0]*m_koef[1]*m_koef[1]*math.sin(m_koef[1]*x) - m_koef[2]*m_koef[3]*m_koef[3]*math.cos(m_koef[3]*x)
    ]

    k = [
        lambda x: k_koef[0] * math.sin(k_koef[1] * x) + k_koef[2],
        lambda x: k_koef[0] * k_koef[1] * math.cos(k_koef[1] * x),
    ]

    q = lambda x: math.cos(q_koef[1]*x) + q_koef[2]
    p = lambda x: p_koef[0]*math.cos(p_koef[1]*x) + p_koef[2]

    f = lambda x: -k[1](x)*u[1](x) - k[0](x)*u[2](x) + p(x)*u[1](x) + q(x)*u[0](x)

    return n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f


if __name__ == "__main__":
    n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f = get_task_variable()

    galerkin = Galerkin(n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f)

    draw(a, b, [u[0], galerkin.solve()])
