#pragma once

#include "searchable_bag.hpp"

class set
{
	searchable_bag &bag;
	public:
		set(searchable_bag &s_bag);
		set(const set &obj);
		set &operator=(const set &obj);
		~set();

		bool has(int) const;
		void insert(int);
		void insert(int *, int);
		void print() const;
		void clear();

		const searchable_bag &get_bag() const;
};