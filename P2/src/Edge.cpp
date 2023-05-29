//
// Created by ntsayz on 09-03-2023.
//

#include "Edge.h"


void Edge::setSource(const std::string &source) {
    Edge::source = source;
}

const std::string &Edge::getDestination() const {
    return destination;
}

void Edge::setDestination(const std::string &destination) {
    Edge::destination = destination;
}

unsigned int Edge::getCapacity() const {
    return weight;
}

void Edge::setWeight(unsigned int weight) {
    Edge::weight = weight;
}


const std::string &Edge::getSource() const {
    return source;
}
