#define _CRT_SECURE_NO_WARNINGS
#include "Event.h"
#include <iostream>
#include <iomanip>
using namespace std;

namespace seneca {

	Event::Event() {}

	void Event::display() 
	{
		counter++;
		if (m_description) {
			int hours = startTimeSec / 3600;
			int minutes = (startTimeSec % 3600) / 60;
			int seconds = startTimeSec % 60;

			cout << setw(2) << setfill('0') << counter << ". "
				<< setw(2) << setfill('0') << hours << ":"
				<< setw(2) << setfill('0') << minutes << ":"
				<< setw(2) << setfill('0') << seconds
				<< " => " << endl;
		}
		else {
			cout << ((strlen(m_description) > 0) ? m_description : "| No Event |") << endl;
		}
	}
	void Event::set(char* desc) {
		if (desc == nullptr || desc[0] == '\0') {
			this->m_description[0] = '\0';
			startTimeSec = 0;
		}
		else {
			strncpy(m_description, desc, MAX - 1);
			startTimeSec = time(nullptr) % 86400;
		}
	}

	void Event::set() {
		m_description[0] = '\0';
	}
	Event::~Event()
	{
		delete[] m_description;
	}
}
