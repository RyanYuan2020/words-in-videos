#pragma once

#ifndef FILECRAWLER
#define FLIECRAWLER

#include<vector>
#include<filesystem>
#include<fstream>
#include<algorithm>
#include<set>
#include"subtitle.h"
#include"path_vec.h"

extern bool _DEBUG_;

namespace ryl
{
	using namespace std;
	using namespace ryl;
	using namespace filesystem;

	struct episode
	{
		subtitle subtitleOfEpisode;
		rel_path_vec relativePathOfSubtitle;
		vector<size_t> numericRelativePathVector;
		rel_path_vec relativePathOfVideo;
		episode(const subtitle & subtitleOfEpisode, const rel_path_vec & relativePathOfSubtitle, const vector<size_t> & nrpv, const rel_path_vec & rpv);
	};

	class LexicographicalFile :public vector<directory_entry>
	{
	public:
		LexicographicalFile(const directory_entry & entry_root);
	};
	class FileNotFoundException :exception {};
	class UnexpectedFileType :exception {};

	class FileCrawler
	{
	private:
		const string str_root_of_subtitle_files, str_root_of_video_files;
		void crawler(const rel_path_vec & relativePath, const vector<size_t> & numericRelativePathVector);

		rel_path_vec getVideoPath(const vector<size_t> & NumericRelativePathOfSubtitle);

	public:
		vector<episode> episodes;

		FileCrawler(const string & root_of_subtitle_files, const string & root_of_video_files);
	};
}

#endif // !FILECRAWLER
