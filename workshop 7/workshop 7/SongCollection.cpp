#include "SongCollection.h"

namespace seneca {
	void SongCollection::trim(std::string& str) const
	{
		str.erase(0, str.find_first_not_of(' '));
		str.erase(str.find_last_not_of(' ') + 1);
	}
	SongCollection::SongCollection(const std::string& filename) {
		string line;
		std::ifstream  file(filename);
		if (file.is_open()) {
			std::getline(file, line);
			Song songs;
			songs.title = line.substr(0, 25);
			songs.artist = line.substr(25, 25);
			songs.album = line.substr(50, 25);
			songs.releaseyear = line.substr(75, 5);
			songs.songLength = std::stoi(line.substr(80, 5));
			songs.m_price = std::stof(line.substr(85));
			trim(songs.title);
			trim(songs.artist);
			trim(songs.album);
			trim(songs.releaseyear);
			s.push_back(songs);
		}
		else {
			throw std::invalid_argument("Unable to open file: " + filename);
		
		}
		file.close();
	}
	void SongCollection::display(std::ostream& out) const
	{
		out << "----------------------------------------------------------------------------------------" << std::endl;
		out << "| The original collection                                                              |" << std::endl;
		out << "----------------------------------------------------------------------------------------" << std::endl;
		std::for_each(s.begin(), s.end(), [&out](const Song& song) {
			out << song;
			});

	}

	void SongCollection::sort(const std::string& field)
	{
		if (field == "title") {
			std::sort(s.begin(), s.end(), [](const Song& a, const Song& b) {
				return a.title < b.title;
				});
		}
		else if (field == "album") {
			std::sort(s.begin(), s.end(), [](const Song& a, const Song& b) {
				return a.album < b.album;
				});
		}
		else if (field == "length") {
			std::sort(s.begin(), s.end(), [](const Song& a, const Song& b) {
				return a.songLength < b.songLength;
				});
		}
		else {
			std::cerr << "invaild field for sorting: " << field << std::endl;
		}
	}

	void SongCollection::cleanAlbum()
	{
		auto isValidAlbum = [](const std::string& album) { return album != "[None]"; };

		auto removeInvalidAlbum = [isValidAlbum](Song& song) {
			if (!isValidAlbum(song.album)) {
				song.album = "";
			}
			};

		std::for_each(s.begin(), s.end(), removeInvalidAlbum);
	}

	bool SongCollection::inCollection(const std::string& artists) const
	{
		return std::any_of(s.begin(), s.end(), [&artists](const Song& song) {
			return song.artist == artists;
			});
	}

	std::list<Song> SongCollection::getSongsForArtist(const std::string& artists) const
	{
		std::list<Song> result;
	
		return result;

	}
	
	std::ostream& operator<<(std::ostream& out, const Song& theSong)
	{
		out << '|' << theSong.title << std::setw(20) << '|' << theSong.artist << std::setw(15) <<
			'|' << theSong.album << std::setw(20) << '|' << theSong.releaseyear << std::setw(6) <<
			'|' << theSong.songLength << '|' << theSong.m_price << '|' << std::endl;

		return out;
	}

}


