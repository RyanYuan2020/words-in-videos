//! Source.cpp contains function main of project Words in Videos
//! @Author: Ryan Yuan
//! The development of this project commenced on July, 22rd, 2020

#include<iostream>
#include<fstream>
#include<vector>
#include"subtitle.h"
#include"path_vec.h"
#include"FileCrawler.h"

using namespace std;
using namespace ryl;

int main()
{
	string subtitleroot("E:\\Words in Videos\\Subtitle"),
		videoroot("E:\\Words in Videos\\Videos");

	FileCrawler fc(subtitleroot, videoroot);

	extern map<string, set<string>> inflected_forms;

#ifdef DEBUG
	cout << inflected_forms.size() << "\n";

	for (auto & iform : inflected_forms)
	{
		cout << iform.second.size();
	}
	cout << fc.episodes.size() << " files in total\n\n\n";
#endif // DEBUG

	string des;

	cout << fc.episodes.size() << " files of subtitle have been scanned succefully.  \n"
		"Type a word to start exploration\n\n";

	while (true)
	{
		cin >> des;

	gotoTag_startNewWord:

		cout << "\n";
		size_t i = 0;
		vector<pair<rel_path_vec, entry>> finalRes;
		for (auto & epi : fc.episodes)
		{
			auto res = epi.subtitleOfEpisode.find_all(des);
			if (res.size())
			{
				cout << epi.relativePathOfVideo << ": \n\n";
				for (auto & resPair : res)
				{
					cout << i << ": \n" << epi.subtitleOfEpisode[resPair.first].txt << "\n\n";
					finalRes.push_back({ epi.relativePathOfVideo,epi.subtitleOfEpisode[resPair.first] });
					i++;
				}
			}
		}

		if (finalRes.size() == 0)
		{
			cout << "Not found\n\nPlease start a new word\n\n";
			continue;
		}
		cout << "Input the number before the entry to watch the excerpt.  \n"
			"Type a new word to start another search\n\n\n";

		while (true)
		{
			long long in;
			string raw_input;
			cin >> raw_input;
			try
			{
				in = stoll(raw_input);
			}
			catch (invalid_argument ia)
			{
				des = raw_input;
				goto gotoTag_startNewWord;
			}
			if (in < finalRes.size() and in >= 0)
			{
				string cmd(R"(cd C:\Program Files (x86)\DAUM\PotPlayer)" +
						   string("&&") +
						   R"(PotPlayerMini.exe )" + "\"" + videoroot + finalRes[in].first.toString() + "\" " + "/seek=" + finalRes[in].second.dur.begin);
#ifdef DEBUG
				cout << cmd << "\n\n";
#endif // DEBUG
				system(cmd.c_str());
			}
			else
			{
				cout << "\nInvalid index, choose another one\n\n\n";
				break;
			}
		}
	}
}