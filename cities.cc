#include "cities.hh"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>

std::istream& Cities::operator>>(std::istream& is){
    int value1 = 0;
    int value2 = 0;
    Cities::coord_t working_coords;     // working_coords is the set of coordinates that is currently being imported
    while (is >> value1 >> value2){     // reads two values from the input stream
        working_coords.first = value1;      // sets the x coordinate to the first value
        working_coords.second = value2;     // sets the y coordinate to the second value
        coords_vector.push_back(working_coords);    // appends the coordinates to the cities coords_vector
    }
    return is;
};

std::ostream& Cities::operator<<(std::ostream& os){
    for (auto coord : coords_vector){       // iterates through the cities coords_vector
        os << coord.first << ' ' << coord.second << '\n';       // for each coordinate it appends a row to the output file
    }
    return os;
};

Cities
Cities::reorder(const Cities::permutation_t& new_ordering){
    Cities new_city = Cities();     // creates a new cities object
    for (auto i : new_ordering){    // for each element 'i' in new_ordering
        new_city.input_coord(coords_vector[i]);     // appends the 'i'th element of the current city to the new citie's coord_vector
    }
    return new_city;
}

double 
Cities::total_path_distance(const Cities::permutation_t& ordering) const{
    double distance = -1;   // automatically set distance to an impossible distance
    int city_1_x = 0;
    int city_1_y = 0;
    int city_2_x = 0;
    int city_2_y = 0;
    for (auto city : ordering){     // iterate through each element 'i' in the permutation
        auto coord = coords_vector[city];   // read the coords of the 'i'th element in coords_vector
        if (distance == -1){        // check if this is the first city
            city_1_x = coord.first;     // set cities 1 & 2 to the new coords so that distance is 0
            city_1_y = coord.second;
            city_2_x = coord.first;
            city_2_y = coord.second;
            distance = 0;
        } else{
            city_2_x = city_1_x;    // update city 2
            city_2_y = city_1_y;
            city_1_x = coord.first;     // load city 1 with the new coords
            city_1_y = coord.second;
        }
        distance += std::sqrt(std::pow(city_1_x-city_2_x, 2)+std::pow(city_1_y-city_2_y, 2));   // calculates distance between two cities
    }
    auto coord = coords_vector[ordering[0]];    // gets the coordinates for the first city
    city_2_x = coord.first;
    city_2_y = coord.second;
    distance += std::sqrt(std::pow(city_1_x-city_2_x, 2)+std::pow(city_1_y-city_2_y, 2));   // calculates distance between first and last city

    return distance;
}

Cities::permutation_t
Cities::random_permutation(unsigned len){
    Cities::permutation_t temp_vec;
    for (unsigned i=0; i<len; i++){     // fills a vector 'temp_vec' with values 0 - (len-1)
        temp_vec.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();    // creates a random seed based on the time
    std::mt19937 r1 (seed);     // random number generator using the time 
    std::shuffle(temp_vec.begin(), temp_vec.end(), std::default_random_engine(r1()));   // shuffles the vector
    return temp_vec;
}