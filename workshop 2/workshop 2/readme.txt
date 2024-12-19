TimedEvents Module
Design and code a class named TimedEvents that manages a statically allocated array of Event objects. Your class predefines the maximum number of event objects at 10. The instance variables for your class should include:

the number of records currently stored
the start time for the current event (an object of type std::chrono::steady_clock::time_point; see documentation here)
the end time for the current event (an object of type std::chrono::steady_clock::time_point)
an array of Events of structure type. The structure should contain the following fields:
a string with the event name.
a string with the predefined units of time
the duration of the event (an object of type std::chrono::steady_clock::duration; see documentation here)
Your class includes the following member functions:

a default constructor

startClock(): a modifier that starts the timer for an event

stopClock(): a modifier that stops the timer for an event

addEvent(): a modifier that receives the address of a C-style null-terminated string that holds the name of the event. This function will update the next time-record in the array:

stores into the name attribute the C-style string at the pointed to address
stores "nanoseconds" as the units of time
calculates and stores the duration of the event (use std::chrono::duration_cast<std::chrono::nanoseconds>(), see documentation here)
a friend insertion operator that receives a reference to an std::ostream object and a TimedEvents object. This operator should insert in the std::ostream object the records from the array in the following format:

Execution Times:
--------------------------
EVENT_NAME DURATION UNITS
EVENT_NAME DURATION UNITS
...
--------------------------
The name of the event should be in a field of size 21, aligned on the left; the duration should be in a field of size 13, aligned on the right.

Starting and stopping the timer means getting the current time (use std::chrono::steady_clock::now(); see documentation here).


StringSet Module
Design and code a class named StringSet that manages a dynamically allocated array of elements of type std::string. Your class keeps track of the number of strings currently stored  and  include a move constructor and a move assignment operatorand defines the following member functions :

a no-argument default constructor
a 1-argument constructor that receives the address of a C-style null terminated string containing the name of a file from which this member function populates the current object. This function
reads the file to count the number of strings present in the file (the record delimiter should be a single space ' ')
allocates memory for that number of strings in the array
re-reads the file and loads the strings into the array.
size_t size(): a query that returns the number of strings stored in the current object.
std::string operator[](size_t): a query that returns a copy of the string at the index received as the function parameter. If the index is invalid, this function should return an empty string.
To review the syntax for reading from a text file using an std::ifstream object see the chapter in your notes entitled Input and Output Operators.

Add any other members that your design requires (without changing the specs above)!

here is the w2 main file 
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include "StringSet.h"
#include "StringSet.h" // intentional
#include "TimedEvents.h"
#include "TimedEvents.h" // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_STRINGSET_H
    #error "The header guard for 'StringSet.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TIMEDEVENTS_H
    #error "The header guard for 'TimedEvents.h' doesn't follow the convention!"
#endif

enum ExitCodes
{
	ALL_GOOD                  = 0,  // nothing is wrong
	ERR_INSUFICIENT_ARGUMENTS = 1,  // the application received too few arguments
	ERR_TOO_MANY_ARGUMENTS    = 2,  // the application received too many arguments
};

int cout = ExitCodes::ALL_GOOD; // won't compile if headers don't follow convention regarding namespaces

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	if (argc == 1)
	{
		std::cerr << "ERROR: Missing file name!\n";
		return ExitCodes::ERR_INSUFICIENT_ARGUMENTS;
	}
	else if (argc != 2)
	{
		std::cerr << "ERROR: Too many arguments!\n";
		return ExitCodes::ERR_TOO_MANY_ARGUMENTS;
	}

	seneca::TimedEvents t;
	{
		t.startClock();
		seneca::StringSet a;
		t.stopClock();
		t.addEvent("  0-arg Constructor");
		std::cout << "  0-arg Constructor - a.size = "
			<< std::setw(7) << a.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[  0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[ 99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size() + 0] << "]\n\n";


		t.startClock();
		seneca::StringSet b(argv[1]);
		t.stopClock();
		t.addEvent("  1-arg Constructor");
		std::cout << "  1-arg Constructor - b.size = "
			<< std::setw(7) << b.size() << " strings -> ";
		std::cout << std::setw(20) << "(b) String     1: [" << b[  0] << "]\n";
		std::cout << std::setw(70) << "(b) String   100: [" << b[ 99] << "]\n";
		std::cout << std::setw(70) << "(b) String  1000: [" << b[999] << "]\n";
		std::cout << std::setw(70) << "(b) String  last: [" << b[b.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(b) String last+: [" << b[b.size() + 1] << "]\n\n";


		t.startClock();
		seneca::StringSet c{ b };
		t.stopClock();
		t.addEvent("  Copy Constructor");
		std::cout << "  Copy Constructor  - c.size = "
			<< std::setw(7) << c.size() << " strings -> ";
		std::cout << std::setw(20) << "(c) String     1: [" << c[  0] << "]\n";
		std::cout << std::setw(70) << "(c) String   100: [" << c[ 99] << "]\n";
		std::cout << std::setw(70) << "(c) String  1000: [" << c[999] << "]\n";
		std::cout << std::setw(70) << "(c) String  last: [" << c[c.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(c) String last+: [" << c[c.size() + 2] << "]\n\n";


		t.startClock();
		a = b;
		t.stopClock();
		t.addEvent("  Copy Assignment");
		std::cout << "  Copy Assignment   - a.size = "
			<< std::setw(7) << a.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[  0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[ 99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size() + 3] << "]\n\n";

		{
			auto& aInDisguise = a;
			aInDisguise = a;
		}

		t.startClock();
		seneca::StringSet d = std::move(a);
		t.stopClock();
		t.addEvent("  Move Constructor");
		std::cout << "  Move Constructor  - d.size = "
			<< std::setw(7) << d.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[  0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[ 99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size() + 4] << "]\n\n";
		std::cout << std::setw(70) << "(d) String     1: [" << d[  0] << "]\n";
		std::cout << std::setw(70) << "(d) String   100: [" << d[ 99] << "]\n";
		std::cout << std::setw(70) << "(d) String  1000: [" << d[999] << "]\n";
		std::cout << std::setw(70) << "(d) String  last: [" << d[d.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(d) String last+: [" << d[d.size() + 5] << "]\n\n";

		{
			auto& dInDisguise = d;
			dInDisguise = std::move(d);
		}

		t.startClock();
		a = std::move(d);
		t.stopClock();
		t.addEvent("  Move Assignment");
		std::cout << "  Move Assignment   - a.size = "
			<< std::setw(7) << a.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[  0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[ 99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size() + 6] << "]\n\n";
		std::cout << std::setw(70) << "(d) String     1: [" << d[ 0] << "]\n";
		std::cout << std::setw(70) << "(d) String   100: [" << d[ 99] << "]\n";
		std::cout << std::setw(70) << "(d) String  1000: [" << d[999] << "]\n";
		std::cout << std::setw(70) << "(d) String  last: [" << d[d.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(d) String last+: [" << d[d.size() + 7] << "]\n";


		t.startClock();
	}
	t.stopClock();
	t.addEvent("  Destructor");

	std::cout << t;
	
	return cout;
}

here is the output 
0-arg Constructor - a.size =       0 strings ->  (a) String     1: []
                                                   (a) String   100: []
                                                   (a) String  1000: []
                                                   (a) String  last: []
                                                   (a) String last+: []

  1-arg Constructor - b.size = 1293934 strings ->  (b) String     1: [This]
                                                   (b) String   100: [OR]
                                                   (b) String  1000: [provide]
                                                   (b) String  last: [Shakespeare]
                                                   (b) String last+: []

  Copy Constructor  - c.size = 1293934 strings ->  (c) String     1: [This]
                                                   (c) String   100: [OR]
                                                   (c) String  1000: [provide]
                                                   (c) String  last: [Shakespeare]
                                                   (c) String last+: []

  Copy Assignment   - a.size = 1293934 strings ->  (a) String     1: [This]
                                                   (a) String   100: [OR]
                                                   (a) String  1000: [provide]
                                                   (a) String  last: [Shakespeare]
                                                   (a) String last+: []

  Move Constructor  - d.size = 1293934 strings ->  (a) String     1: []
                                                   (a) String   100: []
                                                   (a) String  1000: []
                                                   (a) String  last: []
                                                   (a) String last+: []

                                                   (d) String     1: [This]
                                                   (d) String   100: [OR]
                                                   (d) String  1000: [provide]
                                                   (d) String  last: [Shakespeare]
                                                   (d) String last+: []

  Move Assignment   - a.size = 1293934 strings ->  (a) String     1: [This]
                                                   (a) String   100: [OR]
                                                   (a) String  1000: [provide]
                                                   (a) String  last: [Shakespeare]
                                                   (a) String last+: []

                                                   (d) String     1: []
                                                   (d) String   100: []
                                                   (d) String  1000: []
                                                   (d) String  last: []
                                                   (d) String last+: []
--------------------------
Execution Times:
--------------------------
  0-arg Constructor          529603 nanoseconds
  1-arg Constructor      3707006530 nanoseconds
  Copy Constructor        720402197 nanoseconds
  Copy Assignment         717849582 nanoseconds
  Move Constructor           810805 nanoseconds
  Move Assignment            369102 nanoseconds
  Destructor              223364646 nanoseconds
--------------------------