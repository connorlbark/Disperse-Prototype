//
//  Saturation.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/31/23.
//

#include "Saturation.hpp"

#include <math.h>


static double c;
double softClip(double x, double p) {
  c = (x > p ? p : (x < -p ? -p : x));
  
  return c + tanh((x - c) / (1.0 - p)) * (1.0 - p);
}
