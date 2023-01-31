//
//  Types.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#ifndef Types_hpp
#define Types_hpp

#include <utility>
#include <iostream>
#include <string>

struct stereofloat : public std::pair<float, float> {
public:
  stereofloat(float L, float R) : std::pair<float, float>(L, R) {}
  
  operator std::string() const { return "(" + std::to_string(this->first) + "," + std::to_string(this->second) + ")"; }

  float L() {
    return this->first;
  }
  
  float R() {
    return this->second;
  }
};

inline std::ostream & operator<<(std::ostream & Str, stereofloat const & v) {
  return Str << v.operator std::string();
}
#endif /* Types_hpp */
