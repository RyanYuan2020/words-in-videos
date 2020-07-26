#include "FileCrawler.h"

ryl::episode::episode(const subtitle & subtitleOfEpisode, const rel_path_vec & relativePathOfSubtitle, const vector<size_t> & nrpv, const rel_path_vec & rpv) :
	subtitleOfEpisode(subtitleOfEpisode), relativePathOfSubtitle(relativePathOfSubtitle), numericRelativePathVector(nrpv), relativePathOfVideo(rpv)
{}

ryl::LexicographicalFile::LexicographicalFile(const directory_entry & entry_root)
{
	for (auto & ent : directory_iterator(entry_root))
		push_back(ent);
	sort(begin(), end(), [](const directory_entry & ent1, const directory_entry ent2)
		 {
			 return ent1.path().string() < ent2.path().string();
		 });
}

void ryl::FileCrawler::crawler(const rel_path_vec & relativePath, const vector<size_t> & numericRelativePathVector)
{
	path path_path(str_root_of_subtitle_files + relativePath.toString());
	directory_entry ent(path_path);
	if (ent.status().type() != file_type::directory)
	{
		if (subtitle_extensions.find(path_path.extension().string()) != subtitle_extensions.end())
		{
			fstream fs(str_root_of_subtitle_files + relativePath.toString());
			subtitle st(fs, path_path.extension().string());
			episodes.emplace_back(st, relativePath, numericRelativePathVector, getVideoPath(numericRelativePathVector));
			if (_DEBUG_)
			{
				cout << "File " << relativePath.toString() << " has been successfully parsed. \n" << st.size() << " entries in total\n"
					<< "The subtitle file is linked with " << episodes[episodes.size() - 1].relativePathOfVideo << "\n\n";
			}
		}
		else
			throw UnexpectedFileType();
	}
	else
	{
		LexicographicalFile cur_ent(ent);
		for (size_t i = 0; i < cur_ent.size(); i++)
		{
			rel_path_vec next(relativePath);
			next.push_back(cur_ent[i].path().filename().string());

			vector<size_t> numeric_next(numericRelativePathVector);
			numeric_next.push_back(i);

			crawler(next, numeric_next);
		}
	}
}

ryl::rel_path_vec ryl::FileCrawler::getVideoPath(const vector<size_t> & NumericRelativePathOfSubtitle)
{
	rel_path_vec res;
	path path_root_video(str_root_of_video_files);
	directory_entry cur_entry(path_root_video);
	for (auto & num : NumericRelativePathOfSubtitle)
	{
		LexicographicalFile lexiCurEntry(cur_entry);
		cur_entry = lexiCurEntry[num];
		res.push_back(cur_entry.path().filename().string());
	}
	return res;
}

ryl::FileCrawler::FileCrawler(const string & root_of_subtitle_files, const string & root_of_video_files) :
	str_root_of_subtitle_files(root_of_subtitle_files), str_root_of_video_files(root_of_video_files)
{
	path path_root(str_root_of_subtitle_files);
	if (!exists(path_root))
		throw FileNotFoundException();
	crawler(rel_path_vec(), vector<size_t>());
}
