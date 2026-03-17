#pragma once

#include <iostream>
#include <string>
#include <sstream>

class bigint
{
	std::string str;
	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint &other);
		bigint &operator=(const bigint &other);

		std::string getStr() const;

		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		bigint &operator++();
		bigint operator++(int); // z++

		bigint operator<<(const bigint &other) const;
		bigint operator>>(const bigint &other) const;
		bigint &operator<<=(const bigint &other);
		bigint &operator>>=(const bigint &other);

		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint &operator<<=(unsigned int n);
		bigint &operator>>=(unsigned int n);

		// compr 
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
		bool operator<(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>=(const bigint &other) const;
};

std::ostream &operator<<(std::ostream &os, const bigint &obj);