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
#include <algorithm>

stereofloat linearInterpolation(CircularBuffer<float> &buf, float idx);
stereofloat cubicInterpolation(CircularBuffer<float> &buf, float idx);


inline int msToSamps(float sampleRate, float ms) {
  return ceil(sampleRate * (ms / 1000.f));
}

inline stereofloat sinPan(stereofloat in, float pan) {

  float crossValue = (pan + 1.f) / 2.f;
  
  float gainL = sin((1 - crossValue)*juce::MathConstants<float>::halfPi);
  float gainR = sin(crossValue*juce::MathConstants<float>::halfPi);

  return stereofloat(in.L * gainL, in.R * gainR);
}
#endif /* Math_hpp */
