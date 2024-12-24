#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "Status.h"
#include "iProduct.h"
#include <iostream>
namespace sdds
{
    class Item : public iProduct
    {
    private:
        double m_price;
        int m_qty;
        int m_qtyNeeded;
        char* m_description;
        bool m_linear;
    protected:
        Status m_state;
        int m_sku;
        bool linear() const;
    public:

        Item();
        ~Item();
        Item(const Item& src);
        Item& operator=(const Item& src);
        int qtyNeeded()const;
        int qty()const;
        operator double()const;
        operator bool()const;
        int operator-=(int qty);
        int operator+=(int qty);
        void linear(bool isLinear);
        void clear();
        bool operator==(int sku)const;
        bool operator==(const char* description)const;
        std::ofstream& save(std::ofstream& ofstr)const;
        std::ifstream& load(std::ifstream& ifstr);
        std::ostream& display(std::ostream& ostr)const;
        int readSku(std::istream& istr);
        std::istream& read(std::istream& istr);
        void setSku(int squ);
        void setStatus(const char* Status);
        void printState(std::ostream& ostr) const;
        operator const char* () const;
    };
}
#endif // !SDDS
