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
#include <functional>

#include "../Constants.h"

class Disperse {
private:
  float sampleRate;
  int seed;
  std::vector<int> arrangement;
  
  float mix;
  float feedback;
  float timeMs;
  float spread; // pan dilation
  float dispersion; // time random dilation
  
  // two-dimension list: first dimension is parallel delays, second dimension is serial delays.
  std::vector<std::vector<std::shared_ptr<Delay>>> delays;

  void resetDelays();
  std::shared_ptr<Delay> createDelay(int parallel, int series);
  
  // [-1.0, 1.0] even
  float getRandomUniform(int parallelIdx, int seriesIdx, int param);
  
  int simpleParamHash(int parallelIdx, int seriesIdx, int paramIdx) {
    return (paramIdx * MAX_PARALLEL * MAX_SERIES) + (seriesIdx * MAX_PARALLEL) + parallelIdx;
  };
  
  void updateDelays(void(Disperse::*)(std::shared_ptr<Delay>, int, int));
  
  void updateDelayFeedback(std::shared_ptr<Delay>, int, int);
  void updateDelayTimeMs(std::shared_ptr<Delay>, int, int);
  void updateDelayPan(std::shared_ptr<Delay>, int, int);

  void updateSpread();
  void updateDispersion();
  
  void updateAllRandomParams();

public:
  Disperse();
  
  void initialize(float sampleRate, int seed);
  
  stereofloat &process(stereofloat &in);
  
  // these opeartions will completely recreate the delays
  // (i.e., are not 'simple'
  void setVoiceArrangement(std::vector<int>);
  void setRandomSeed(int);
  
  // updates delays in-place
  void setMix(float);
  void setFeedback(float);
  void setTimeMs(float);
  void setSpread(float);
  void setDispersion(float);
  
  float getMix();
  float getFeedback();
  float getTimeMs();
  float getSpread();
  float getDispersion();
};

#endif /* Disperse_hpp */
