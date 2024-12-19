#ifndef SENECA_CHILD_H
#define SENECA_CHILD_H
#include "Toy.h"


using namespace std;

namespace seneca {
	
	class Child {
        std::string c_name;
        size_t c_age;
        Toy** toys;
        size_t c_toyCount;
    public:
        Child(std::string name, int age, const Toy* toysArr[], size_t count);
        Child(const Child& src);
        Child& operator=(const Child& src);
        Child(Child&& src) noexcept;
        Child& operator=(Child&& src) noexcept;
        ~Child();
        size_t size() const;

        friend std::ostream& operator << (std::ostream& os, const Child& c);
	};
}
#endif // !SENECA_CHILD_H

