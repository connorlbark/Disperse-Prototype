//
//  Disperse.cpp
//  Disperse
//
//  Created by Connor Barker on 1/20/23.
//

#include "Disperse.hpp"


Disperse::Disperse() {}

void Disperse::initialize(float sampleRate) {
  this->sampleRate = sampleRate;
  
  this->delays = {
    {createDelay(0, 0)},
    {createDelay(1, 0)},
    {createDelay(3, 0)}
  };
};


Delay Disperse::createDelay(int parallel, int series) {
  Delay delay = Delay();
  
  delay.initialize(sampleRate, MAX_DELAY_MS);
  
  delay.setFeedback(0.5);
  delay.setModDepth(0.2);
  delay.setMix(1.0);
  
  if (parallel == 0) {
    delay.setTimeMs(3*179);
    delay.setPan(-.2);
    delay.setModRate(1.1);
  } else if (parallel == 1) {
    delay.setTimeMs(3*218);
    delay.setPan(0.0);
    delay.setModRate(1.0);
  } else if (parallel == 2) {
    delay.setTimeMs(3*437);
    delay.setPan(0.2);
    delay.setModRate(0.9);
  }
  
  return delay;
}


stereofloat Disperse::process(stereofloat in) {
  stereofloat wet = stereofloat(0.0, 0.0);
  
  
  std::list<std::list<Delay>>::iterator parallelIt;
  for (parallelIt = this->delays.begin(); parallelIt != this->delays.end(); ++parallelIt){
      
    stereofloat serialVal = stereofloat(in.L(), in.R());

    std::list<Delay>::iterator serialIt;
    for (serialIt = parallelIt->begin(); serialIt != parallelIt->end(); ++serialIt){
      
      serialVal = serialIt->process(serialVal);
    }
    
    wet = stereofloat(serialVal.L() + wet.L(), serialVal.R() + wet.R());
  }
    
  return stereofloat((in.L() + wet.L()) /2.0, (in.R() + wet.R())/2.0);
}
