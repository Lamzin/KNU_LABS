//https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format


#include <iostream>

using namespace std;


typedef long double f64;
typedef long long i64;
typedef unsigned long long u64;


const u64 h = 11, m = 21;


u64 get_bit(u64 x, u64 n) {
	return ((x & ((u64)1 << n))) ? 1 : 0;
}


void print(f64 y) {
	u64 x = *(u64 *)&y;

	cout << "x:        " << y;
	cout << endl;
	cout << "xx:       " << x;
	cout << endl;

	cout << "sign:     " << get_bit(x, 63);
	cout << endl;

	cout << "exponent: ";
	for (int i = 62; i > 51; i--) cout << get_bit(x, i);
	cout << endl;

	cout << "fraction: ";
	for (int i = 51; i > 0; i--) cout << get_bit(x, i);
	cout << endl;
}



int main() {

	f64 x;
	cout << "x = ";
	cin >> x;

	print(x);

	cin.get();
	cin.get();

	return 0;
}