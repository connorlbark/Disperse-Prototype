//
//  Delay.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/31/23.
//

#ifndef Delay_hpp
#define Delay_hpp

#include "../DSP/CircularBuffer.hpp"
#include "../Utils/Types.hpp"
#include "Vibrato.hpp"

#define MAX_DELAY_MS 2000.0

class Delay {
private:
  float sampleRate;
  
  CircularBuffer<float> buf;
  Vibrato vibrato;
  
  float feedback;
  int timeSamps;
  float pan;
  
  float mix;

  stereofloat fxLoop(stereofloat in);
public:
  Delay();
  Delay(float sampleRate, float maxTimeMs);

  void initialize(float sampleRate, float maxTimeMs);
  
  stereofloat process(stereofloat in);
  
  void setModDepth(float depth);
  void setModRate(float hz);
  void setFeedback(float feedback);
  void setTimeMs(float timeMs);
  void setPan(float pan);
  void setMix(float mix);
};

#endif /* Delay_hpp */
