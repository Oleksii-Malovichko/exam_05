#include "bigint.hpp"

bigint::bigint()
{
	str = "0";
}

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	str = ss.str();
}

bigint::bigint(const bigint &obj)
{
	*this = obj;
}

bigint &bigint::operator=(const bigint &obj)
{
	if (this != &obj)
	{
		this->str = obj.str;
	}
	return *this;
}

std::string bigint::getStr() const
{
	return str;
}

std::string reverse(const std::string s)
{
	std::string res;
	size_t i = s.length();
	while (i > 0)
	{
		res += s[i-1];
		i--;
	}
	return res;
}

std::string addition(const bigint obj1, const bigint obj2)
{
	std::string s1 = reverse(obj1.getStr());
	std::string s2 = reverse(obj2.getStr());
	std::string res;
	size_t len1 = s1.length();
	size_t len2 = s2.length();

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

	int carry = 0;
	int digit1;
	int digit2;
	size_t len = s1.length();
	size_t i = 0;
	while (i < len)
	{
		digit1 = s1[i] - '0';
		digit2 = s2[i] - '0';
		int result = digit1 + digit2 + carry;
		carry = result / 10;
		res.push_back((result % 10) + '0');
		i++;
	}
	if (carry != 0)
		res.push_back(carry + '0');
	return reverse(res);
}

bigint bigint::operator+(const bigint &obj) const
{
	bigint temp;
	std::string res = addition(*this, obj);
	temp.str = res;
	return temp;
}

bigint &bigint::operator+=(const bigint &obj)
{
	*this = *this + obj;
	return *this;
}

bigint &bigint::operator++()
{
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint temp(*this);
	*this = *this + bigint(1);
	return temp;
}

bigint bigint::operator<<(unsigned int num) const
{
	bigint temp(*this);
	if (temp.str == "0")
		return temp;
	// temp.str.insert(temp.str.end(), num, '0');
	temp.str.append(num, '0');
	return temp;
}

bigint bigint::operator>>(unsigned int num) const
{
	bigint temp(*this);
	if (num >= temp.str.length())
		temp.str = "0";
	else
	{
		// temp.str.erase(temp.str.length() - num);
		temp.str = temp.str.substr(0, temp.str.length() - num);
	}
	return temp;
}

bigint &bigint::operator<<=(unsigned int num)
{
	*this = *this << num;
	return *this;
}

bigint &bigint::operator>>=(unsigned int num)
{
	*this = *this >> num;
	return *this;
}

unsigned int stringToUINT(std::string str)
{
	std::stringstream ss(str);
	unsigned int res = 0;
	ss >> res;
	return res;
}

bigint bigint::operator<<(const bigint &obj) const
{
	bigint temp(*this);
	temp = temp << stringToUINT(obj.getStr());
	return temp;
}

bigint bigint::operator>>(const bigint &obj) const
{
	bigint temp(*this);
	temp = temp >> stringToUINT(obj.getStr());
	return temp;
}

bigint &bigint::operator<<=(const bigint &obj)
{
	*this = *this << obj;
	return *this;
}

bigint &bigint::operator>>=(const bigint &obj)
{
	*this = *this >> obj;
	return *this;
}

bool bigint::operator==(const bigint &obj) const
{
	return str == obj.str;
}

bool bigint::operator!=(const bigint &obj) const
{
	return !(str == obj.str);
}

bool bigint::operator<(const bigint &obj) const
{
	size_t len1 = str.length();
	size_t len2 = obj.str.length();

	if (len1 != len2)
		return len1 < len2;
	return str < obj.str;
}

bool bigint::operator>(const bigint &obj) const
{
	return obj < *this;
}

bool bigint::operator<=(const bigint &obj) const
{
	return *this < obj || str == obj.str;
}

bool bigint::operator>=(const bigint &obj) const
{
	return obj < *this || str == obj.str;
}

std::ostream &operator<<(std::ostream &os, const bigint &obj)
{
	os << obj.getStr();
	return os;
}

// // 890

// bigint::bigint()
// {
// 	this->str = "0";
// }

// bigint::bigint(unsigned int num)
// {
// 	std::stringstream ss;
// 	ss << num;
// 	this->str = ss.str();
// 	// std::cout << "str: " << str << std::endl;
// }

// bigint::bigint(const bigint& source)
// {
// 	(*this) = source;
// }

// bigint& bigint::operator=(const bigint& source)
// {
// 	if(this == &source) // сравнение адресов
// 		return(*this); // вернуть значение
// 	this->str = source.str;
// 	return(*this);
// }

// std::string bigint::getStr() const
// {
// 	return(this->str);
// }

// std::string reverse(const std::string& str)
// {
// 	std::string revStr;
// 	for(size_t i = str.length(); i > 0; i--)
// 	{
// 		revStr.push_back(str[i - 1]);
// 	}
// 	return(revStr);
// }

// std::string addition(const bigint& obj1, const bigint& obj2)
// {
// 	std::string str1 = reverse(obj1.getStr());
// 	std::string str2 = reverse(obj2.getStr());
// 	std::string result;
// 	size_t len1 = str1.length();
// 	size_t len2 = str2.length();

// 	if(len1 > len2)
// 	{
// 		int diff = len1 - len2;
// 		while(diff > 0)
// 		{
// 			str2.push_back('0');
// 			diff--;
// 		}
// 	}
// 	else if(len2 > len1)
// 	{
// 		int diff = len2 - len1;
// 		while(diff > 0)
// 		{
// 			str1.push_back('0');
// 			diff--;
// 		}
// 	}

// 	int carry = 0;
// 	int digit1;
// 	int digit2;
// 	size_t len = str1.length();
// 	for(size_t i = 0; i < len; i++)
// 	{
// 		digit1 = str1[i] - '0';
// 		// std::cout <<  "digit1:" << digit1 << std::endl;
// 		digit2 = str2[i] - '0';
// 		// std::cout << "digit2:" << digit2 << std::endl;
// 		int res = digit1 + digit2 + carry;
// 		// std::cout << res << std::endl;
// 		if(res > 9)
// 		{
// 			carry = res / 10;
// 			result.push_back((res % 10) + '0');
// 		}
// 		else
// 			result.push_back(res + '0');
// 	}
// 	if(carry != 0)
// 		result.push_back(carry + '0');
// 	return(reverse(result));
// }

// bigint bigint::operator+(const bigint& other)const
// {
// 	bigint temp(other);
// 	temp.str.clear();
// 	std::string result = addition(*this, other);
// 	temp.str = result;
// 	//std::cout << "r: " << result << std::endl;

// 	return(temp);
// }

// bigint& bigint::operator+=(const bigint& other)
// {
// 	(*this) = (*this) + other;
// 	return(*this);
// }

// bigint& bigint::operator++()
// {
// 	*(this) = *(this) + bigint(1);
// 	return(*this);
// }

// bigint bigint::operator++(int)
// {
// 	bigint temp = (*this);
// 	*(this) = *(this) + bigint(1);
// 	return(temp);
// }


// bigint bigint::operator<<(unsigned int n)const
// {
// 	bigint temp = *this;

// 	temp.str.insert(temp.str.end(), n, '0');
// 	//std::cout << temp.str << std::endl;
// 	return(temp);
// }

// bigint bigint::operator>>(unsigned int n)const
// {
// 	bigint temp = *this;
// 	size_t len = temp.str.length();
// 	if(n >= len)
// 		temp.str = "0";
// 	else
// 	{
// 		temp.str.erase(temp.str.length() - n, n); // вырезать начиная от temp.str.length() - n до ко-ва n
// 	}
// 	return(temp);
// }

// bigint& bigint::operator<<=(unsigned int n)
// {
// 	(*this) = (*this) << n;
// 	return(*this);
// }

// bigint& bigint::operator>>=(unsigned int n)
// {
// 	(*this) = (*this) >> n;
// 	return(*this);
// }

// unsigned int stringToUINT(std::string str)
// {
// 	std::stringstream ss(str);
// 	unsigned int res;
// 	ss >> res;
// 	return (res);
// }

// bigint bigint::operator<<(const bigint& other)const
// {
// 	bigint temp;
// 	temp = (*this) << stringToUINT(other.str);
// 	return(temp);
// }

// bigint bigint::operator>>(const bigint& other)const
// {
// 	bigint temp;
// 	temp = (*this) >> stringToUINT(other.str);
// 	return(temp);
// }

// bigint& bigint::operator<<=(const bigint& other)
// {
// 	(*this) = (*this) << stringToUINT(other.str);
// 	return(*this);
// }

// bigint& bigint::operator>>=(const bigint& other)
// {
// 	(*this) = (*this) >> stringToUINT(other.str);
// 	return(*this);
// }


// bool bigint::operator==(const bigint& other) const
// {
// 	if(this->getStr() == other.getStr())
// 		return(true);
// 	return(false);
// }

// bool bigint::operator!=(const bigint& other) const
// {
// 	return(!((*this) == (other)));
// }

// bool bigint::operator<(const bigint& other) const
// {
// 	std::string str1 = this->str;
// 	std::string str2 = other.getStr();
// 	size_t len1 = str1.length();
// 	size_t len2 = str2.length();

// 	if(len1 != len2)
// 		return(len1 < len2);
// 	return(str1 < str2);  // thanks for your feedback, mjuicha!! o7
// }

// bool bigint::operator>(const bigint& other) const
// {
// 	// return(!(((*this) < other)));
// 	return other < *this;
// }

// bool bigint::operator<=(const bigint& other) const
// {
// 	return((((*this) < other) || ((*this) == other)));
// }

// bool bigint::operator>=(const bigint& other) const
// {
// 	return((((*this) > other) || ((*this) == other)));
// }

// // non member func
// std::ostream& operator<<(std::ostream& output, const bigint& obj)
// {
// 	output << obj.getStr();
// 	return(output);
// }
