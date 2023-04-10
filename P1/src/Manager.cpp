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
    std::vector<Station> stationsVEC = Utility::loadDataFromCSV<Station>(fname1);
    std::vector<Segment> segmentsVEC = Utility::loadDataFromCSV<Segment>(fname2);

    for(const auto& station: stationsVEC){
        railway_network.addStation(station);
        municipalities[station.getMunicipality()].push_back(station);
        districts[station.getDistrict()].push_back(station);
        stations[station.getName()] = station;
    }
    for(const auto& segment: segmentsVEC){
        railway_network.addSegment(segment);
    }
    return true;
}

//exemplo de non-functional
void Manager::main_menu(){
    globalSession = true;
    while (globalSession){
        Utility::clear_screen();
        switch (Menu::Main()) {
            case 1:
                topkdistrictsmunicipalities();
                break;
            case 2:
                reducedconnectivity();
                break;
            case 3:
                search_stations(true);
                break;
            case 9:
                globalSession = false;
        }
    }
}



void Manager::topkdistrictsmunicipalities() {
    Utility::clear_screen();
    localSession = true;
    while(localSession){
        Utility::header("Transportation Budget Prioritization");
        Utility::body("Report of Top-k Municipalities and Districts and their respective traffic volumes",{""});
        std::printf("Please enter the value of K:");
        std::cin >> choice;
        int k = Utility::getInput(choice,1,30);

        // Call function to calculate top-k municipalities and districts
        auto [top_k_municipalities, top_k_districts] = railway_network.top_k_municipalities_and_districts(k);

        // Print top-k municipalities
        std::printf("Top %d Municipalities:\n", k);
        if (top_k_municipalities.empty()) {
            std::printf("No municipalities found.\n");
        } else {
            for (const auto& [municipality, volume] : top_k_municipalities) {
                std::printf("%s: %.2f\n", municipality.c_str(), volume);
            }
        }

        // Print top-k districts
        std::printf("\nTop %d Districts:\n", k);
        if (top_k_districts.empty()) {
            std::printf("No districts found.\n");
        } else {
            for (const auto& [district, volume] : top_k_districts) {
                std::printf("%s: %.2f\n", district.c_str(), volume);
            }
        }
        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if(choice == 0) localSession = false;
    }
}




void Manager::search_stations(bool notARecursiveCall) {
    localSession = true;
    while(localSession){
        Utility::clear_screen();
        switch (Menu::search_stations(notARecursiveCall)) {
            case 1:
                while(localSession){
                    if(!notARecursiveCall){
                        sourceStations = get_stations_in_municipality();
                        if(sourceStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        destinationStations = get_stations_in_municipality();
                        if(destinationStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 2:
                while(localSession){
                    if(!notARecursiveCall){
                        sourceStations = get_stations_in_district();
                        if(sourceStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        destinationStations = get_stations_in_district();
                        if(destinationStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 3:
                while(localSession){
                    if(!notARecursiveCall){
                        sourceStations.push_back(get_station_by_name());
                        if(sourceStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        destinationStations.push_back(get_station_by_name());
                        if(destinationStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 9:
                localSession = false;
                break;
        }

        show_stations();

    }
}

void Manager::show_stations(){
    std::printf("FROM:");
    for( auto const k: sourceStations){
        std::printf("%s\n",k.getName().c_str());
    }
    std::printf("\nTO:\n");
    for( auto const k: destinationStations){
        std::printf("%s\n",k.getName().c_str());
    }

    sourceStations.clear();
    destinationStations.clear();
}

void Manager::reducedconnectivity() {
    Utility::clear_screen();
    localSession = true;
    while(localSession){
        Utility::header("Max trains between stations");
        Utility::body("Repors and Dis",{""});
        std::printf("Please stations");
        std::cin >> choice;
        Utility::getInput(choice,1,30);

        int j = railway_network.max_trains_between_stations("Porto Campanhã","Lisboa Oriente");

        std::printf("%-- d --",j);

        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if(choice == 0) localSession = false;
    }
}

std::vector<Station> Manager::get_stations_in_municipality(){
    localSession = true;
    std::string municipalityChosen;
    while(localSession){
        municipalityChosen = Utility::getName("municipality");
        if(municipalityChosen == "exit"){
            localSession = false;
            return std::vector<Station>{};
        }
        option =1;

        for(auto const& [municipality,vec]: municipalities){
            if(Utility::isSubstring(municipality, municipalityChosen)){
                std::cout << option << ". " << municipality << "\n";
                option++;
            }
        }
        if(option < 2){
            std::cerr << "I didn't find any municipality by that name, try again!\n";
            continue;
        }
        std::cout << "-->";
        std::cin >> choice;
        if(choice < 1 || choice >= option || std::cin.bad()){
            std::cerr << "Invalid entry, try again!\n";
            continue;
        }
        option=1;

        for(auto const& [municipality,vec]: municipalities){
            if(Utility::isSubstring(municipality, municipalityChosen)){
                if(option == choice){
                    std::cout << "You chose all the stations in " << municipality << "\n";
                    localSession = false;
                    return vec;
                }
                option++;
            }
        }

    }
    return std::vector<Station>{};
}

std::vector<Station> Manager::get_stations_in_district(){
    localSession = true;
    std::string districtChosen;
    while(localSession){
        districtChosen = Utility::getName("district");
        if(districtChosen == "exit"){
            localSession = false;
            return std::vector<Station>{};
        }
        option =1;

        for(auto const& [district,vec]: districts){
            if(Utility::isSubstring(district, districtChosen)){
                std::cout << option << ". " << district << "\n";
                option++;
            }
        }
        if(option < 2){
            std::cerr << "I didn't find any districts by that name, try again!\n";
            continue;
        }
        std::cout << "-->";
        std::cin >> choice;
        if(choice < 1 || choice >= option || std::cin.bad()){
            std::cerr << "Invalid entry, try again!\n";
            continue;
        }
        option=1;

        for(auto const& [district,vec]: districts){
            if(Utility::isSubstring(district, districtChosen)){
                if(option == choice){
                    std::cout << "You chose all the stations in " << district << "\n";
                    localSession = false;
                    return vec;
                }
                option++;
            }
        }

    }
    return std::vector<Station>{};

}
Station Manager::get_station_by_name(){
    localSession = true;
    std::string stationChosen;
    while(localSession){
        stationChosen = Utility::getName("Station");
        if(stationChosen == "exit"){
            localSession = false;
            return {};
        }
        option =1;

        for(auto const& [station,vec]: stations){
            if(Utility::isSubstring(station, stationChosen)){
                std::cout << option << ". " << station << "\n";
                option++;
            }
        }
        if(option < 2){
            std::cerr << "I didn't find any station with that name, try again!\n";
            continue;
        }
        std::cout << "-->";
        std::cin >> choice;
        if(choice < 1 || choice >= option || std::cin.bad()){
            std::cerr << "Invalid entry, try again!\n";
            continue;
        }
        option=1;

        for(auto const& [station,vec]: stations){
            if(Utility::isSubstring(station, stationChosen)){
                if(option == choice){
                    std::cout << "You chose " << station << "\n";
                    localSession = false;
                    return vec;
                }
                option++;
            }
        }

    }
    return {};
}









