//
//  CircularBuffer.hpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#ifndef CircularBuffer_hpp
#define CircularBuffer_hpp

#include <JuceHeader.h>
#include <vector>

template <typename T>
class CircularBuffer: public juce::AudioBuffer<T> {
private:
  int circularBufferIdx = 0; // defaults to the beginning of the buffer.
  
  int mapCircularIdxToBufferIdx(int numSamplesAgo) {
    int bufferSamplesAgo = this->circularBufferIdx - numSamplesAgo - 1;
    while (bufferSamplesAgo < 0) {
      bufferSamplesAgo += this->getNumSamples();
    };
    while (bufferSamplesAgo >= this->getNumSamples()) {
      bufferSamplesAgo -= this->getNumSamples();
    };
    return bufferSamplesAgo;
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
  
  CircularBuffer(int channels, int samples): juce::AudioBuffer<float>(channels, samples) {
    this->initialize();
  }

  /**
   ReadCircular: reads from the buffer according to the internal circular buffer index.
   
   Inputs:
      channel: channel to read from
      numSamplesAgo: number of samples in the past from the current time.
   */
  T readCircular(int channel, int numSamplesAgo) {
    int bufferIdx = this->mapCircularIdxToBufferIdx(numSamplesAgo);
    
    return this->getSample(channel, bufferIdx);
  };

  /**
   WriteCircular: Writes to the circular buffer, and updates the internal index.
   
   Inputs:
     in - Expects enough input samples to fill up all channels
   
   If given less channels, then the rest of the channels will be filled with 0.0. If given too many, the extra channels will be ignored.
   */
  void writeCircular(const std::vector<T> in) {
    for (int channelIdx = 0; channelIdx < this->getNumChannels(); channelIdx++) {
      float sample = 0.f;
      if (channelIdx < in.size()) {
        sample = in[channelIdx];
      }
      
      this->setSample(channelIdx, this->circularBufferIdx, sample);
    }
    
    incrementCircularIndex();
  };

};

#endif /* CircularBuffer_hpp */
