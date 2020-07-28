#pragma once

#ifndef SUBTITLE
#define SUBTITLE

#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<iostream>
#include<regex>
#include<sstream>

using namespace std;

namespace ryl
{
	struct entry
	{
		size_t no = 0;
		struct
		{
			string begin, end;
		}dur;
		string txt = string();
	};

	class subtitle : public vector<entry>
	{
		fstream & src;

		const string durationDelimiter = " --> ";

		istream & getvalidline(istream & io, string & des);

		void srt_parser();

		void ass_parser();

		size_t find_Nth(const string & str, const size_t & N, const char des, const size_t & pos = 0);

		string makePlainTxt(const string & src);

		size_t find_in_entry(const string & des, size_t idx, bool isWord = true, bool caseSens = false);

	public:

		subtitle(fstream & src, const string & extension);

		/**
		 * @brief	 find word des in this subtitle
		 * @param des objective word
		 * @param isWord
		 * @param caseSens
		 * @param pos from which, 0 as default value
		 * @return vector<pair<index of entry, position in the entry text>>
		*/
		vector<pair<size_t, size_t>> find_all(const string & des, bool isWord = true, bool caseSens = false, size_t pos = 0);
	};
	const set<string> subtitle_extensions{ string(".srt"),string(".ass") };
	const string inflected_form_data_path(R"(..\data\inflected_forms)");
}

#endif // !SUBTITLE
