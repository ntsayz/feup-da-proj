//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <functional>

#ifndef SRC_SEGMENT_H
#define SRC_SEGMENT_H

/**
    @class Segment
    @brief Represents a segment, track section between two stations
*/

class Segment {
private:
    /**
    * @brief The source
    */
    std::string source;

    /**
    * @brief The destination
    */
    std::string destination;
    /**
    * @brief The segment's capacity
    */
    double capacity;
    /**
    * @brief The service - STANDARD or ALFA PENDULAR
    */
    std::string service;
public:
    /**
       @brief Gets the cost of the segment
       @param
       @return cost in euros
   */
    double getCost() const;

    Segment(std::string source , std::string destination ,double capacity, std::string service):
    source(std::move(source)),destination(std::move(destination)),capacity(capacity),service(std::move(service)){

    }

    /**
       @brief Creates an Segment object from a string in .csv format
       @param iss An std::istringstream object containing the string from the line in the file
       @return A segment object
   */
    static Segment fromCSVLine(std::istringstream& iss) {
        std::string source, destination, service,capStr;
        double capacity;

        std::getline(iss, source, ',');
        std::getline(iss, destination, ',');
        std::getline(iss, capStr, ',');
        std::getline(iss, service);

        std::stringstream(capStr) >> capacity;

        return {source, destination, capacity, service};
    }
    /**
 * @brief Gets the source station of the segment.
 *
 * @return station name.
 */
    const std::string &getSource() const;

/**
 * @brief Sets the source station of the segment.
 *
 * @param source  source station name.
 */
    void setSource(const std::string &source);

/**
 * @brief Gets the destination station of the segment.
 *
 * @return  destination name.
 */
    const std::string &getDestination() const;

/**
 * @brief Sets the destination station of the segment.
 *
 * @param destination new destination station.
 */
    void setDestination(const std::string &destination);

/**
 * @brief Gets the capacity of the segment.
 *
 * @return  capacity of the segment.
 */
    double getCapacity() const;

/**
 * @brief Sets the capacity of the segment.
 *
 * @param capacity  new capacity.
 */
    void setCapacity(double capacity);

/**
 * @brief Gets the type of service offered on the segment.
 *
 * @return service.
 */
    const std::string &getService() const;

/**
 * @brief Sets the type of service offered on the segment.
 *
 * @param service  new service type.
 */
    void setService(const std::string &service);

    bool operator==(const Segment& other) const {
        return source == other.source && destination == other.destination && capacity == other.capacity && service == other.service;
    }
    bool operator!=(const Segment& other) const {
        return !(*this == other);
    }


};

namespace std {
    template<>
    struct hash<Segment> {
        size_t operator()(const Segment& segment) const {
            // You can choose any way to combine the hashes of the members
            // This is just one example, using bit manipulation
            size_t source_hash = std::hash<std::string>{}(segment.getSource());
            size_t destination_hash = std::hash<std::string>{}(segment.getDestination());
            size_t capacity_hash = std::hash<double>{}(segment.getCapacity());
            size_t service_hash = std::hash<std::string>{}(segment.getService());

            return source_hash ^ (destination_hash << 1) ^ (capacity_hash << 2) ^ (service_hash << 3);
        }
    };
}
#endif //SRC_SEGMENT_H
