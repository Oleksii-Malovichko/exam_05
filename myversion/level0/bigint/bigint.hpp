#pragma once

#include <iostream>
#include <string>
#include <sstream>

// почитать о смысле точек и -> когда получаю значение от объекта

class bigint
{
	std::string str;

	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint &other);
		const std::string &getStr() const;
		bigint &operator=(const bigint &other);

		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		bigint &operator++(void);
		bigint operator++(int);
};

std::ostream &operator<<(std::ostream &os, const bigint &obj);