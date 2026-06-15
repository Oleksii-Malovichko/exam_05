#include "set.hpp"

set::set(searchable_bag &s_bag) : bag(s_bag) {}

set::set(const set &obj) : bag(obj.bag) {}

set &set::operator=(const set &obj)
{
	(void)obj;
	return *this;
}

set::~set() {}

bool set::has(int value) const
{
	return bag.has(value);
}

void set::insert(int value)
{
	if (!this->has(value))
		bag.insert(value);
}

void set::insert(int *data, int size)
{
	for (int i = 0; i < size; i++)
		this->insert(data[i]);
}

void set::print() const
{
	return bag.print();
}

void set::clear()
{
	return bag.clear();
}

const searchable_bag &set::get_bag() const
{
	return this->bag;
}