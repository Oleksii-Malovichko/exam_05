#include "bigint.hpp"

/* 
полностью выучить .hpp файл, затем начинать работать с .cpp */

bigint::bigint()
{
	this->str = "0";
}

bigint::bigint(unsigned int num)
{
	std::stringstream tmp;
	tmp << num;
	this->str = tmp.str();
}

bigint::bigint(const bigint &other)
{
	*this = other;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		this->str = other.str;
	}
	return *this;
}

const std::string &bigint::getStr() const
{
	return this->str;
}

void reverse(std::string &s)
{
	std::string tmp;

	int i = static_cast<int>(s.length()) - 1;
	while (i >= 0)
	{
		tmp += s[i];
		i--;
	}
	s = tmp;
}

std::string addition(const bigint obj1, const bigint obj2)
{
	std::string r;
	std::string s1 = obj1.getStr();
	std::string s2 = obj2.getStr();

	// std::cout << "[BEFORE] s1: " << s1 << std::endl;
	// std::cout << "[BEFORE] s2: " << s2 << std::endl;
	reverse(s1);
	reverse(s2);

	// std::cout << "[AFTER] s1: " << s1 << std::endl;
	// std::cout << "[AFTER] s2: " << s2 << std::endl;

	size_t len1 = s1.size();
	size_t len2 = s2.size();

	if (len1 > len2)
	{
		int diff = len1 - len2;
		while (diff > 0)
		{
			s2.push_back('0');
			diff--;
		}
	}
	if (len2 > len1)
	{
		int diff = len2 - len1;
		while (diff > 0)
		{
			s1.push_back('0');
			diff--;
		}
	}
	// std::cout << "[AFTER] s1: " << s1 << std::endl;
	// std::cout << "[AFTER] s2: " << s2 << std::endl;
	
	int carry = 0;
	int digit1 = 0;
	int digit2 = 0;
	size_t i = 0;
	size_t len = s1.length();
	while (i < len)
	{
		digit1 = s1[i] - '0';
		digit2 = s2[i] - '0';
		int result = digit1 + digit2 + carry;
		carry = result / 10;
		r.push_back((result % 10) + '0');
		i++;
	}
	if (carry != 0)
		r.push_back(carry + '0');

	reverse(r);
	return r;
}

bigint bigint::operator+(const bigint &other) const
{
	bigint result;
	std::string r = addition(*this, other);
	result.str = r;
	return result;
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++()
{
	*this = *this + 1;
	return *this;
}

bigint bigint::operator++(int)
{
	bigint old(*this);
	*this = *this + 1;
	return old;
}

// output
std::ostream &operator<<(std::ostream &os, const bigint &obj)
{
	os << obj.getStr();
	return os;
}