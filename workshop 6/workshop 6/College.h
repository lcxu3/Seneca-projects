#ifndef SENECA_COLLEGE_H
#define SENECA_COLLEGE_H
#include <vector>
#include <iostream>
#include <iomanip>
#include "Person.h"
#include <list>
using namespace std;
namespace seneca {
	class College  {
		vector<Person*> m_persons;
	public:
		College(const College& c) = delete;
		College& operator=(const College& c) = delete;
		College();
		College& operator +=(Person* thePerson);
		void display(std::ostream& out) const;
		~College();
		template <typename T>
		void select(const T& test, std::list<const Person*>& persons);
	};

	template<typename T>
	inline void College::select(const T& test, std::list<const Person*>& persons)
	{
		for (const seneca::Person* persons : m_persons) {
			if (test(person)) {
				persons.push_back(person);
			}
		}
	}
}

#endif // !SENECA_COLLEGE_H

