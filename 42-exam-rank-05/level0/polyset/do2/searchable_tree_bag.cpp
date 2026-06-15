#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &obj) : tree_bag(obj) {}

searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &obj)
{
	if (this != &obj)
	{
		tree_bag::operator=(obj);
	}
	return *this;
}

searchable_tree_bag::~searchable_tree_bag(){}

bool searchable_tree_bag::search(node *node, const int value) const
{
	if (node == 0)
		return false;
	else if (node->value == value)
		return true;
	else if (node->value > value)
		return search(node->l, value);
	return search(node->r, value);
}

bool searchable_tree_bag::has(int value) const
{
	return search(this->tree, value);
}
