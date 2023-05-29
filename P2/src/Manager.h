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
#include "Node.h"
#include "Edge.h"
#include "Menu.h"
#include "Graph.h"
#ifdef _WIN32
#include <windows.h>
#endif
// Library effective with Linux
#include <unistd.h>

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

    Graph graph;


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
    /// Function to load the data from the .csv files from the dataset.
    /// \param fname1 Path to nodes file
    /// \param fname2 Path to edges file
    /// \return It compares the size of the data structures that the data was loaded into, to determine if they're according to spec
    bool load_data();
    /**
	* @brief Main menu of the application
	*/
    void main_menu();

};


#endif //SRC_MANAGER_H
