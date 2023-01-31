//
//  Oscillator.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/28/23.
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <JuceHeader.h>

class Oscillator {
public:
  Oscillator() {
    this->oscFunction = [](float x) { return std::sinf(x); };
    this->oscRange = juce::MathConstants<float>::twoPi;
  }

  void setFrequency (float frequency, float sampleRate)
  {
      auto cyclesPerSample = frequency / sampleRate;
      angleDelta = cyclesPerSample * this->oscRange;
  }
  
  forcedinline float getNextSample() noexcept
  {
      auto currentSample = this->oscFunction (currentAngle);
      updateAngle();
      return currentSample;
  }
  
  forcedinline void updateAngle() noexcept
  {
      currentAngle += angleDelta;
      if (currentAngle >= this->oscRange)
          currentAngle -= this->oscRange;
  }

private:
  float currentAngle = 0.0f, angleDelta = 0.0f;
  
  std::function<float(float)> oscFunction;
  float oscRange;

};
#endif /* Oscillator_hpp */
