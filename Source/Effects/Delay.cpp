//
//  Delay.cpp
//  Disperse - Shared Code
//
//  Created by Connor Barker on 1/31/23.
//

#include "Delay.hpp"
#include "../DSP/Math.hpp"
#include "../DSP/Saturation.hpp"
#include <algorithm>

Delay::Delay() : buf(0), vibrato() {
  
};

Delay::Delay(float sampleRate, float maxTimeMs) : Delay() {
  this->initialize(sampleRate, maxTimeMs);
};


void Delay::initialize(float sampleRate, float maxTimeMs) {
  this->sampleRate = sampleRate;
  int maxTimeSamps = msToSamps(sampleRate, maxTimeMs);
  
  buf = CircularBuffer(maxTimeSamps);

  // max vibrato is 15ms back
  vibrato.initialize(msToSamps(sampleRate, 15.f));
  
  this->setModRate(1.0);
  this->setModDepth(0.0);
  
  this->pan = 0.f;
  this->setTimeMs(100.f);
  this->feedback = 0.f;
  
  this->mix = 0.5;
}


void Delay::setTimeMs(float timeMs) {
  this->timeSamps = msToSamps(sampleRate, timeMs);
}

void Delay::setFeedback(float feedback) {
  this->feedback = feedback;
}

void Delay::setModRate(float hz) {
  this->vibrato.setSpeed(this->sampleRate, hz);
}

void Delay::setModDepth(float depth) {
  this->vibrato.setDepth(depth);
}

void Delay::setPan(float pan) {
  this->pan = pan;
}

void Delay::setMix(float mix) {
  this->mix = mix;
}

static stereofloat fxOut;

stereofloat &Delay::fxLoop(stereofloat &in) {
  in = this->vibrato.process(in);


  fxOut.L = softClip(in.L, 0.7);
  fxOut.R = softClip(in.R, 0.7);
  return fxOut;
}

static stereofloat delayedValue;
static stereofloat dryFeedback;
static stereofloat wet;
static stereofloat delayOut;

stereofloat &Delay::process(stereofloat &in) {
  
  
  delayedValue = this->buf.readCircular(this->timeSamps);
  
  dryFeedback.L = in.L + (delayedValue.L) * this->feedback;
  dryFeedback.R = in.R + (delayedValue.R) * this->feedback;

  if (this->pan != 0.f) {
    dryFeedback = sinPan(dryFeedback, this->pan);
  }

  this->buf.writeCircular(dryFeedback);

  
  wet = this->fxLoop(delayedValue);
  
  delayOut.L = wet.L * mix + in.L * (1-mix);
  delayOut.R = wet.R * mix + in.R * (1-mix);
  return delayOut;
  
}
