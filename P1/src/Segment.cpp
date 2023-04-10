//
// Created by ntsayz on 09-03-2023.
//

#include "Segment.h"


void Segment::setSource(const std::string &source) {
    Segment::source = source;
}

const std::string &Segment::getDestination() const {
    return destination;
}

void Segment::setDestination(const std::string &destination) {
    Segment::destination = destination;
}

double Segment::getCapacity() const {
    return capacity;
}

void Segment::setCapacity(double capacity2) {
    Segment::capacity = capacity2;
}

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


const std::string &Segment::getService() const {
    return service;
}

void Segment::setService(const std::string &service) {
    Segment::service = service;
}

const std::string &Segment::getSource() const {
    return source;
}
