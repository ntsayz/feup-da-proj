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
                max_Number_of_trains();
                break;
            case 4:
                stations_most_trains();
                break;
            case 5:
                most_affected_stations_seg_failure();
                break;
            case 6:
                max_trains_at_station();
                break;
            case 9:
                globalSession = false;
        }
    }
}

void Manager::max_trains_at_station(){
    Utility::clear_screen();
    localSession = true;
    while ((localSession)){
        Station station = get_station_by_name();
        int n = railway_network.max_trains_at_station(station.getName());
        printf("The Maximum Number of trains that can simultaneously arrive at Station %s is %d", station.getName().c_str(), n);
    }
}

void Manager::topkdistrictsmunicipalities() {
    Utility::clear_screen();
    localSession = true;
    while(localSession){
        Utility::header("Transportation Budget Prioritization");
        Utility::body("Report of Top-k Municipalities and Districts and their respective traffic volumes",{""});
        Utility::body("Please enter how many do you want to see!",{""});
        Utility::footer("");
        std::cin >> choice;
        int k = Utility::getInput(choice,1,10);


        auto [top_k_municipalities, top_k_districts] = railway_network.top_k_municipalities_and_districts(k);


        std::printf("Top %d Municipalities:\n", k);
        if (top_k_municipalities.empty()) {
            std::printf("No municipalities found.\n");
        } else {
            for (const auto& [municipality, volume] : top_k_municipalities) {
                if(municipality.size() > 1) std::printf("%s: %.2f\n", municipality.c_str(), volume);
            }
        }

        std::printf("\nTop %d Districts:\n", k);
        if (top_k_districts.empty()) {
            std::printf("No districts found.\n");
        } else {
            for (const auto& [district, volume] : top_k_districts) {
                if(district.size() > 1)std::printf("%s: %.2f\n", district.c_str(), volume);
            }
        }
        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if(choice == 0) localSession = false;
    }
}

void Manager::stations_most_trains(){
    Utility::clear_screen();
    localSession = true;
    while(localSession){
        Utility::header("Pairs of stations require the most amount of trains");
        Utility::body("Pairs of stations require the most amount of trains when taking full advantage of the existing network capacity",{""});
        auto stationspair = railway_network.stations_require_most_trains();

        for(auto const [k,v,val]: stationspair){
            std::printf("%s - %s (%d)\n",k.c_str(),v.c_str(),val);
        }

        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if(choice == 0) localSession = false;
    }
}

void Manager::max_Number_of_trains() {
    Utility::clear_screen();
    localSession = true;
    while (localSession) {
        Utility::header("Maximum Number of Trains between two stations");
        std::printf("Please choose the stations");

        search_stations(true);


        for (auto const sourceSt: sourceStations) {
            for (auto const destSt: destinationStations) {
                int j = railway_network.max_trains_between_stations(sourceSt.getName(), destSt.getName());
                std::printf("The maximum number of trains between stations %s and %s is %d!\n", sourceSt.getName().c_str(), destSt.getName().c_str(),j);
            }
        }

        sourceStations.clear();
        destinationStations.clear();

        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if (choice == 0) localSession = false;
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
                        destinationStations = get_stations_in_municipality();
                        if(destinationStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        sourceStations = get_stations_in_municipality();
                        if(sourceStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 2:
                while(localSession){
                    if(!notARecursiveCall){
                        destinationStations = get_stations_in_district();
                        if(destinationStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        sourceStations = get_stations_in_district();
                        if(sourceStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 3:
                while(localSession){
                    if(!notARecursiveCall){
                        destinationStations.push_back(get_station_by_name());
                        if(destinationStations.empty()){ localSession = false;
                            return;}
                        return;
                    }else{
                        sourceStations.push_back(get_station_by_name());
                        if(sourceStations.empty()){ localSession = false;
                            continue;}
                        search_stations(false);
                    }
                }
                break;
            case 9:
                localSession = false;
                break;
        }


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

void Manager::most_affected_stations_seg_failure() {
    Utility::clear_screen();
    localSession = true;
    while (localSession) {
        Utility::header("Most affected stations by segment failure");
        Utility::body("", {""});

        // Get the most affected stations by segment failure
        auto most_affected_stations = railway_network.most_affected_stations_by_segment_failure();

        std::cout << "Segment Failure\tAffected Stations\tNumber of Affected Stations\n";
        std::cout << "-----------------------------------------------------------------\n";
        for (const auto& item : most_affected_stations) {
            const auto& segment = item.first;
            const auto& affected_stations = item.second;
            int num_affected_stations = affected_stations.size();

            std::cout << segment.getSource() << " - " << segment.getDestination() << "\t";
            for (size_t i = 0; i < affected_stations.size(); ++i) {
                std::cout << affected_stations[i];
                if (i < affected_stations.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "\t" << num_affected_stations << std::endl;
        }

        Utility::footer("0. Back to Menu");
        std::cin >> choice;
        Utility::clear_screen();
        if (choice == 0) localSession = false;
    }
}


void Manager::reducedconnectivity() {
    Utility::clear_screen();
    localSession = true;
    while(localSession){
        Utility::header("Max-flow of trains between stations");
        Utility::body("Repors and Dis",{""});
        std::printf("Please choose the stations");

        search_stations(true);


        for(auto const sourceSt: sourceStations){
            for(auto const destSt: destinationStations){
                int j = railway_network.reduced_max_trains_between_stations(sourceSt.getName(), destSt.getName());
                std::printf("Between '%s' AND '%s' %d trains can travel simultaneously!\n",sourceSt.getName().c_str(),destSt.getName().c_str(),j);
            }
        }

        sourceStations.clear();
        destinationStations.clear();

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









