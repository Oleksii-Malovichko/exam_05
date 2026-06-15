#include "bigint2.hpp"

int main(void)
{
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);

	// base test
	std::cout << "a = " << a << std::endl; // 42
	std::cout << "b = " << b << std::endl; // 21
	std::cout << "c = " << c << std::endl; // 0
	std::cout << "d = " << d << std::endl; // 1337
	std::cout << "e = " << e << std::endl; // 1337

	std::cout << "a + b = " << a + b << std::endl; // 63
	std::cout << "a + c = " << a + c << std::endl; // 42
	std::cout << "(c += a) = " << (c += a) << std::endl; // 42

	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;

	// b = 23, b << 10 -> 23000000000 + 42 = 230000000042
	std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << ", d: " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << ", d: " << d << std::endl;

	std::cout << "a = " << a << std::endl; // a = 42
	std::cout << "d = " << d << std::endl; // d = 5348
	
	std::cout << "(d < a) = " << (d < a) << std::endl; // (d < a) = 0
	std::cout << "(d > a) = " << (d > a) << std::endl; // (d > a) = 1
	std::cout << "(d == d) = " << (d == d) << std::endl; // (d == d) = 1
	std::cout << "(d != a) = " << (d != a) << std::endl; // (d != a) = 1
	std::cout << "(d <= a) = " << (d <= a) << std::endl; // (d <= a) = 0
	std::cout << "(d >= a) = " << (d >= a) << std::endl; // (d >= a) = 1

	// extra
	bigint x(12345678); bigint y(5);
	std::cout << "(x << y) = " << (x << y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >>= y) = " << (x >>= y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	std::cout << "x= " << (x <<= 5) << ", y= " << (y <<= 12) << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	std::cout << "My tests:\n";
	bigint x1(0), z1(5);
	std::cout << (x1 << z1) << std::endl; // 00000

	std::cout << "My tests (chatgpt)" << std::endl;
	std::cout << bigint(999) + bigint(1) << std::endl;
	std::cout << (bigint(42) >> 2) << std::endl;
	std::cout << (bigint(42) >> 3) << std::endl;
	std::cout << (bigint(0) << 10) << std::endl;
	std::cout << (bigint(13) >= bigint(42)) << std::endl;
	return (0);
}

/* 
a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
a + c = 42
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 230000000042
(d <<= 4) = 13370000, d: 13370000
(d >>= 2) = 133700, d: 133700
a = 42
d = 133700
(d < a) = 0
(d > a) = 1
(d == d) = 1
(d != a) = 1
(d <= a) = 0
(d >= a) = 1
(x << y) = 1234567800000, x: 12345678, y: 5
(x >>= y) = 123, x: 123, y: 5
(x >= y) = 1, x: 123, y: 5
x= 12300000, y= 5000000000000
(x >= y) = 0, x: 12300000, y: 5000000000000
My tests:
0
My tests (chatgpt)
1000
0
0
0
0

a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
a + c = 42
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 230000000042
(d <<= 4) = 13370000, d: 13370000
(d >>= 2) = 133700, d: 133700
a = 42
d = 133700
(d < a) = 0
(d > a) = 1
(d == d) = 1
(d != a) = 1
(d <= a) = 0
(d >= a) = 1
(x << y) = 1234567800000, x: 12345678, y: 5
(x >>= y) = 123, x: 123, y: 5
(x >= y) = 1, x: 123, y: 5
x= 12300000, y= 5000000000000
(x >= y) = 0, x: 12300000, y: 5000000000000
My tests:
0
My tests (chatgpt)
1000
0
0
0
0
*/
