//
// Created by ntsayz on 09-03-2023.
//

#include "Node.h"


int Node::getId() const {
    return id;
}

void Node::setId(int id) {
    Node::id = id;
}

double Node::getLatitude() const {
    return latitude;
}

void Node::setLatitude(double latitude) {
    Node::latitude = latitude;
}

double Node::getLongitude() const {
    return longitude;
}

void Node::setLongitude(double longitude) {
    Node::longitude = longitude;
}

Node::Node(int id) : id(id) {}
