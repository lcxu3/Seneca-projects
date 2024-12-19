#include "Utilities.h"
#include "Employee.h"
#include "Student.h"
#include "Professor.h"
namespace seneca {
    Person* Utilities::buildInstance(istream& in)
    {
        char firstChar;
        while (in >> std::ws >> firstChar) {
            if (firstChar == 'e' || firstChar == 'E') {
                return new Employee(in);
            }
            else if (firstChar == 's' || firstChar == 'S') {
                return new Student(in);
            }
            else if (firstChar == 'p' || firstChar == 'P') {
                return new Professor(in);
            }
            else {
                return nullptr;
            }
        }

        return nullptr;

    }
}