# -*- coding: utf-8 -*-


import matplotlib.pyplot as plt
import numpy as np


from methods import Galerkin
from function import F, sin, cos, X


def draw(a, b, functions):
    xs = np.arange(a, b, (b - a)/100.)
    ys = [plt.plot(xs, [f(x) for x in xs]) for f in functions]
    plt.show()


def get_task_variable():
    n = 5
    a, b = 0, 5

    m_koef = [2., 1., 1.5, 0.5, 5.]
    k_koef = [2., 1., 4.]
    q_koef = [2., 1., 4.]
    p_koef = [2., 1., 4.]
    alpha_koef = [1., 1.]

    u = [
        m_koef[0]*sin(m_koef[1]*X) + m_koef[2]*cos(m_koef[3]*X) + m_koef[4],
        m_koef[0]*m_koef[1]*cos(m_koef[1]*X) - m_koef[2]*m_koef[3]*sin(m_koef[3]*X),
        -m_koef[0]*m_koef[1]*m_koef[1]*sin(m_koef[1]*X) - m_koef[2]*m_koef[3]*m_koef[3]*cos(m_koef[3]*X)
    ]

    k = [
        k_koef[0] * sin(k_koef[1] * X) + k_koef[2],
        k_koef[0] * k_koef[1] * cos(k_koef[1] * X),
    ]

    q = cos(q_koef[1]*X) + q_koef[2]
    p = p_koef[0]*cos(p_koef[1]*X) + p_koef[2]

    f = -k[1]*u[1] - k[0]*u[2] + p*u[1] + q*u[0]

    return n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f


if __name__ == "__main__":
    n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f = get_task_variable()

    galerkin = Galerkin(n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f)

    draw(a, b, [u[0], galerkin.solve()])
