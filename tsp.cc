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
    Cities cities;

    std::filesystem::path file_path {argv[1]};
    std::ifstream is (file_path);       // creates input stream from a file
    file_path = "shortest.tsv";
    std::ofstream os (file_path);       // creates output stream to a file
    cities >> is;
    is.close();

    Cities best_cities;

    double best_path = -1;
    double new_path = 0;

    for (int i=0; i<10000; i++){
        Cities::permutation_t new_perm = Cities::random_permutation(cities.size());     // creates a new permutation for each iteration
        new_path = cities.total_path_distance(new_perm);        // calculates the path length with the given permutation
        if (best_path == -1){           // if it is the first city...
            best_path = new_path;
            best_cities = cities.reorder(new_perm);
            std::cout << i << ": " << best_path << "\n";
        } else if (best_path > new_path){   // if the new path is shorter than the previous shortest path...
            best_path = new_path;       // make the new path the best path
            best_cities = cities.reorder(new_perm); // create a city where the coords_vector is in the order of the best path
            std::cout << i << ": " << best_path << "\n";
        }
    }
    best_cities << os;
    os.close();
}