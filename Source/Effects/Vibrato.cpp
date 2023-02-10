//
//  Vibrato.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/25/23.
//

#include "Vibrato.hpp"
#include "../DSP/Math.hpp"

Vibrato::Vibrato() : buf(0) {}

void Vibrato::initialize(int maxSampsDepth) {
  this->buf = CircularBuffer<float>(maxSampsDepth);
}

stereofloat Vibrato::process(stereofloat in) {

  float osc = this->osc.getNextSample();
  
  float modulation = ((osc + 1.f) / 2.f);
  // modulation from [0.f, this->depth]
  float depthSamps = this->depth * (this->buf.getNumSamples()) + 1.f;

  float delay = depthSamps / 2.f + modulation * depthSamps / 2.f;
  this->buf.writeCircular(in.L, in.R);
  stereofloat out = linearInterpolation(this->buf, delay);

  return out;
//  return stereofloat(this->buf.readCircular(0, 800), this->buf.readCircular(1, 800));
}

void Vibrato::setSpeed(float sampleRate, float hz) {
  this->osc.setFrequency(hz, sampleRate);
}

void Vibrato::setDepth(float depth) {
  this->depth = depth;
}
