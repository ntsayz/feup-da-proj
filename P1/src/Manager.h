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

    /**
	* @brief Hashtable to store stations. Its Unique name as key and a station object as the value.
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
    std::unordered_map<std::string,std::vector<Station>> districts;
    /**
	* @brief Graph with Stations as nodes and segments as edges that connect them. Stored in an adjacency list
	*/
    Graph railway_network;
    /**
	* @brief List of stations in the source. (recurso)
	*/
    std::vector<Station> sourceStations;
    /**
	* @brief List of stations in the destination. (recurso)
	*/
    std::vector<Station> destinationStations;

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
     * Function to search for stations
     */
    ///
    /// \param notARecursiveCall Since we need to use this function multiple times within the same call chain, it should be recursive. This was a way to handle recursion appropriately
    void search_stations(bool notARecursiveCall);

    /**
 * @brief Finds the top k districts and municipalities based on the number of stations.
 *
 * This function analyzes the data to determine the top k districts and municipalities
 * with the highest number of train stations.
 */
    void topkdistrictsmunicipalities();

/**
 * @brief Analyzes the reduced connectivity of the train network.
 *
 * This function examines the train network and determines the impact of
 * reduced connectivity on the overall system.
 */
    void reducedconnectivity();

/**
 * @brief Gets a vector of stations located within a specific municipality.
 *
 * @return A vector of Station objects within the specified municipality.
 */
    std::vector<Station> get_stations_in_municipality();

/**
 * @brief Gets a vector of stations located within a specific district.
 *
 * @return A vector of Station objects within the specified district.
 */
    std::vector<Station> get_stations_in_district();

/**
 * @brief Gets a specific station by its name.
 *
 * @return A Station object with the specified name, if found.
 */
    Station get_station_by_name();

/**
 * @brief Calculates the maximum number of trains that can operate in the network.
 *
 * This function analyzes the capacity of each segment and determines the maximum
 * number of trains that can operate simultaneously.
 */
    void max_Number_of_trains();

/**
 * @brief Finds the station pairs that require the most trains to operate.
 *
 * This function analyzes the train network to determine which pairs of stations
 * require the most trains to operate effectively.
 */
    void stations_pairs_require_most_trains();

/**
 * @brief Identifies the most affected stations in case of segment failure.
 *
 * This function examines the train network and determines which stations would
 * be most affected if a segment were to fail, based on factors such as
 * connectivity and capacity.
 */
    void most_affected_stations_seg_failure();

/**
 * @brief Calculates the maximum number of trains at each station.
 *
 * This function analyzes the train network and determines the maximum number of
 * trains that can be present at each station at any given time.
 */
    void max_trains_at_station();
};


#endif //SRC_MANAGER_H
