//
//  Vibrato.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/25/23.
//

#ifndef Vibrato_hpp
#define Vibrato_hpp

#include <JuceHeader.h>
#include "../Utils/Types.hpp"
#include "../DSP/CircularBuffer.hpp"
#include "../DSP/Oscillator.hpp"

class Vibrato {
  CircularBuffer buf;
  
  float depth; // 0.0 to 1.0
  
  Oscillator osc;
  
public:
  Vibrato();
  
  void initialize(int maxSampsDepth);
  
  stereofloat process(stereofloat &in);
  
  void setOscillator(Oscillator);
  void setSpeed(float sampleRate, float hz);
  void setDepth(float depth);
};


#endif /* Vibrato_hpp */
