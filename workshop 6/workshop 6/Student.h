#ifndef SENECA_STUDENT_H
#define SENECA_STUDENT_H
#include "Person.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using std::string;
namespace seneca {
	class Student : public Person {
		string m_name;
		int m_age;
		string m_id;
	std::string* m_courses;
		int m_count{};
		string trim(const string& str);
	public:
		Student(std::istream& is);
		std::string status() const;
		std::string name() const;
		std::string age() const;
		std::string id() const;
		void display(std::ostream& out) const;
		~Student();
		Student(const Student& s) = delete;
		Student& operator=(const Student& s) = delete;
	};
}
#endif // !SENECA_STUDENT_H

