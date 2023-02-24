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
  this->buf = CircularBuffer(maxSampsDepth);
}

static float oscVal;
static float modulation;
static float delay;
static float depthSamps;

stereofloat Vibrato::process(stereofloat &in) {

  oscVal = this->osc.getNextSample();
  
  modulation = ((oscVal + 1.f) / 2.f);
  // modulation from [0.f, this->depth]
  depthSamps = this->depth * (this->buf.getNumSamples()) + 1.f;

  delay = depthSamps / 2.f + modulation * depthSamps / 2.f;

  this->buf.writeCircular(in);
  return linearInterpolation(this->buf, delay);
}

void Vibrato::setSpeed(float sampleRate, float hz) {
  this->osc.setFrequency(hz, sampleRate);
}

void Vibrato::setDepth(float depth) {
  this->depth = depth;
}
