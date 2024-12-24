#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
namespace sdds
{
    class Status
    {
        char* description;
        int errorCode;

    public:
        Status(const char* Description = nullptr);
        ~Status();
        Status(const Status& src);
        Status& operator=(const Status& src);
        Status& operator=(int newCode);
        Status& operator=(const char* newDescription);
        operator int() const;
        operator const char* () const;
        operator bool() const;
        void set(const char* Description, int code = 0);
        Status& clear();
    };
    std::ostream& operator<<(std::ostream& os, const Status& status);



}
#endif