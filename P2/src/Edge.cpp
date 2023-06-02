//
// Created by ntsayz on 09-03-2023.
//

#include "Edge.h"


int Edge::getSource() const {
    return source;
}

void Edge::setSource(int source) {
    Edge::source = source;
}

int Edge::getDestination() const {
    return destination;
}

void Edge::setDestination(int destination) {
    Edge::destination = destination;
}

double Edge::getDistance() const {
    return distance;
}

void Edge::setDistance(double distance) {
    Edge::distance = distance;
}

const std::optional<std::string> &Edge::getSourceLabel() const {
    return source_label;
}

void Edge::setSourceLabel(const std::optional<std::string> &sourceLabel) {
    source_label = sourceLabel;
}

const std::optional<std::string> &Edge::getDestinationLabel() const {
    return destination_label;
}

void Edge::setDestinationLabel(const std::optional<std::string> &destinationLabel) {
    destination_label = destinationLabel;
}

Edge::Edge() {

}
