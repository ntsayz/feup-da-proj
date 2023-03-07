//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Manager.h"

void Manager::run() {
    main_menu();
}

//exemplo de non-functional
void Manager::main_menu(){
    globalSession = true;
    while (globalSession){
        Utility::clear_screen();
        switch (Menu::Main()) {
            case 1:
                std::printf("Nothing to show here yet");
                break;
            case 2:
                std::printf("Don't look for shit you know its not there sir");
                break;
            case 9:
                globalSession = false;
        }
    }
}

//exemplo de functional
void Manager::search_stations(bool notARecursiveCall) {
    /*localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::Search(notARecursiveCall)) {
            case 1:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports = get_airports_by_city_country();
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports = get_airports_by_city_country();
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 2:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports.push_back(get_airports_by_code());
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports.push_back(get_airports_by_code());
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 3:
                while(localSession){
                    if(!notARecursiveCall){
                        arrivalAirports = get_airports_by_coordinates();
                        if(departuresAirports.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        departuresAirports = get_airports_by_coordinates();
                        if(departuresAirports.empty()){ localSession = false;
                            continue;}
                        search_flights_menu(false);
                    }
                }
                break;
            case 9:
                localSession = false;
                break;
        }
        if(!departuresAirports.empty() && !arrivalAirports.empty()){
            search_flights(departuresAirports, arrivalAirports);
            departuresAirports.clear();
            arrivalAirports.clear();
        }
    }*/
}

bool Manager::loadData(const std::string &fname1, const std::string &fname2) {
    //std::vector<Airline> airlinesVEC = Utility::loadDataFromCSV<Airline>(fname1);
    //std::vector<Airport> airportsVEC = Utility::loadDataFromCSV<Airport>(fname2);

    return false;
}



