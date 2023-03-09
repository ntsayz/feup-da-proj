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
#include "Station.h"
#include "Segment.h"
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
	* @brief Hashtable to store stations. Its Unique name as key and an airline object as the value.
	*/
    std::unordered_map<std::string,Station> stations;
    /**
	* @brief Hashtable to store a concatenated string with all of the stations of a municipality
     * with a district and its municipality name as key, for uniqueness.
     * A vector of Stations objects as values, because municipalities may have multiple stations
	*/
    std::unordered_map<std::string,std::vector<Station>> municipalities;
    /**
	* @brief Hashtable to store all of the stations of a district
     * A vector of Stations objects as values, because a districts may have multiple stations
	*/
    std::unordered_map<std::string,std::vector<Station>> district;
    /**
	* @brief Graph with Airports as nodes and flights as edges that connect them. Stored in an adjacency list
	*/
    //Graph flight_network;
    /**
	* @brief List of airports in the city of departure.
	*/
    //std::vector<Airport> departuresAirports;
    /**
	* @brief List of airports in the city of arrival.
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
    bool load_data();
    /**
	* @brief Main menu of the application
	*/
    void main_menu();
    /**
     * Function t
     */
    /// 1st Option in the Main menu; Shows the 'Search Stations' section
    /// \param notARecursiveCall Since we need to use this function multiple times within the same call chain, it should be recursive. This was a way to handle recursion appropriately
    void search_stations(bool notARecursiveCall);
};


#endif //SRC_MANAGER_H
