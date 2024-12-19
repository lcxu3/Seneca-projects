#include <iostream>
#include <ostream>
#include <iomanip>
#include "TimedEvents.h"

namespace seneca {
	TimedEvents::TimedEvents() :numOfRecords(0){}
	
	void TimedEvents::startClock()
	{
		startTime = std::chrono::steady_clock::now();
	}

	void TimedEvents::stopClock()
	{
		endTime = std::chrono::steady_clock::now();
	}

	void TimedEvents::addEvent(const char* en)
	{
		if (numOfRecords < maxEvents) {
			events[numOfRecords].eventName = en;
			events[numOfRecords].timeUnits = "nanoseconds";
			events[numOfRecords].eventDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
			numOfRecords++;
		}
	}

	std::ostream& operator<<(std::ostream& os, TimedEvents te)
	{
		
		os << "Execution Times:" << std::endl;
		os << "--------------------------" << std::endl;
		for (int i = 0; i < te.numOfRecords; ++i) {
		        os << std::left << std::setw(21) << te.events[i].eventName
				<< std::setw(13) << std::right << 
		std::chrono::duration_cast<std::chrono::nanoseconds>(te.events[i].eventDuration).count()
				<< " " << te.events[i].timeUnits << std::endl;
		}
		os << "--------------------------" << std::endl;
		return os;
	}
}