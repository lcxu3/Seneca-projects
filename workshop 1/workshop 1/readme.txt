here is the instuctions for w1p1 
w1 Module (partially supplied)
Study the code supplied and make sure you understand it.

Finish the implementation of the main function, by completing the parts marked with TODO:

write the prototype of the main function to receive a set of standard command line arguments
echo the set of arguments to standard output in the following format:
1: first argument
2: second argument
3: third argument
4: ...
Do not modify this module in any other place!

Event Module
The Event module defines a system clock, as a global variable named g_sysClock that stores only positive integers. The value of the clock represents the time of day as the number of seconds since midnight (an integer between 0 and 86400; choose an appropriate type). This clock will be accessed when a new event starts and from the main function.

This module also defines a class named Event in the namespace sdds that stores some information about an event:

a C-style null-terminated string of up to 128 characters including the null byte terminator representing the description of the event.

the time when the event starts, expressed in number of seconds that passed from midnight. The time must be an integer between 0 and 86400 (choose an appropriate type).

Public Members

Default constructor
display(): a query that displays to the screen the content of an Event instance in the following format:
COUNTER. HH:MM:SS => DESCRIPTION
If no description has been stored in the current object, this query should print:
COUNTER. | No Event |
where
COUNTER is a field of size 2, that holds the number of times that this function has been called (use a local-to-function variable that remains in memory for the lifetime of the program) Do not use global/member variables to store the counter!
HH:MM:SS represents the time when the event started, expressed in hours, minutes and seconds
set(): a modifier that receives the address of an array of characters (by default, the parameter is null).
If the address is not null and the array is not empty, this function starts a new event and stores the information about this event in the current instance.
If the address is null or the array is empty, this function resets the current instance to an empty state.
Add any other private members that your design requires (without changing the specs above)!
 
 here is the instuctions for w1p2 
 For this part of the workshop, upgrade your Event class to accept a description in the form of a C-style null-terminated string of any length. Make sure your program doesn't have memory leaks.

here is the w1p1.cpp and w1p2.cpp wihtout completing the code 
#include <iostream>
#include <iomanip>
#include <fstream>
#include "event.h"
#include "event.h"

// Cheching if header guards exist and follow convention.
#ifndef SENECA_EVENT_H
    #error "The header guard for 'Event.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces


/* input file format: a comma separated set of fields; some fields have a single parameter
T175,SComputer Starting,P,

codes
	T - time (parameter: a number representing the time--measured in seconds--when the following codes apply)
	S - start event (parameter: a string representing the description for the event that starts)
	E - end the event
	P - print to screen
	A - archive
*/

// TODO: write the prototype for the main function
//         to accept command line arguments

{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	// TODO: print the command line here, in the format
	//   1: first argument
	//   2: second argument
	//   3: third argument
	//   ...


	std::cout << "--------------------------\n\n";


	// the archive can store maximum 10 events
	seneca::Event archive[10];
	// the index of the next available position in the archive
	size_t idxArchive = 0;

	seneca::Event currentEvent;

	const size_t secInDay = 60u * 60u * 24u;// day has 86400 seconds

	for (auto day = 1; day < argc; ++day)
	{
		// each parameter for an application contains the events from one day
		// process each one
		std::cout << "--------------------\n";
		std::cout << "    Day " << day << '\n';
		std::cout << "--------------------\n";
		std::ifstream in(argv[day]);
		if (in.is_open() == false)
		{
			std::cout << "Cannot open file [" << argv[day] << "]. Ignoring it!\n";
			continue; // go to the next iteration of the loop
		}
		char opcode = '\0';
		size_t time = secInDay + 1;
		in >> opcode >> time;

		// starting at midnight, until the end of the day
		for (seneca::g_sysClock = 0u; seneca::g_sysClock < secInDay; ++seneca::g_sysClock)
		{
			// what should happen this second
			while (time == seneca::g_sysClock)
			{
				// skip the delimiter
				in.ignore();
				// read the next opcode
				in >> opcode;

				// end of the file
				if (in.fail())
					break;

				// handle the operation code
				switch (opcode)
				{
				case 'T': // a new time code, this is the exit from the while loop (back to for loop)
					in >> time;
					break;
				case 'S': // start a new event, the old event is automatically finished
					char buffer[1024];
					in.get(buffer, 1024, ',');
					currentEvent.set(buffer);
					break;
				case 'E': // end the current event
					currentEvent.set();
					break;
				case 'P': // print to scren the information about the current event
					currentEvent.display();
					break;
				case 'A': // add a copy of the current event to the archive
					seneca::Event copy(currentEvent);
					archive[idxArchive++] = copy;
					break;
				}
			}
		}
	}

	// print the archive
	std::cout << "--------------------\n";
	std::cout << "    Archive\n";
	std::cout << "--------------------\n";
	for (auto i = 0u; i < idxArchive; ++i)
		archive[i].display();
	std::cout << "--------------------\n";
	
	return cout;
}

monday.txt file
T175,SComputer starts,P,
T200,P,E,P,
T4534,A,SUser logs in,P,
T4800,E,SAuthentication failed,
T4809,A,E,SUser logs in,P,
T5000,E,SBrowser starts,A,
T32464,SBrowser closed,A,P,
T63213,SUser checks email,A,P,

tuesday.txt file
T3743,SUser starts working on homework,A,P,
T4834,E,P,SUser takes a break,P,
T4950,SUser plays Sudoku,
T5200,P,A,E,A,SUser resumes homework,A,P,
T7234,E,

correct output w1p1
Command Line:
--------------------------
  1: ws
  2: monday.txt
  3: tuesday.txt
--------------------------

--------------------
    Day 1
--------------------
 1. 00:02:55 => Computer starts
 2. 00:02:55 => Computer starts
 3. | No Event |
 4. 01:15:34 => User logs in
 5. 01:20:09 => User logs in
 6. 09:01:04 => Browser closed
 7. 17:33:33 => User checks email
--------------------
    Day 2
--------------------
 8. 01:02:23 => User starts working on homework
 9. | No Event |
10. 01:20:34 => User takes a break
11. 01:22:30 => User plays Sudoku
12. 01:26:40 => User resumes homework
--------------------
    Archive
--------------------
13. | No Event |
14. 01:20:00 => Authentication failed
15. 01:23:20 => Browser starts
16. 09:01:04 => Browser closed
17. 17:33:33 => User checks email
18. 01:02:23 => User starts working on homework
19. 01:22:30 => User plays Sudoku
20. | No Event |
21. 01:26:40 => User resumes homework
--------------------

correct output w1p2 
Command Line:
--------------------------
  1: ws
  2: monday.txt
  3: missing.txt 
  4: tuesday.txt
--------------------------

--------------------
    Day 1
--------------------
 1. 00:02:55 => Computer starts
 2. 00:02:55 => Computer starts
 3. | No Event |
 4. 01:15:34 => User logs in
 5. 01:20:09 => User logs in
 6. 09:01:04 => Browser closed
 7. 17:33:33 => User checks email
--------------------
    Day 2
--------------------
Cannot open file [missing.txt]. Ignoring it!
--------------------
    Day 3
--------------------
 8. 01:02:23 => User starts working on homework
 9. | No Event |
10. 01:20:34 => User takes a break
11. 01:22:30 => User plays Sudoku
12. 01:26:40 => User resumes homework
--------------------
    Archive
--------------------
13. | No Event |
14. 01:20:00 => Authentication failed
15. 01:23:20 => Browser starts
16. 09:01:04 => Browser closed
17. 17:33:33 => User checks email
18. 01:02:23 => User starts working on homework
19. 01:22:30 => User plays Sudoku
20. | No Event |
21. 01:26:40 => User resumes homework
--------------------
