//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#ifndef SRC_NODE_H
#define SRC_NODE_H
/**
    @class Node
    @brief Represents a node
*/
class Node {
private:
    /**
    * @brief The id of the node
    */
    int id;
    /**
    * @brief The latitude of the node
    */
    double latitude;
    /**
    * @brief The longitude of the node
    */
    double longitude;

public:
    Node(int id, double latitude, double longitude): id(id), latitude(latitude), longitude(longitude) {}

    Node() : id(), latitude(), longitude() {}

    /**
        @brief Creates a Node object from a string in .csv format
        @param iss An std::istringstream object containing the string from the line in the file
        @return A node object
    */
    static Node fromCSVLine(std::istringstream& iss, bool hasLabel) {
        std::string id_str, latitude_str, longitude_str;

        std::getline(iss, id_str, ',');
        std::getline(iss, latitude_str, ',');
        std::getline(iss, longitude_str);

        int id = std::stoi(id_str);
        double latitude = std::stod(latitude_str);
        double longitude = std::stod(longitude_str);

        return {id, latitude, longitude};
    }
};



#endif //SRC_NODE_H
