#include "cities.hh"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>

Cities::Cities(){}

std::istream& Cities::operator>>(std::istream& is){
    int value1 = 0;
    int value2 = 0;
    Cities::coord_t working_coords;
    while (is >> value1 >> value2){
        working_coords.first = value1;
        working_coords.second = value2;
        coords_vector.push_back(working_coords);
    }
    return is;
};

std::ostream& Cities::operator<<(std::ostream& os){
    for (auto coord : coords_vector){
        os << coord.first << ' ' << coord.second << '\n';
    }
    return os;
};

Cities
Cities::reorder(const Cities::permutation_t& new_ordering){
    Cities new_city = Cities();
    std::vector temp_coords_vector = coords_vector;
    for (auto i : new_ordering){
        temp_coords_vector.push_back(coords_vector[i]);
    }
    coords_vector = temp_coords_vector;
    return new_city
}

double 
Cities::total_path_distance(const Cities::permutation_t& ordering) const{
    double distance = -1;
    int city_1_x = 0;
    int city_1_y = 0;
    int city_2_x = 0;
    int city_2_y = 0;
    for (auto city : ordering){
        auto coord = coords_vector[city];
        if (distance == -1){
            city_1_x = coord.first;
            city_1_y = coord.second;
            city_2_x = coord.first;
            city_2_y = coord.second;
            distance = 0;
        } else{
            city_2_x = city_1_x;
            city_2_y = city_1_y;
            city_1_x = coord.first;
            city_1_y = coord.second;
        }
        distance += std::sqrt(std::pow(city_1_x-city_2_x, 2)+std::pow(city_1_y-city_2_y, 2));
    }
    auto coord = coords_vector[ordering[0]];
    city_2_x = coord.first;
    city_2_y = coord.second;
    distance += std::sqrt(std::pow(city_1_x-city_2_x, 2)+std::pow(city_1_y-city_2_y, 2));

    return distance;
}

Cities::permutation_t
Cities::random_permutation(unsigned len) const{
    Cities::permutation_t temp_vec;
    unsigned seed = 1;
    for (unsigned i=0; i<len; i++){
        temp_vec.push_back(i);
    }
    std::shuffle(temp_vec.begin(), temp_vec.end(), std::default_random_engine(seed));
    return temp_vec;
}