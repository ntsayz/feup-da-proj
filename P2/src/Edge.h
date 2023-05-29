//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <optional>
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
    Edge(int source, int destination, double distance, std::optional<std::string> source_label = {}, std::optional<std::string> destination_label = {})
            : source(source), destination(destination), distance(distance), source_label(std::move(source_label)), destination_label(std::move(destination_label)) {}

    static Edge fromCSVLine(std::istringstream& iss, bool hasLabels) {
        std::string source_str, destination_str, distance_str;
        std::string source_label_str, destination_label_str;

        std::getline(iss, source_str, ',');
        std::getline(iss, destination_str, ',');
        std::getline(iss, distance_str, ',');

        int source = std::stoi(source_str);
        int destination = std::stoi(destination_str);
        double distance = std::stod(distance_str);

        if (hasLabels) {
            std::getline(iss, source_label_str, ',');
            std::getline(iss, destination_label_str);
            return {source, destination, distance, source_label_str, destination_label_str};
        }
        return {source, destination, distance};
    }
};



#endif //SRC_EDGE_H
