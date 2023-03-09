//
// Created by ntsayz on 09-03-2023.
//

#include "Station.h"

const std::string &Station::getName() const {
    return name;
}

void Station::setName(const std::string &name) {
    Station::name = name;
}

const std::string &Station::getDistrict() const {
    return district;
}

void Station::setDistrict(const std::string &district) {
    Station::district = district;
}

const std::string &Station::getMunicipality() const {
    return municipality;
}

void Station::setMunicipality(const std::string &municipality) {
    Station::municipality = municipality;
}

const std::string &Station::getTownship() const {
    return township;
}

void Station::setTownship(const std::string &township) {
    Station::township = township;
}

const std::string &Station::getLine() const {
    return line;
}

void Station::setLine(const std::string &line) {
    Station::line = line;
}
