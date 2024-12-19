#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include "Pair.h"

namespace seneca {

    template<typename T, int CAPACITY>
    class Collection
    {
    private:
        T data[CAPACITY];
        int currentSize{ 0 };

    public:
        static T dummy;

        int size() const;

        void display(std::ostream& out = std::cout);
        bool add(const T& item);
        T& operator[](int index);
       

        ~Collection() {}
    };
   
    template<typename T, int CAPACITY>
    inline int Collection<T, CAPACITY>::size() const
    {
        return currentSize;
    }
    template<typename T, int CAPACITY>
    inline void Collection<T, CAPACITY>::display(std::ostream& out)
    {
        for (int i = 0; i < currentSize; i++) {
            out << data[i] << " ";
        }
        out << std::endl;
    }
    template<typename T, int CAPACITY>
    inline bool Collection<T, CAPACITY>::add(const T& item)
    {
        if (currentSize < CAPACITY) {
            for (int i = 0; i < currentSize; ++i) {
                if (data[i] == item)
                    return false;
            }
            data[currentSize++] = item;
            return true;
        }
        return false;
    }
    template<typename T, int CAPACITY>
    inline T& Collection<T, CAPACITY>::operator[](int index)
    {
        return (index >= 0 && index < currentSize) ? data[index] : dummy;
    }

    template<>
    Pair Collection<Pair, 100>::dummy = Pair("No Key", "No Value");
}
#endif 
