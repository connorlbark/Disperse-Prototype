//
//  CircularBuffer.cpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/20/23.
//

#include "CircularBuffer.hpp"



static int bufferSamplesAgo;
int CircularBuffer::mapCircularIdxToBufferIdx(int numSamplesAgo) {
  
  
  bufferSamplesAgo = this->circularBufferIdx - numSamplesAgo - 1;
  
  if (bufferSamplesAgo >= 0) {
    return bufferSamplesAgo;
  } else {
    int numBufferIterationsAgo = std::ceil(-bufferSamplesAgo / (float)this->numSamples);
    
    return bufferSamplesAgo + numBufferIterationsAgo * numSamples;
  }
};

void CircularBuffer::incrementCircularIndex() {
  this->circularBufferIdx += 1;
  if (this->circularBufferIdx == this->getNumSamples()) {
    this->circularBufferIdx = 0;
  }
}

void CircularBuffer::initialize() {
  for (int sampleIdx = 0; sampleIdx < this->getNumSamples(); sampleIdx++) {
    for (int channelIdx = 0; channelIdx < this->getNumChannels(); channelIdx++) {
      this->setSample(channelIdx, sampleIdx, 0.f);
    }
  }
  
  this->readL = this->getReadPointer(0);
  this->readR = this->getReadPointer(1);
  this->writeL = this->getWritePointer(0);
  this->writeR = this->getWritePointer(1);
}
/**
 ReadCircular: reads from the buffer according to the internal circular buffer index.
 
 Inputs:
    channel: channel to read from
    numSamplesAgo: number of samples in the past from the current time.
 */
stereofloat CircularBuffer::readCircular(int numSamplesAgo) {
  int bufferIdx = this->mapCircularIdxToBufferIdx(numSamplesAgo);
  
  return stereofloat(*(readL+bufferIdx), *(readR+bufferIdx));
};

void CircularBuffer::writeCircular(stereofloat &in) {

  *(writeL + this->circularBufferIdx) = in.L;
  *(writeR + this->circularBufferIdx) = in.R;

  incrementCircularIndex();
}
