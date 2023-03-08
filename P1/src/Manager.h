//
// Created by Ntsay Zacarias on 07/03/2023.
//

#ifndef SRC_MANAGER_H
#define SRC_MANAGER_H

/**
    @class Manager
    @brief Manages the application.
    Stores its most important data structures, manages the application state.
*/

#include <string>
#include "Utility.h"
#include "Menu.h"

class Manager {
private:

    /**
	* @brief variable for user input.
	*/
    int option;
    /**
	* @brief variable for user input.
	*/
    int choice;
    /**
	* @brief Controls the global state of the application in the menus.
	*/
    bool globalSession = false;
    /**
	* @brief Controls the local state of the application in functions, menus.
	*/
    bool localSession = false;
    /** @name  Manager's Data Structures */
    /**@{
    *
    */

    /**
	* @brief Hashtables and whatnot
	*/

    /** @} end of Manager's Data Structures */
public:
    /**
	* @brief Manager's constructor
	*/
    Manager()= default;
    /**
	* @brief Function to start the application, called by the only instance of the manager function.
	*/
    void run();
    void testing();
    /// Function to load the data from the .csv files from the dataset.
    /// \param fname1 Path to 'network.csv'
    /// \param fname2 Path to 'stations.csv'
    /// \return It compares the size of the data structures that the data was loaded into, to determine if they're according to spec
    bool loadData(const std::string& fname1, const std::string& fname2);

    void main_menu();

    /// 1st Option in the Main menu; Shows the 'Search Stations' section
    /// \param notARecursiveCall Since we need to use this function multiple times within the same call chain, it should be recursive. This was a way to handle recursion appropriately
    void search_stations(bool notARecursiveCall);
};


#endif //SRC_MANAGER_H
