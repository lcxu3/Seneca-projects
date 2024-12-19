#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <cstring>
#include <string>
#include <string.h>
namespace seneca {
	extern unsigned int g_sysClock;
	static int counter;
	const int MAX = 128;
	class Event {
		char m_description[MAX + 1];
		std::string desc[MAX + 1];
		int startTimeSec = 0;
	public:
		Event();
		void display();
		void set(char* desc);
		void set(); 
		~Event();


	};

}
#endif 

