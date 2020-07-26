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

bool _DEBUG_ = false;

int main()
{
	string subtitleroot("E:\\Words in Videos\\Subtitle"),
		videoroot("E:\\Words in Videos\\Videos");

	FileCrawler fc(subtitleroot, videoroot);

	if (_DEBUG_)
	{
		cout << fc.episodes.size() << " files in total\n\n\n";
	}

	while (true)
	{
		string des;
		cin >> des;
		cout << "\n";
		size_t i = 0;
		vector<pair<rel_path_vec, entry>> finalRes;
		for (auto & epi : fc.episodes)
		{
			auto res = epi.subtitleOfEpisode.find_all(des);
			if (res.size())
			{
				cout << epi.relativePathOfVideo << ": \n";
				for (auto & resPair : res)
				{
					cout << i << "  " << epi.subtitleOfEpisode[resPair.first].txt << "\n\n";
					finalRes.push_back({ epi.relativePathOfVideo,epi.subtitleOfEpisode[resPair.first] });
					i++;
				}
			}
		}

		if (finalRes.size() == 0)
		{
			cout << "Not found\n\n";
			continue;
		}

		while (true)
		{
			size_t in;
			cin >> in;
			if (in < finalRes.size())
			{
				string cmd(R"(cd C:\Program Files (x86)\DAUM\PotPlayer)" +
						   string("&&") +
						   R"(PotPlayerMini.exe )" + "\"" + videoroot + finalRes[in].first.toString() + "\" " + "/seek=" + finalRes[in].second.dur.begin);
				if (_DEBUG_)
				{
					cout << cmd << "\n\n";
				}
				system(cmd.c_str());
			}
			else
			{
				cout << "\n\n";
				break;
			}
		}
	}
}
