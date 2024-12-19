#ifndef SENECA_TIMEDEVENTS_H
#define SENECA_TIMEDEVENTS_H
#include <string>
#include <chrono>
namespace seneca {
	class TimedEvents {
		static const int maxEvents = 10;
		struct Event {
			std::string eventName;
			std::string timeUnits;
			std::chrono::steady_clock::duration eventDuration;
		};

		int numOfRecords;
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		Event events[maxEvents];

	public:
		TimedEvents();
		void startClock();
		void stopClock();
		void addEvent(const char* en);
		friend std::ostream& operator << (std::ostream& os, TimedEvents te);
	};
}
#endif
