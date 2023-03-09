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

unsigned int Segment::getCapacity() const {
    return capacity;
}

void Segment::setCapacity(unsigned int capacity) {
    Segment::capacity = capacity;
}

const std::string &Segment::getService() const {
    return service;
}

void Segment::setService(const std::string &service) {
    Segment::service = service;
}
