//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef SRC_NODE_H
#define SRC_NODE_H

/**
 * @class Node
 * @brief Represents a node in a graph
 */
class Node {
private:
    /**
    * @brief The ID of the node
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
    /**
     * @brief Constructs a Node object with the given ID, latitude, and longitude
     * @param id The ID of the node
     * @param latitude The latitude of the node
     * @param longitude The longitude of the node
     */
    Node(int id, double latitude, double longitude) : id(id), latitude(latitude), longitude(longitude) {}

    /**
     * @brief Default constructor for Node
     */
    Node() : id(), latitude(), longitude() {}

    /**
     * @brief Explicit constructor for Node with only the ID
     * @param id The ID of the node
     */
    explicit Node(int id);

    /**
     * @brief Creates a Node object from a string in .csv format
     * @param iss An std::istringstream object containing the string from the line in the file
     * @param hasLabel Indicates if the CSV contains a label (not used in this code)
     * @return A Node object
     */
    static Node fromCSVLine(std::istringstream& iss, bool hasLabel) {
        std::string id_str, latitude_str, longitude_str;

        std::getline(iss, id_str, ',');
        std::getline(iss, latitude_str, ',');
        std::getline(iss, longitude_str);

        try {
            int id = std::stoi(id_str);
            double latitude = std::stod(latitude_str);
            double longitude = std::stod(longitude_str);
            return {id, latitude, longitude};
        } catch (std::invalid_argument const& e) {
            std::cout << "Bad input: std::invalid_argument thrown. Invalid numbers in line." << '\n';
            // You can return an "invalid" Node here, or throw your own exception, or handle this error in some other way.
        } catch (std::out_of_range const& e) {
            std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            // Same here.
        }
        return {};  // Return a default Node if something goes wrong.
    }

    /**
     * @brief Getter for the ID of the node
     * @return The ID of the node
     */
    int getId() const;

    /**
     * @brief Setter for the ID of the node
     * @param id The ID of the node
     */
    void setId(int id);

    /**
     * @brief Getter for the latitude of the node
     * @return The latitude of the node
     */
    double getLatitude() const;

    /**
     * @brief Setter for the latitude of the node
     * @param latitude The latitude of the node
     */
    void setLatitude(double latitude);

    /**
     * @brief Getter for the longitude of the node
     * @return The longitude of the node
     */
    double getLongitude() const;

    /**
     * @brief Setter for the longitude of the node
     * @param longitude The longitude of the node
     */
    void setLongitude(double longitude);
};

#endif //SRC_NODE_H
