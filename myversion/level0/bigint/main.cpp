#include "bigint2.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
	bigint b(21), c, d(1337), e(d);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
	bigint a2(12);
	bigint b2(0);
	std::cout << "a1 + b1 = " << a2 + b2 << std::endl;
    // std::cout << "(c += a) = " << (c += a) << std::endl;

    // std::cout << "b = " << b << std::endl;
    // std::cout << "++b = " << ++b << std::endl;
	// bigint z(b++);
	// std::cout << "b = " << z << std::endl;
    // std::cout << "b++ = " << b++ << std::endl;

    // std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    // std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    // std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    // std::cout << "a =" << a << std::endl;
    // std::cout << "d =" << d << std::endl;

    // std::cout << "(d < a) = " << (d < a) << std::endl;
    // std::cout << "(d <= a) = " << (d <= a) << std::endl;
    // std::cout << "(d > a) = " << (d > a) << std::endl;
    // std::cout << "(d >= a) = " << (d >= a) << std::endl;
    // std::cout << "(d == a) = " << (d == a) << std::endl;
    // std::cout << "(d != a) = " << (d != a) << std::endl;
}


// #include <limits.h>
// int main()
// {
// 	// std::cout << "MAX_INT: " << INT_MAX << std::endl;
//     bigint a1(5051);
//     bigint b1(9000);
//     std::cout << "5051 + 9000 = " << a1 + b1 << std::endl; // 14051

//     bigint a2(1);
//     bigint b2(9);
//     std::cout << "1 + 9 = " << a2 + b2 << std::endl; // 10

//     bigint a3(99);
//     bigint b3(1);
//     std::cout << "99 + 1 = " << a3 + b3 << std::endl; // 100

//     bigint a4(999);
//     bigint b4(1);
//     std::cout << "999 + 1 = " << a4 + b4 << std::endl; // 1000

//     bigint a5(1234);
//     bigint b5(8766);
//     std::cout << "1234 + 8766 = " << a5 + b5 << std::endl; // 10000

//     bigint a6(0);
//     bigint b6(0);
//     std::cout << "0 + 0 = " << a6 + b6 << std::endl; // 0

//     bigint a7(5000);
//     bigint b7(5);
//     std::cout << "5000 + 5 = " << a7 + b7 << std::endl; // 5005

//     bigint a8(42);
//     bigint b8(58);
//     std::cout << "42 + 58 = " << a8 + b8 << std::endl; // 100

//     bigint a9(999999);
//     bigint b9(1);
//     std::cout << "999999 + 1 = " << a9 + b9 << std::endl; // 1000000

//     bigint a10(1000000);
//     bigint b10(999999);
//     std::cout << "1000000 + 999999 = " << a10 + b10 << std::endl; // 1999999

// 	bigint a11(9999);
// 	bigint b11(1111);
// 	std::cout << "9999 + 1111 = " << a11 + b11 << std::endl; // 11110

// 	// 

// 	std::cout << "BIGINT" << std::endl;
// 	bigint a12(__INT_MAX__);
// 	bigint b12(2);
// 	std::cout << "2147483647 + 2 = " << a12 + b12 << std::endl;

// 	std::cout << "INT" << std::endl;
// 	int a = __INT_MAX__;
// 	int b = 2;
// 	std::cout << "2147483647 + 2 = " << a + b << std::endl;
// }

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


a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 220000000042
(d <<= 4) = 13370000
(d >>= 2) = 133700
a =42
d =133700
(d < a) = 0
(d <= a) = 0
(d > a) = 1
(d >= a) = 1
(d == a) = 0
(d != a) = 1*/