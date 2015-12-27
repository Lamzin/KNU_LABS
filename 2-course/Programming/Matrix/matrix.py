from __future__ import print_function
from fractions import Fraction
import logging

class MatrixInputError(Exception):
    pass


class Matrix(object):

    def __init__(self, T):
        self.type = T
        self.matrix = []

    def read(self):
        try:
            n = int(raw_input())
            for i in range(n):
                self.matrix.append([self.type(x) for x in raw_input().split()])
                if len(self.matrix[-1]) != n:
                    raise MatrixInputError
        except Exception as e:
            logging.error(e, exc_info=True)
            self.matrix = []

    @property
    def size(self):
        return len(self.matrix)

    def write(self):
        for line in self.matrix:
            for element in line:
                print(element, end=" ")
            print(end="\n")

    def reverse(self):
        E = Matrix(self.type)
        E.matrix = [
            [self.type(1 if i == j else 0) for j in range(self.size)]
            for i in range(self.size)]

        for i in range(self.size):
            if self.matrix[i][i] == self.type(0):
                return Matrix(self.type)
            k = self.matrix[i][i]
            for j in range(self.size):
                self.matrix[i][j] /= k
                E.matrix[i][j]    /= k
            for ii in range(self.size):
                if ii == i:
                    continue
                kk = self.matrix[ii][i]
                for jj in range(self.size):
                    self.matrix[ii][jj] -= self.matrix[i][jj] * kk
                    E.matrix[ii][jj]    -= E.matrix[i][jj]    * kk
        return E


if __name__ == "__main__":
    A = Matrix(Fraction)
    A.read()
    A.write()
    E = A.reverse()
    if E:
        E.write()


