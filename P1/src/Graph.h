//
// Created by ntsayz on 09-03-2023.
//

#include <vector>
#include <unordered_map>
#include "Segment.h"
#include "Station.h"
#ifndef SRC_GRAPH_H
#define SRC_GRAPH_H


class Graph {
public:
    /**
     * @brief Adds a station to the graph
     * @param station The station to be added
     */
    void addStation(const Station& station);
    /**
     * @brief Adds a segment to the graph
     * @param segment The segment to be added
     */
    void addSegment(const Segment& segment);
    /**
     * @brief Returns a vector of all segments going out from a specified station
     * @param station The station to get the segments for
     * @return A vector of all segments going out from the specified station
     */
    std::vector<Segment> getSegmentsFromStation(const Station& station) const;
    /**
     * @brief Returns a vector of all segments going into a specified station
     * @param station The station to get the segments for
     * @return A vector of all segments going into the specified station
     */
    std::vector<Segment> getSegmentsToStation(const Station& station) const;
    /**
     * @brief Returns the number of segments going out from a specified station
     * @param station The station to get the segments for
     * @return The number of segments going out from the specified station
     */
    int numSegmentsFromStation(const Station& station) const;
    /**
     * @brief Returns the number of segments going into a specified station
     * @param station The station to get the segments for
     * @return The number of segments going into the specified station
     */
    int numSegmentsToStation(const Station& station) const;
private:
    /**
     * @brief Adjacency list representing all stations as nodes and segments as edges.
     *        Each station is mapped to a vector of segments going out from that station.
     */
    std::unordered_map<std::string, std::vector<Segment>> adjacency_list;
    /**
     * @brief Hashtable with station IDs being mapped to their objects
     */
    std::unordered_map<int, Station> stations;


};


#endif //SRC_GRAPH_H
