//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <optional>
#include <iostream>

#ifndef SRC_EDGE_H
#define SRC_EDGE_H

/**
 * @class Edge
 * @brief Represents an edge between two nodes in a graph
 */
class Edge {
private:
    int source;  // The ID of the source node
    int destination;  // The ID of the destination node
    double distance;  // The distance of the edge
    std::optional<std::string> source_label;  // An optional label for the source node
    std::optional<std::string> destination_label;  // An optional label for the destination node

public:
    /**
     * @brief Default constructor for Edge
     */
    Edge();

    /**
     * @brief Constructor for Edge with specified source, destination, distance, source_label, and destination_label
     * @param source The ID of the source node
     * @param destination The ID of the destination node
     * @param distance The distance of the edge
     * @param source_label Optional label for the source node
     * @param destination_label Optional label for the destination node
     */
    Edge(int source, int destination, double distance, std::optional<std::string> source_label = {}, std::optional<std::string> destination_label = {})
            : source(source), destination(destination), distance(distance), source_label(std::move(source_label)), destination_label(std::move(destination_label)) {}

    /**
     * @brief Creates an Edge object from a string in .csv format
     * @param iss An std::istringstream object containing the string from the line in the file
     * @param hasLabels Indicates if the CSV contains labels (not used in this code)
     * @return An Edge object
     */
    static Edge fromCSVLine(std::istringstream& iss, bool hasLabels) {
        std::string source_str, destination_str, distance_str;
        std::string source_label_str, destination_label_str;

        std::getline(iss, source_str, ',');
        std::getline(iss, destination_str, ',');
        std::getline(iss, distance_str, ',');

        try {
            int source = std::stoi(source_str);
            int destination = std::stoi(destination_str);
            double distance = std::stod(distance_str);
            return {source, destination, distance};
        } catch (std::invalid_argument const& e) {
            std::cout << "Bad input: std::invalid_argument thrown. Invalid numbers in line." << '\n';
            // You can return an "invalid" Edge here, or throw your own exception, or handle this error in some other way.
        } catch (std::out_of_range const& e) {
            std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            // Same here.
        }
        return {};
    }

    /**
     * @brief Getter for the source ID of the edge
     * @return The ID of the source node
     */
    int getSource() const;



    /**
     * @brief Getter for the destination ID of the edge
     * @return The ID of the destination node
     */
    int getDestination() const;


    /**
     * @brief Getter for the distance of the edge
     * @return The distance of the edge
     */
    double getDistance() const;




    /**
     * @brief Overloaded > operator for comparing edges based on their distances
     * @param other The other edge to compare with
     * @return True if this edge's distance is greater than the other edge's distance, False otherwise
     */
    bool operator>(const Edge& other) const {
        // Assuming getDistance() returns the weight of the edge
        return this->getDistance() > other.getDistance();
    }
};

#endif //SRC_EDGE_H
