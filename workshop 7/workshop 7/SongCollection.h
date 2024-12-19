#include <string>
#include <iomanip>
#include <list>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
using std::string;

namespace seneca {
	struct Song {
		string artist;
		string title;
		string album;
		double m_price;
		string releaseyear;
		double songLength;
	};

	class SongCollection {
		std::vector<Song> s;
		void trim(std::string& str) const;
	public:
		SongCollection(const std::string& filename);
		void display(std::ostream& out) const;
		
		 
		void sort(  const std::string& field);
		void cleanAlbum();
		bool inCollection(const std::string& artists) const;
		std::list<Song> getSongsForArtist(const std::string& artists) const;

	};
	std::ostream& operator<<(std::ostream& out, const Song& theSong);

}
#endif // !SENECA_SONGCOLLECTION_H

