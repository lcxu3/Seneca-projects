#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Date.h"
#include "Item.h"
#include <iostream>
namespace sdds
{
    class Perishable : public Item
    {
    private:
        Date m_expiry;
        char* instruction;
    public:
        Perishable();
        ~Perishable();
        Perishable(const Perishable& src);
        Perishable& operator=(const Perishable& src);
        const Date& expiry() const;
        std::ofstream& save(std::ofstream& ofstr)const;
        std::ifstream& load(std::ifstream& ifstr);
        std::ostream& display(std::ostream& ostr)const;
        int readSku(std::istream& istr);
        std::istream& read(std::istream& istr);
        operator bool() const;
    };
}
#endif

