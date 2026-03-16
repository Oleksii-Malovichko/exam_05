
#ifndef BIGINT2_HPP
#define BIGINT2_HPP
// где есть = это reference и НЕ const

#include <iostream>
#include <string>

class bigint
{
	std::string str;
	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint &other);
		bigint &operator=(const bigint &other);

		// addition
		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		// incr
		bigint &operator++(); // ++x
		bigint operator++(int); // x++

		// shift num
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint &operator<<=(unsigned int n);
		bigint &operator>>=(unsigned int n);

		// shift obj
		bigint operator<<(const bigint &other) const;
		bigint operator>>(const bigint &other) const;
		bigint &operator<<=(const bigint &other);
		bigint &operator>>=(const bigint &other);

		// compr
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
		bool operator<(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator>=(const bigint &other) const;

	private:
		std::string getStr() const;

};

std::ostream operator<<(std::ostream &os, const bigint &obj);

#endif