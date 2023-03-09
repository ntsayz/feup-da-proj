//
// Created by ntsayz on 09-03-2023.
//
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#ifndef SRC_STATION_H
#define SRC_STATION_H
/**
    @class Station
    @brief Represents a station
*/
class Station {
private:
    /**
    * @brief The name of the station
    */
    std::string name;
    /**
    * @brief The line the station belongs to
    */
    std::string district;
    /**
    * @brief The municipality of the station
    */
    std::string municipality;
    /**
    * @brief The township
    */
    std::string township;
    /**
    * @brief The line the station belongs to
    */
    std::string line;

public:
    Station(std::string name, std::string district,std::string municipality,  std::string township,std::string line):
    name(std::move(name)), district(std::move(district)),municipality(std::move(municipality)),township(std::move(township)),line(std::move(line)){}



    /**
        @brief Creates a Station object from a string in .csv format
        @param iss An std::istringstream object containing the string from the line in the file
        @return A station object
    */

    static Station fromCSVLine(std::istringstream& iss) {
        std::string name, district, municipality,  township, line;

        std::getline(iss, name, ',');
        std::getline(iss, district, ',');
        std::getline(iss, municipality, ',');
        std::getline(iss, township, ',');
        std::getline(iss,line);

        return {name, district, municipality,  township, line};
    }

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getDistrict() const;

    void setDistrict(const std::string &district);

    const std::string &getMunicipality() const;

    void setMunicipality(const std::string &municipality);

    const std::string &getTownship() const;

    void setTownship(const std::string &township);

    const std::string &getLine() const;

    void setLine(const std::string &line);
};


#endif //SRC_STATION_H
