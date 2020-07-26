#pragma once

#ifndef REL_PATH_VEC
#define REL_PATH_VEC

#include<iostream>
#include<vector>
#include<string>

using namespace std;

namespace ryl
{
	class rel_path_vec : public vector<string>
	{
		friend ostream & operator<<(ostream &, const rel_path_vec &);
	public:
		using vector<string>::vector;

		rel_path_vec(const string & path);
		string toString()const;
		void setPath(const string & str_path);
	};

	ostream & operator<<(ostream & os, const rel_path_vec & rpv);
}

#endif // !PATH_VEC
