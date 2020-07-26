#include "subtitle.h"

istream & ryl::subtitle::getvalidline(istream & io, string & des)
{
	while (getline(io, des))
	{
		if (des.size())
			break;
	}
	return io;
}

void ryl::subtitle::srt_parser()
{
	string tmpstr;
	while (getvalidline(src, tmpstr))
	{
		entry tmpentry;
		try
		{
			tmpentry.no = stoi(tmpstr);
		}
		catch (invalid_argument)
		{
			cerr << "invalid argument when attempting to convert string to integer\nthe raw string is " << tmpstr << "\n\n" << "The exception occurs at entry " << size() << "\n\n";
		}

		getline(src, tmpstr);
		size_t tmppos = tmpstr.find(durationDelimiter);
		tmpentry.dur.begin = tmpstr.substr(0, tmppos);
		tmpentry.dur.end = tmpstr.substr(tmppos + 5, tmpstr.size() - tmppos + 5);
		while (getline(src, tmpstr) and tmpstr.size() != 0)
			tmpentry.txt += tmpstr + "\n";
		tmpentry.txt = makePlainTxt(tmpentry.txt);
		push_back(tmpentry);
	}
}

void ryl::subtitle::ass_parser()
{
	string line;
	entry tmpentry;
	size_t no = 1;
	constexpr unsigned NumOfKeywords = 3;
	const char * keywords[NumOfKeywords] = { "Start","End","Text" };
	const char delimiter = ',';
	size_t commas[3]{ 0 };  //commas before Start, End, Text
	while (getline(src, line) and line != "[Events]");
	getline(src, line);
	for (size_t i = 0; i < NumOfKeywords; i++)
		commas[i] = count(line.begin(), line.begin() + line.find(keywords[i]), delimiter);
	while (getvalidline(src, line))
	{
		tmpentry.no = no++;

		tmpentry.dur.begin = line.substr(find_Nth(line, commas[0], delimiter) + 1, 10);
		tmpentry.dur.end = line.substr(find_Nth(line, commas[1], delimiter) + 1, 10);

		size_t tmppos = find_Nth(line, commas[2], delimiter) + 1;
		tmpentry.txt = line.substr(tmppos, line.size() - tmppos);
		tmpentry.txt = makePlainTxt(tmpentry.txt);
		push_back(tmpentry);
	}
}

size_t ryl::subtitle::find_Nth(const string & str, const size_t & N, const char des, const size_t & pos)
{
	size_t tmpN = 0;
	for (size_t i = pos; i < str.size(); i++)
	{
		if (str[i] == des)
			tmpN++;
		if (tmpN == N)
			return i;
	}
	return str.size();
}

string ryl::subtitle::makePlainTxt(const string & src)
{
	string res;
	bool wrapped = false;
	char curWrapper;
	map<char, char> wrappers{
		{ '{','}' },
		{ '<','>' }
	};
	for (auto iter = src.begin(); iter != src.end(); iter++)
	{
		if (wrapped)
		{
			if (*iter == wrappers[curWrapper])
				wrapped = false;
		}
		else
		{
			if (wrappers.find(*iter) != wrappers.end())
			{
				wrapped = true;
				curWrapper = *iter;
			}
			else if (*iter == '\\' and *(iter + 1) == 'N')
			{
				iter++;
				res.push_back('\n');
			}
			else
				res.push_back(*iter);
		}
	}
	return res;
}

size_t ryl::subtitle::find_in_entry(const string & des, size_t idx, bool isWord, bool caseSens)
{
	const string & src_str = (*this)[idx].txt;
	string pattern = isWord ? ("\\b" + des + "\\b") : des;
	regex r;
	smatch res;
	if (caseSens)
		r.assign(pattern);
	else
		r.assign(pattern, regex_constants::icase);
	if (regex_search(src_str, res, r))
		return res.position();
	else
		return string::npos;
}

ryl::subtitle::subtitle(fstream & src, const string & extension) :
	src(src)
{
	if (extension == ".srt")
		srt_parser();
	else if (extension == ".ass")
		ass_parser();
}

/**
* @brief	 find word des in this subtitle
* @param des objective word
* @param isWord
* @param caseSens
* @param pos from which, 0 as default value
* @return vector<pair<index of entry, position in the entry text>>
*/

vector<pair<size_t, size_t>> ryl::subtitle::find_all(const string & des, bool isWord, bool caseSens, size_t pos)
{
	vector<pair<size_t, size_t>> res;
	size_t temp;
	for (size_t i = pos; i < size(); i++)
	{
		if ((temp = find_in_entry(des, i, isWord, caseSens)) != string::npos)
			res.push_back({ i,temp });
	}
	return res;
}
