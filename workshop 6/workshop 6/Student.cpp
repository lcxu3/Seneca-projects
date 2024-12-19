#include "Student.h"
namespace seneca {
	string Student::trim(const string& str)
	{
		size_t first = str.find_first_not_of(' ');
		if (std::string::npos == first) {
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}
	
	Student::Student(std::istream& is)
	{
		
		string line;
		getline(is, line);
		std::istringstream iss(line);
		string field;
		std::getline(iss, field, ',');
		char tag = field[0];
		if (tag != 's' && tag != 'S') {
			throw std::runtime_error("++Invalid record!");
		}
		std::getline(iss, m_name, ',');
		m_name = trim(m_name);
		
		std::getline(iss, field, ',');
		try {
			m_age = std::stoi(trim(field));
		}
		catch (const std::invalid_argument& e) {
			throw std::runtime_error(m_name + " ++Invalid record!");
		}

		std::getline(iss, m_id, ',');
		if (m_id.empty() || m_id[0] != 'S') {
			throw std::runtime_error(m_name + " ++Invalid record!");
		}

		std::getline(iss, field, ',');
		try {
			m_count = std::stoi(trim(field));
		}
		catch (const std::invalid_argument& e) {
			throw std::runtime_error(m_name + " ++Invalid record!");
		}


		m_courses = new std::string[m_count];
		for (int i = 0; i < m_count; ++i) {
			std::getline(iss, m_courses[i], ',');
			m_courses[i] = trim(m_courses[i]);
		}
	}

	std::string Student::status() const
	{
		return "Student";
	}

	std::string Student::name() const
	{
		return m_name;
	}

	std::string Student::age() const
	{
		return std::to_string(m_age);
	}

	std::string Student::id() const
	{
		return m_id;
	}

	void Student::display(std::ostream& out) const
	{
		out << "| " << std::left << std::setw(10) << status()
			<< " | " << std::setw(10) << m_id
			<< " | " << std::setw(20) << m_name
			<< " | " << std::setw(3) << m_age
			<< " | ";
		for (int i = 0; i < m_count; ++i) {
			out << m_courses[i];
			if (i != m_count - 1) out << ", ";
		}
	}

	Student::~Student()
	{
		delete[] m_courses;
	}



}
