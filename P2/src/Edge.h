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
    @class Edge
    @brief Represents an edge between two nodes
*/
class Edge {
private:
    int source;
    int destination;
    double distance;
    std::optional<std::string> source_label;
    std::optional<std::string> destination_label;

public:
    Edge();
    Edge(int source, int destination, double distance, std::optional<std::string> source_label = {}, std::optional<std::string> destination_label = {})
            : source(source), destination(destination), distance(distance), source_label(std::move(source_label)), destination_label(std::move(destination_label)) {}

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
        } catch (std::invalid_argument const &e) {
            std::cout << "Bad input: std::invalid_argument thrown. Invalid numbers in line." << '\n';
            // You can return an "invalid" edge here, or throw your own exception, or handle this error in some other way.
        } catch (std::out_of_range const &e) {
            std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            // Same here.
        }
        return {};  // Return a default Edge if something goes wrong.
    }


    int getSource() const;

    void setSource(int source);

    int getDestination() const;

    void setDestination(int destination);

    double getDistance() const;

    void setDistance(double distance);

    const std::optional<std::string> &getSourceLabel() const;

    void setSourceLabel(const std::optional<std::string> &sourceLabel);

    const std::optional<std::string> &getDestinationLabel() const;

    void setDestinationLabel(const std::optional<std::string> &destinationLabel);
};



#endif //SRC_EDGE_H
