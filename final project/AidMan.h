#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "Utils.h"
#include "Date.h"
#include "iProduct.h"
#include <iostream>
#include "Perishable.h"
#include "Item.h"
namespace sdds
{
    const int sdds_max_num_items = 100;
    class AidMan
    {
    private:
        char* fileName;
        int numberItemsArray;
        Menu menuInfo;
        iProduct* allItems[sdds_max_num_items];
        unsigned int menu() const;
        void save();
        void deallocate();
        bool load();
    public:
        AidMan();
        ~AidMan();
        AidMan(const AidMan& source) = delete;
        AidMan& operator=(const AidMan& source) = delete;
        void run();
        int list(const char* sub_desc = nullptr);
        void add();
        int search(int sku) const;
    };
}
#endif
