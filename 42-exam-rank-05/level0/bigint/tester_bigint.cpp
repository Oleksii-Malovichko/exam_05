#include "bigint2.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

static int tests_passed = 0;
static int tests_failed = 0;

void report(bool ok, const std::string &msg)
{
    if (ok)
        tests_passed++;
    else
    {
        tests_failed++;
        std::cout << "❌ FAIL: " << msg << std::endl;
    }
}

// ===================== HELPERS =====================

std::string normalize(const std::string &s)
{
    size_t i = 0;
    while (i + 1 < s.size() && s[i] == '0')
        i++;
    return s.substr(i);
}

bigint to_bigint_from_ull(unsigned long long v)
{
    return bigint(v);
}

// ===================== ADD =====================

void test_add(unsigned long long a, unsigned long long b)
{
    bigint x(a), y(b);
    bigint res = x + y;

    unsigned long long expected = a + b;

    report(res.getStr() == std::to_string(expected),
           "add: " + std::to_string(a) + " + " + std::to_string(b));
}

// ===================== ADD ASSIGN =====================

void test_add_assign(unsigned long long a, unsigned long long b)
{
    bigint x(a), y(b);
    x += y;

    unsigned long long expected = a + b;

    report(x.getStr() == std::to_string(expected),
           "add_assign");
}

// ===================== INCREMENT =====================

void test_increment(unsigned long long a)
{
    bigint x(a);

    bigint pre = ++x;
    report(pre.getStr() == std::to_string(a + 1), "pre-increment");

    bigint post = x++;
    report(post.getStr() == std::to_string(a + 1), "post-increment");

    report(x.getStr() == std::to_string(a + 2), "post value");
}

// ===================== SHIFT =====================

void test_shift(unsigned long long a, unsigned int n)
{
    bigint x(a);

    bigint l = x << n;
    bigint r = x >> n;

    // expected mathematically
    std::string expected_l = std::to_string(a);
    expected_l.append(n, '0');

    unsigned long long expected_r = a;
    for (unsigned int i = 0; i < n; i++)
        expected_r /= 10;

    // normalize expected left (remove leading zeros if any)
    std::string norm_l = normalize(expected_l);

    report(l.getStr() == norm_l, "left shift");
    report(r.getStr() == std::to_string(expected_r), "right shift");
}

// ===================== SHIFT ASSIGN =====================

void test_shift_assign(unsigned long long a, unsigned int n)
{
    bigint x(a);
    bigint y = x;

    x <<= n;
    y = y << n;

    report(x.getStr() == y.getStr(), "shift assign <<=");

    x >>= n;
    y = y >> n;

    report(x.getStr() == y.getStr(), "shift assign >>=");
}

// ===================== COMPARE =====================

void test_compare(unsigned long long a, unsigned long long b)
{
    bigint x(a), y(b);

    report((x < y) == (a < b), "operator <");
    report((x > y) == (a > b), "operator >");
    report((x == y) == (a == b), "operator ==");
    report((x != y) == (a != b), "operator !=");
    report((x <= y) == (a <= b), "operator <=");
    report((x >= y) == (a >= b), "operator >=");
}

// ===================== ZERO =====================

void test_zero()
{
    bigint a(0), b(0);

    report((a + b).getStr() == "0", "zero add");
    report((a << 5).getStr() == "0", "zero shift <<");
    report((a >> 5).getStr() == "0", "zero shift >>");
}

// ===================== BIG TEST =====================

void big_test()
{
    bigint a(1);

    for (int i = 0; i < 500; i++)
        a = a << 1;

    bigint b = a + a;

    report(b.getStr().size() > 0, "big test size check");
}

// ===================== MAIN =====================

int main()
{
    std::cout << "START TESTS\n";

    test_zero();

    for (unsigned long long i = 0; i < 2000; i++)
    {
        if (i % 200 == 0)
            std::cout << "progress i=" << i << std::endl;

        for (unsigned long long j = 0; j < 2000; j += 211)
        {
            test_add(i, j);
            test_add_assign(i, j);
            test_compare(i, j);
        }

        test_increment(i);

        for (unsigned int n = 0; n < 6; n++)
        {
            test_shift(i, n);
            test_shift_assign(i, n);
        }
    }

    big_test();

    std::cout << "\n===== RESULT =====\n";
    std::cout << "Passed: " << tests_passed << "\n";
    std::cout << "Failed: " << tests_failed << "\n";

    int total = tests_passed + tests_failed;
    double score = total ? (100.0 * tests_passed / total) : 0;

    std::cout << "Score: " << score << "%\n";

    return (tests_failed == 0) ? 0 : 1;
}