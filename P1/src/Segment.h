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
    * @brief The
    */
    std::string source;

    /**
    * @brief The
    */
    std::string destination;
    /**
    * @brief The
    */
    double capacity;
    /**
    * @brief The
    */
    std::string service;
public:
    Segment(std::string source , std::string destination ,double capacity, std::string service):
    source(std::move(source)),destination(std::move(destination)),capacity(capacity),service(std::move(service)){}

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

    const std::string &getSource() const;

    void setSource(const std::string &source);

    const std::string &getDestination() const;

    void setDestination(const std::string &destination);

    double getCapacity() const;

    void setCapacity(double capacity);

    const std::string &getService() const;

    void setService(const std::string &service);

    bool operator==(const Segment& other) const {
        return source == other.source && destination == other.destination && capacity == other.capacity && service == other.service;
    }
    bool operator!=(const Segment& other) const {
        return !(*this == other);
    }


};


#endif //SRC_SEGMENT_H
