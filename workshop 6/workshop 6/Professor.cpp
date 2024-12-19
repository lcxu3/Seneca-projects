
#include "Employee.h"
#include "Professor.h"
namespace seneca {
	Professor::Professor() : m_department(""){}

	Professor::Professor(std::istream& in){
		Employee(in);
		string line;
		istringstream iss(line);
		getline(iss, m_department);
		string tString;
		getline(iss, tString, ',');
		if (tString.length() != 1 || (tString[0] != 'p' && tString[0] != 'P')) {
			throw invalid_argument("Invalid tag");
		}

	}

	void Professor::display(std::ostream& out) const
	{
		Employee::display(out);
		out << '|' << Employee::status() << '|' << Employee::id() << '|' << Employee::age() << '|' 
			<< m_department << '|' << status() << endl;
	}

	std::string Professor::status() const
	{
		return "Profssor";
	}

	std::string Professor::department() const
	{
		return m_department;
	}
}