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

Delay::Delay() : buf(0, 0), vibrato() {
  
};

Delay::Delay(float sampleRate, float maxTimeMs) : Delay() {
  this->initialize(sampleRate, maxTimeMs);
};


void Delay::initialize(float sampleRate, float maxTimeMs) {
  this->sampleRate = sampleRate;
  int maxTimeSamps = msToSamps(sampleRate, maxTimeMs);
  
  buf = CircularBuffer<float>(2, maxTimeSamps);
  
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

stereofloat Delay::fxLoop(stereofloat in) {
  in = this->vibrato.process(in);
  
  return stereofloat(softClip(in.L(), 0.7), softClip(in.R(), 0.7));
}

stereofloat Delay::process(stereofloat in) {
  
  stereofloat delayedValue =
              stereofloat(
                this->buf.readCircular(0, this->timeSamps),
                this->buf.readCircular(1, this->timeSamps));
           
  stereofloat dryFeedback = stereofloat((in.L() + delayedValue.L()) * this->feedback, (in.R() + delayedValue.R()) * this->feedback);
  
  dryFeedback = sinPan(dryFeedback, this->pan);
  this->buf.writeCircular({dryFeedback.L(), dryFeedback.R()});
  
  
  stereofloat wet = this->fxLoop(delayedValue);
  return stereofloat(wet.L() * mix + in.L() * (1-mix),
                     wet.R() * mix + in.R() * (1-mix));
  
}
