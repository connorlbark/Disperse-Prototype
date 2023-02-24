//
//  Math.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/28/23.
//

#ifndef Math_hpp
#define Math_hpp

#include "../Utils/Types.hpp"
#include "CircularBuffer.hpp"
#include <JuceHeader.h>
#include <math.h>

stereofloat &linearInterpolation(CircularBuffer &buf, float idx);
stereofloat cubicInterpolation(CircularBuffer &buf, float idx);


inline int msToSamps(float sampleRate, float ms) {
  return ceil(sampleRate * (ms / 1000.f));
}


static float crossValue;
static float gainL;
static float gainR;
static stereofloat out;

inline stereofloat &sinPan(stereofloat &in, float pan) {

  crossValue = (pan + 1.f) / 2.f;
  
  gainL = sin((1 - crossValue)*juce::MathConstants<float>::halfPi);
  gainR = sin(crossValue*juce::MathConstants<float>::halfPi);

  out.L = in.L * gainL;
  out.R = in.R * gainR;
  return out;
}
#endif /* Math_hpp */
