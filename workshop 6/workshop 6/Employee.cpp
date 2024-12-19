#include "Employee.h"


namespace seneca {
	Employee::Employee() : m_name(""), m_age(""), m_id("") {}

	Employee::Employee(istream& is)
	{
       string line;
        getline(is, line);
        istringstream iss (line);
       
		string tagString,tags;
        getline(iss, tagString, ',');
        if (tagString.length() != 1 || (tagString[0] != 'e' && tagString[0] != 'E')) {
            throw invalid_argument("Invalid tag");
        }
         tags = tagString[0];

       getline(iss, m_name, ',');

       string ageString;
        getline(iss, ageString, ',');
        try {
            m_age = stoi(ageString);
        }
        catch (...) {
            throw invalid_argument(m_name + " ++Invalid record!");
        }

        getline(iss, m_id);
        if (m_id.empty() || m_id[0] != 'E') {
            throw invalid_argument(m_name + " ++Invalid record!");
        }

	}

	string Employee::status() const
	{
		return "Employee";
	}

	string Employee::name() const
	{
		return m_name;
	}

	
	string Employee::id() const
	{
		return m_id;
	}

	string Employee::age() const
	{
		return m_age;
	}

	void Employee::display(std::ostream& out) const
	{
		out << left <<  '| ' << status() << setw(10) <<  '| ' << 
			m_id << setw(10) << '| ' << m_name << setw(20) << '| ' << m_age << setw(3) << '| ';
	}


}
