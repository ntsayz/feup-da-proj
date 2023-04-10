//
// Created by Ntsay Zacarias on 07/03/2023.
//

#ifndef SRC_MENU_H
#define SRC_MENU_H
#include "Utility.h"

/**
    @class Menu
    @brief Prints the menu and avoids bloating the Manager class
*/
class Menu {

public:
    static int choice;
    static unsigned int Main();
    static unsigned int DataLoader(std::string& f1, std::string& f2);
    static void GetCustomFiles();
    static unsigned int search_stations(bool notARecursiveCall);
};


#endif //SRC_MENU_H
