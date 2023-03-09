//
// Created by Ntsay Zacarias on 07/03/2023.
//

#include "Manager.h"

void Manager::run() {
    if(!load_data()){
        return;
    }
    main_menu();

}
bool Manager::load_data() {
    std::string fname1 = "no file chosen" , fname2 = "no file chosen";
    localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::DataLoader(fname1,fname2)) {
            case 1:
                fname1 = "../dataset/stations.csv" , fname2 = "../dataset/network.csv";
                break;
            case 2:
                Utility::get_filenames(fname1,fname2);
                break;
            case 9:
                localSession = false;
        }
    }
    std::printf("Loading data...");
    std::vector<Station> stationsVEC = Utility::loadDataFromCSV<Station>(fname1);
    std::vector<Segment> segmentsVEC = Utility::loadDataFromCSV<Segment>(fname2);

    for(const auto& station: stationsVEC){
        railway_network.addStation(station);
        municipalities[station.getMunicipality()].push_back(station);
        districts[station.getDistrict()].push_back(station);
    }
    for(const auto& segment: segmentsVEC){
        railway_network.addSegment(segment);
    }

    std::printf("\n%zu Municipalities |",municipalities.size());
    std::printf(" %zu Districts |",districts.size());
    std::printf(" %zu Stations \n", stationsVEC.size());
    sleep(1);
    return true;
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





