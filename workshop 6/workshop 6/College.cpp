#include "College.h"

namespace seneca {
    College::College()
    {
        m_persons.push_back(nullptr);
    }

    College& College::operator+=(Person* thePerson)
    {
        m_persons.push_back(thePerson);
        return *this;
    }

    void College::display(std::ostream& out) const
    {
        out << "------------------------------------------------------------------------------------------------------------------------" << endl;
        out << "|                                        Test #1 Persons in the college!                                                |" << endl;
        for (const Person* person : m_persons) {
            out << person->status() << endl;
        }
        out << "------------------------------------------------------------------------------------------------------------------------" << endl;
        out << "|                                        Test #2 Persons in the college!                                                |" << endl;
        for (const Person* person : m_persons) {
            out << person->name() << person->age() << person->id() << endl;
        }
        out << "------------------------------------------------------------------------------------------------------------------------" << endl;
   

    }

    College::~College()
    {
        m_persons.clear();
    }

    

}
