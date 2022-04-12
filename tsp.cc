#include "cities.hh"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]){
    if (argc < 2) {
        std::cerr << "arguments expected\n";
        throw ;
    }
    Cities cities = Cities();

    std::filesystem::path file_path {argv[1]};
    std::ifstream is (file_path);
    file_path = "shortest.tsv";
    std::ofstream os (file_path);
    cities >> is;
    is.close();

    Cities best_cities = Cities();

    double best_path = -1;
    int new_path = 0;

    for (int i=0; i<1000; i++){
        Cities new_cities = cities.reorder();
        new_path = new_cities.total_path_distance(new_cities.ordering);
        if (best_path == -1){
            best_path = new_path;
            best_cities = new_cities;
            std::cout << i << ' ' << best_path;
        } else if (best_path > new_path){
            best_cities = new_cities;
            best_path = new_path;
            std::cout << i << ' ' << best_path;
        }
    }
    cities << os;
    os.close();
    std::cout << cities.total_path_distance({ 0, 1, 2, 3, 4 }) << "\n";
    std::cout << cities.total_path_distance({ 3, 2, 4, 0, 1 }) << "\n";
}