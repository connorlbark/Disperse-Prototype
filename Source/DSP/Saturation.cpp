//
//  Saturation.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/31/23.
//

#include "Saturation.hpp"

#include <math.h>
#include <algorithm>


double softClip(double x, double p) {
  double c = std::max(-p, std::min(p, x));
  
  return c + tanh((x - c) / (1.0 - p)) * (1.0 - p);
}
