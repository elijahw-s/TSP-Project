/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>


// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of cities. Each value represents a unique index
  // into the current city ordering in some container.
  using permutation_t = std::vector<unsigned int>;

  Cities(){};

  std::istream& operator>>(std::istream&);
  std::ostream& operator<<(std::ostream&);

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities 
  reorder(const Cities::permutation_t& new_ordering);

  // .input_coord(coord) appends a coordinate to the cities coords_vector
  void
  input_coord(coord_t coord){coords_vector.push_back(coord);}

  // .size() returns the number of cities contained within a cities object
  unsigned
  size(){return coords_vector.size();}

  permutation_t static
  random_permutation(unsigned len);

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double 
  total_path_distance(const permutation_t& ordering) const;

 private:
  permutation_t ordering;
  std::vector<coord_t> coords_vector;
};
