#ifndef SENECA_SET_H
#define SENECA_SET_H
#include "Collection.h"
#include <cmath>

namespace seneca {

    template<typename T>
    class Set : public Collection<typename T,CAPACITY>
    {

    public:
        bool add(const T& item);
    };

    template<typename T>
    inline bool Set<T>::add(const T& item)
    {
        if (data.size() == 0) {
            return data.add(item);
        }

        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == item)
                return false;
        }

        return data.add(item);
    }

    template<>
    class Set<double>
    {
    private:
        Collection<double, 100> data;

    public:
        bool add(const double& item) {
            if (data.size() == 0) {
                return data.add(item);
            }

            for (int i = 0; i < data.size(); ++i) {
                if (std::fabs(data[i] - item) <= 0.01)
                    return false;
            }

            return data.add(item);
        }
    };
  
  

}

#endif // SDDS_SET_H