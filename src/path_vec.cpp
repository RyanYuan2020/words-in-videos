#include<iostream>
#include "path_vec.h"

std::ostream & ryl::operator<<(ostream & os, const rel_path_vec & rpv)
{
	for (auto & relFileName : rpv)
	{
		os << relFileName << ' ';
	}
	return os;
}

ryl::rel_path_vec::rel_path_vec(const string & path)
{
	setPath(path);
}

string ryl::rel_path_vec::toString() const
{
	string res;
	for (auto & dirname : *this)
	{
		res += "\\" + dirname;
	}
	return res;
}

void ryl::rel_path_vec::setPath(const string & str_path)
{
	this->clear();
	size_t begin{ 0 }, end{ 0 };
	for (; end < str_path.size(); end++)
	{
		if (str_path[end] == '\\')
		{
			if (end != begin)
				this->push_back(str_path.substr(begin, end - begin));
			begin = end + 1;
		}
	}
	if (end != begin)
		this->push_back(str_path.substr(begin, end - 1));
}