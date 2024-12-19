#ifndef SENECA_PROFESSOR_H
#define SENECA_PROFESSOR_H
#include "Employee.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
namespace seneca {
	class Professor : public Employee {
	
		string m_department;
	public:
		Professor();
		Professor(std::istream& in);
		void display(std::ostream& out) const;
		std::string status() const;
		std::string department() const;
	};
}
#endif // !SENECA_PROFESSOR_H

