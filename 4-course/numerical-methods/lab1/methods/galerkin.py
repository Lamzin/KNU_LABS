# -*- coding: utf-8 -*-


import numpy as np
import math

from scipy import integrate

from function import F, X


class Galerkin(object):

    def __init__(s, n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f):
        s.n = n
        s.a = a
        s.b = b
        s.m_koef = m_koef
        s.k_koef = k_koef
        s.q_koef = q_koef
        s.p_koef = p_koef
        s.alpha_koef = alpha_koef
        s.u = u
        s.k = k
        s.p = p
        s.q = q
        s.f = f

        s.__init_mu__()
        s.__init_psi__()
        s.__init_v__()
        s.__init_phi__()

    def __init_mu__(s):
        s.mu = [
            (-s.k[0]*s.u[1] + s.alpha_koef[0]*s.u[0])(s.a),
            (s.k[0]*s.u[1] + s.alpha_koef[1]*s.u[0])(s.b)
        ]

    def __init_psi__(s):
        s.psi_koef_a = (s.alpha_koef[1]*s.mu[0] - s.alpha_koef[0]*s.mu[1]) / \
                          (s.alpha_koef[1]*(-s.k[0](s.a) + s.a*s.alpha_koef[0]) -
                           s.alpha_koef[0]*(s.k[0](s.b) + s.b*s.alpha_koef[1]))
        s.psi_koef_b = (s.mu[1] - s.psi_koef_a*(s.k[0](s.b) + s.b*s.alpha_koef[1])) / s.alpha_koef[1]
        s.psi = s.psi_koef_a*X + s.psi_koef_b

    def __init_v__(s):
        s.v = [
            s.u[0] - s.psi,
            s.u[1] - s.psi_koef_a,
            s.u[2]
        ]
        s.Av = -s.k[1]*s.v[1] - s.k[0]*s.v[2] + s.p*s.v[1] + s.q*s.v[0]

    def __init_phi__(s):
        s.phi_koef_a = s.k[0](s.b) * (s.b - s.a) / \
                          (2*s.k[0](s.b) + s.alpha_koef[1]*(s.b-s.a)) + \
                          s.b
        s.phi_koef_b = s.a - s.k[0](s.a) * (s.b - s.a) / (2*s.k[0](s.a) + s.alpha_koef[0]*(s.b-s.a))

        s.phi = [[
            (X - s.a)**2 * (X - s.phi_koef_a),
            (X - s.a)**2 + 2*(X - s.a)*(X - s.phi_koef_a),
            2*(X - s.a) + 2*(X - s.phi_koef_a) + 2*(X - s.a)
        ]] + \
        [[
            (s.b - X)**2 * (s.phi_koef_b - X),
            -(s.b - X)**2 - 2 * (s.b - X) * (s.phi_koef_b - X),
            2*(s.b - X) + 2*(s.b - X) + 2*(s.phi_koef_b - X)
        ]] + \
        [
            [
                (X - s.a)**2 * (s.b - X)**(i - 1),
                2*(X - s.a) * (s.b - X)**(i - 1) - (i - 1) * (X - s.a)**2 * (s.b - X)**(i - 2),
                2*(s.b - X)**(i - 1) - 2*(i - 1)*(X - s.a)*(s.b - X)**(i - 2) + (i - 1)*(i - 2)*(X - s.a)*(X - s.a)*(s.b - X)**(i - 3) - 2*(i - 1)*(X - s.a)*(s.b - X)**(i - 2)
            ]
            for i in range(3, s.n + 1)
        ]

        s.A_phi = lambda i: -s.k[1]*s.phi[i][1] - s.k[0]*s.phi[i][2] + s.p*s.phi[i][1] + s.q*s.phi[i][0]

    def solve(s):
        matrix = [
            [
                (integrate.quad(s.A_phi(j)*s.phi[i][0], s.a, s.b))[0]
                for j in range(s.n)
            ]
            for i in range(s.n)
        ]
        b = [
            (integrate.quad(s.Av*s.phi[i][0], s.a, s.b))[0]
            for i in range(s.n)
        ]
        c = np.linalg.solve(np.array(matrix), np.array(b))

        u_approximation = lambda x: sum([c[i] * s.phi[i][0](x) for i in range(s.n)]) + s.psi(x)
        return u_approximation
