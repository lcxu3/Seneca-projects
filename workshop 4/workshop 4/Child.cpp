#include <iostream>
#include <iomanip>
#include "Child.h"

namespace seneca {
	
    Child::Child(std::string name, int age, const Toy* toysArr[], size_t count) : c_name(name), c_age(age), c_toyCount(count) {
        if (count > 0) {
            toys = new Toy * [c_toyCount];
            for (size_t i = 0; i < c_toyCount; i++) {
                toys[i] = new Toy(*(toysArr[i]));
            }
        }
        else {
            toys = nullptr;
        }
    }

    Child::Child(const Child& src) {
        *this = src;
    }

    Child& Child::operator=(const Child& src) {
        if (this != &src) {
            toys = nullptr;
            if (src.toys) {
                toys = new Toy * [src.c_toyCount];
                for (size_t i = 0; i < src.c_toyCount; i++) {
                    toys[i] = new Toy(*(src.toys[i]));
                }
            }
            c_name = src.c_name;
            c_age = src.c_age;
            c_toyCount = src.c_toyCount;
        }
        return *this;
    }

    Child::Child(Child&& src) noexcept {
        *this = std::move(src);
    }

    Child& Child::operator=(Child&& src) noexcept {
        if (this != &src) {
            c_name = src.c_name;
            src.c_name = "";
            c_age = src.c_age;
            src.c_age = 0;
            c_toyCount = src.c_toyCount;
            src.c_toyCount = 0;
        }
        return *this;
    }

    size_t Child::size() const { return c_toyCount; }

    Child::~Child() {
        for (size_t i = 0; i < c_toyCount; i++) {
            delete toys[i];
        }
      
    }

    std::ostream& operator<<(std::ostream& os, const Child& c)
    {
        static int call_count{ 1 };
        os << "--------------------------" << endl;
        os << "Child: " << call_count << " " << c.c_name << " " << c.c_age << " years old:" << endl;
        os << "--------------------------" << endl;
        if (c.size() > 0) {
            for (size_t i = 0; i < c.size(); i++) {
                os << *c.toys[i];
            }
        }
        else {
            os << "This child has no toys!" << endl;
        }
        os << "--------------------------" << endl;
        call_count++;
        return os;
    }

}