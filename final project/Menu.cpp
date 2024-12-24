#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds
{
    Menu::Menu() {
        setEmpty();
    };
    Menu::Menu(const char* MenuContext, unsigned int NumberOptions) {
        if (NumberOptions <= 15 && NumberOptions >= 1 && MenuContext != nullptr && strlen(MenuContext) > 0) {
            numoption = NumberOptions;
            mContext = new char[strlen(MenuContext) + 1];
            strcpy(mContext, MenuContext);
        }
        else {
            setEmpty();
        };
    };
    Menu::~Menu() {
        delete[] mContext;
    };
    void Menu::setEmpty() {
        mContext = nullptr;
        numoption = -1;

    };
    unsigned int Menu::run() const {
        cout << mContext;
        cout << "0- Exit" << endl;
        cout << "> ";
        unsigned int optionNumber = ut.getIntegerWithRange(numoption);
        return optionNumber;
    };
    void Menu::set(const char* MenuContext, unsigned int NumberOptions) {
        delete[] mContext;
        mContext = new char[strlen(MenuContext) + 1];
        strcpy(mContext, MenuContext);
        numoption = NumberOptions;
    };
}