#ifndef SENECA_EMPLOYEE_H
#define SENECA_EMPLOYEE_H
#include "Person.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
namespace seneca {
	class Employee :  public Person {
		string m_name;
		string m_age;
		string m_id;
		
	public:
		Employee();
		Employee(istream& is);
		string status() const;
		string name() const;
		string id() const;
		string age() const;
		void display(std::ostream& out) const;
	};
}
#endif // !SENECA_EMPLOYEE_H
