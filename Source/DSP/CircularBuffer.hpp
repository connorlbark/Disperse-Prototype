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

template <typename T>
class CircularBuffer: public juce::AudioBuffer<T> {
private:
  int circularBufferIdx = 0; // defaults to the beginning of the buffer.
  int numSamples = 0;
  
//  float * L;
//  float * R;
  
  int mapCircularIdxToBufferIdx(int numSamplesAgo) {
    int bufferSamplesAgo = this->circularBufferIdx - numSamplesAgo - 1;

    int modResult = bufferSamplesAgo % numSamples;
    return modResult >= 0 ? modResult : modResult+numSamples;
  };
  
  void incrementCircularIndex() {
    this->circularBufferIdx += 1;
    if (this->circularBufferIdx == this->getNumSamples()) {
      this->circularBufferIdx = 0;
    }
  }
  
  void initialize() {
    for (int sampleIdx = 0; sampleIdx < this->getNumSamples(); sampleIdx++) {
      for (int channelIdx = 0; channelIdx < this->getNumChannels(); channelIdx++) {
        this->setSample(channelIdx, sampleIdx, 0.f);
      }
    }
  }
public:
  
  CircularBuffer(int samples): juce::AudioBuffer<float>(2, samples) {
    this->numSamples = samples;
    this->initialize();
//    this-> L = this->getWritePointer(0);
//    this-> R = this->getWritePointer(1);
  }

  /**
   ReadCircular: reads from the buffer according to the internal circular buffer index.
   
   Inputs:
      channel: channel to read from
      numSamplesAgo: number of samples in the past from the current time.
   */
  stereofloat readCircular(int numSamplesAgo) {
    int bufferIdx = this->mapCircularIdxToBufferIdx(numSamplesAgo);
    
    const float * bufL = this->getReadPointer(0);
    const float * bufR = this->getReadPointer(1);

    
    return stereofloat(*(bufL+bufferIdx), *(bufR+bufferIdx));
  };

  void writeCircular(float L, float R) {
    float * bufL = this->getWritePointer(0);
    float * bufR = this->getWritePointer(1);

    *(bufL + this->circularBufferIdx) = L;
    *(bufR + this->circularBufferIdx) = L;

    incrementCircularIndex();
  }

};

#endif /* CircularBuffer_hpp */
