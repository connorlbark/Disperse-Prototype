//
//  CircularBuffer.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#ifndef CircularBuffer_hpp
#define CircularBuffer_hpp

#include <JuceHeader.h>
#include "../Utils/Types.hpp"

class CircularBuffer: public juce::AudioBuffer<float> {
private:
  int circularBufferIdx = 0; // defaults to the beginning of the buffer.
  int numSamples = 0;
  
  const float *readL;
  const float *readR;
  float *writeL;
  float *writeR;
  
  int mapCircularIdxToBufferIdx(int numSamplesAgo);
  void incrementCircularIndex();
  void initialize();
  
public:
  
  CircularBuffer(int samples): juce::AudioBuffer<float>(2, samples) {
    this->numSamples = samples;
    this->initialize();
  }

  /**
   ReadCircular: reads from the buffer according to the internal circular buffer index.
   
   Inputs:
      channel: channel to read from
      numSamplesAgo: number of samples in the past from the current time.
   */
  stereofloat readCircular(int numSamplesAgo);

  void writeCircular(stereofloat &in);
};

#endif /* CircularBuffer_hpp */
