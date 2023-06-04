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



Edge::Edge() {

}
