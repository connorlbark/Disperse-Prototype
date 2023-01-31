//
//  Disperse.hpp
//  Disperse
//
//  Created by Connor Barker on 1/20/23.
//

#ifndef Disperse_hpp
#define Disperse_hpp

#include <stdio.h>
#include <list>
#include "Delay.hpp"
#include <JuceHeader.h>

class Disperse {
private:
  
  float sampleRate;
  
  // two-dimension list: first dimension is parallel delays, second dimension is serial delays.
  std::list<std::list<Delay>> delays;

  Delay createDelay(int parallel, int series);
public:
  Disperse();
  
  void initialize(float sampleRate);
  
  stereofloat process(stereofloat in);
  
  
  
  
};

#endif /* Disperse_hpp */
