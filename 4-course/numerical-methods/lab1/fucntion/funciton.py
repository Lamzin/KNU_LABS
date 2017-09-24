# -*- coding: utf-8 -*-


class Function(object):

    def __init__(self, f):
        self.f = f

    def __add__(self, g):
        return self.__helper__(g, lambda x, y: x + y)

    def __sub__(self, g):
        return self.__helper__(g, lambda x, y: x - y)

    def __mul__(self, g):
        return self.__helper__(g, lambda x, y: x * y)

    def __div__(self, g):
        return self.__helper__(g, lambda x, y: x / y)

    def __call__(self, x):
        if hasattr(self.f, '__call__'):
            return self.f(x)
        return self.f

    def __helper__(self, g, operator):
        if hasattr(g, '__call__'):
            return Function(lambda x, f=self.f: operator(f(x), g(x)))
        return Function(lambda x, f=self.f: operator(f(x), g))



if __name__ == "__main__":
    f = Function(lambda x: x)
    g = Function(lambda x: 2*x)

    x = 9
    print(f(x))
    print((f + g)(x))
    print((f - g)(x))
    print((f * g)(x))
    print((f / g)(x))
