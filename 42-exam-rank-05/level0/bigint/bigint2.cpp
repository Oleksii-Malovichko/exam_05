#include "bigint2.hpp"

bigint::bigint() : str("0") {}

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	this->str = ss.str();
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

std::string bigint::getStr() const
{
	return this->str;
}

std::string reverse(const std::string &s)
{
	int i = static_cast<int>(s.size()) - 1;
	std::string r;
	while (i >= 0)
	{
		r += s[i];
		i--;
	}
	return r;
}

std::string addition(const bigint &obj1, const bigint &obj2)
{
	std::string s1 = reverse(obj1.getStr());
	std::string s2 = reverse(obj2.getStr());
	std::string result;
	size_t len1 = s1.size();
	size_t len2 = s2.size();

	if (len1 > len2)
	{
		int diff = len1 - len2;
		while (diff > 0)
		{
			s2 += '0';
			diff--;
		}
	}
	else if (len2 > len1)
	{
		int diff = len2 - len1;
		while (diff > 0)
		{
			s1 += '0';
			diff--;
		}
	}

	int num1;
	int num2;
	int carry = 0;
	size_t len = s1.size();
	size_t i = 0;
	while (i < len)
	{
		num1 = s1[i] - '0';
		num2 = s2[i] - '0';
		int r = num1 + num2 + carry;
		carry = r / 10;
		result.push_back((r % 10) + '0');
		i++;
	}
	if (carry != 0)
		result.push_back(carry + '0');
	return reverse(result);
}

bigint bigint::operator+(const bigint &other) const
{
	bigint tmp;
	std::string res = addition(*this, other);
	tmp.str = res;
	return tmp;
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint old(*this);
	*this = *this + bigint(1);
	return old;
}

bigint bigint::operator<<(unsigned int n) const
{
	bigint tmp(*this);
	tmp.str.insert(tmp.str.size(), n, '0');
	return tmp;
}

bigint bigint::operator>>(unsigned int n) const
{
	bigint tmp(*this);
	if (n >= tmp.str.size())
	{
		tmp.str = "0";
	}
	else
		tmp.str.erase(tmp.str.size() - n);
	return tmp;
}

bigint &bigint::operator<<=(unsigned int n)
{
	*this = *this << n;
	return *this;
}

bigint &bigint::operator>>=(unsigned int n)
{
	*this = *this >> n;
	return *this;	
}

unsigned int stringToUint(const std::string &s)
{
	std::stringstream ss;
	ss << s;
	unsigned int r;
	ss >> r;
	return r;
}

bigint bigint::operator<<(const bigint &other) const
{
	bigint tmp;
	tmp = *this << stringToUint(other.str);
	return tmp;
}

bigint bigint::operator>>(const bigint &other) const
{
	bigint tmp;
	tmp = *this >> stringToUint(other.str);
	return tmp;
}

bigint &bigint::operator<<=(const bigint &other)
{
	*this = *this << stringToUint(other.str);
	return *this;
}

bigint &bigint::operator>>=(const bigint &other)
{
	*this = *this >> stringToUint(other.str);
	return *this;
}

bool bigint::operator==(const bigint &other) const
{
	return this->str == other.str;
}

bool bigint::operator!=(const bigint &other) const
{
	return this->str != other.str;
}

bool bigint::operator<(const bigint &other) const
{
	if (this->str.size() != other.str.size())
		return this->str.size() < other.str.size();
	return this->str < other.str;
}

bool bigint::operator>(const bigint &other) const
{
	if (this->str.size() != other.str.size())
		return this->str.size() > other.str.size();
	return this->str > other.str;
}

bool bigint::operator<=(const bigint &other) const
{
	return !(*this > other);
}

bool bigint::operator>=(const bigint &other) const
{
	return !(*this < other);
}

std::ostream &operator<<(std::ostream &os, const bigint &obj)
{
	os << obj.getStr();
	return os;
}