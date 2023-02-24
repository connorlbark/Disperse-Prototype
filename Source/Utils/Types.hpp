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

struct stereofloat {
public :
  float L;
  float R;
  
  stereofloat() {
    this->L = 0.f;
    this->R = 0.f;
  }

  
  stereofloat(float L, float R) {
    this->L = L;
    this->R = R;
  }
  
  operator std::string() const { return "(" + std::to_string(L) + "," + std::to_string(R) + ")"; }

};

inline bool operator== (const stereofloat& s1, const stereofloat& s2) {
  return s1.L == s2.L && s1.R == s2.R;
}

inline std::ostream & operator<<(std::ostream & Str, stereofloat const & v) {
  return Str << v.operator std::string();
}

#endif /* Types_hpp */
