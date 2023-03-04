//
//  Disperse.cpp
//  Disperse
//
//  Created by Connor Barker on 1/20/23.
//

#include "Disperse.hpp"
#include <random>


Disperse::Disperse() {}

void Disperse::initialize(float sampleRate, int seed) {
  this->sampleRate = sampleRate;
  this->seed = seed;
  
  this->arrangement = {
    1,
  };
  resetDelays();
};


static std::mt19937 gen;
static std::uniform_real_distribution<> dist;
float Disperse::getRandomUniform(int parallelIdx, int seriesIdx, int paramIdx) {
  gen = std::mt19937(this->seed * this->simpleParamHash(parallelIdx, seriesIdx, paramIdx));
  dist = std::uniform_real_distribution<>(-1, 1);

  return dist(gen);
}

static int serialMax;
void Disperse::resetDelays() {
  this->delays.clear();
  
  for (int parallelIdx = 0; parallelIdx < this->arrangement.size(); parallelIdx++) {
    serialMax = this->arrangement.at(parallelIdx);
    
    std::vector<std::shared_ptr<Delay>> serialDelays;
    for (int serialIdx = 0; serialIdx < serialMax; serialIdx++) {
      serialDelays.push_back(this->createDelay(parallelIdx, serialIdx));
    }
    
    this->delays.push_back(serialDelays);
  }
  
  updateAllRandomParams();
}

void Disperse::updateDelays(void(Disperse::*update)(std::shared_ptr<Delay>, int, int)) {
  for (int parallelIdx = 0; parallelIdx < this->delays.size(); parallelIdx ++) {
    std::vector<std::shared_ptr<Delay>> serialDelays = this->delays.at(parallelIdx);
    
    for (int serialIdx = 0; serialIdx < serialDelays.size(); serialIdx++) {
      
      (this->*update)(serialDelays.at(serialIdx), parallelIdx, serialIdx);

    }
    
  }
}

void Disperse::updateAllRandomParams() {
  this->updateDelays(&Disperse::updateDelayFeedback);
  this->updateDelays(&Disperse::updateDelayTimeMs);
  this->updateDelays(&Disperse::updateDelayPan);
}


std::shared_ptr<Delay> Disperse::createDelay(int parallel, int series) {
  std::shared_ptr<Delay> delay = std::make_shared<Delay>();
  
  delay->initialize(sampleRate, MAX_DELAY_TIME);
  
  delay->setFeedback(0.5);
  delay->setModDepth(0.2);
  delay->setMix(1.0);
  
  return delay;
}

void Disperse::setMix(float mix) {
  this->mix = mix;
}

void Disperse::setFeedback(float feedback) {
  this->feedback = feedback;
  this->updateDelays(&Disperse::updateDelayFeedback);
}

void Disperse::setTimeMs(float timeMs) {
  this->timeMs = timeMs;
  this->updateDelays(&Disperse::updateDelayTimeMs);
}

void Disperse::setSpread(float spread) {
  this->spread = spread;
  updateSpread();
}
void Disperse::setDispersion(float dispersion) {
  this->dispersion = dispersion;
  updateDispersion();
}



static float randValue;
void Disperse::updateDelayFeedback(std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
  randValue = this->getRandomUniform(parallelIdx, serialIdx, FEEDBACK_IDX);
  
  randValue *= MAX_FEEDBACK_SPREAD;
  randValue *= this->dispersion;

  delay->setFeedback(this->feedback + randValue);
}

void Disperse::updateDelayTimeMs(std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
  randValue = this->getRandomUniform(parallelIdx, serialIdx, TIME_IDX);
  
  randValue *= MAX_TIME_SPREAD;

  randValue *= this->dispersion;
  delay->setTimeMs(this->timeMs + randValue);
}

void Disperse::updateDelayPan(std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
  randValue = this->getRandomUniform(parallelIdx, serialIdx, PAN_IDX);
  
  randValue *= MAX_PAN_SPREAD;
  randValue *= this->spread;

  delay->setPan(randValue);
}

void Disperse::updateSpread() {
  this->updateDelays(&Disperse::updateDelayPan);
}

void Disperse::updateDispersion() {
  this->updateDelays(&Disperse::updateDelayTimeMs);
  this->updateDelays(&Disperse::updateDelayFeedback);

}

void Disperse::setRandomSeed(int seed) {
  updateAllRandomParams();
}

void Disperse::setVoiceArrangement(std::vector<int> arrangement) {
  this->arrangement = arrangement;

  resetDelays();
}


static stereofloat wet;
static stereofloat disperseOut;
static stereofloat serial;

stereofloat &Disperse::process(stereofloat &in) {
  wet.L = 0.f;
  wet.R = 0.f;
  
  for (int parallelIdx = 0; parallelIdx < this->arrangement.size(); parallelIdx++) {
    serial.L = in.L;
    serial.R = in.R;
    for (int serialIdx = 0; serialIdx < this->arrangement.at(parallelIdx); serialIdx++) {
      serial = this->delays.at(parallelIdx).at(serialIdx)->process(serial);
    }
    
    wet.L += serial.L;
    wet.R += serial.R;
  }
  
  
  disperseOut.L = wet.L * mix + in.L * (1-mix);
  disperseOut.R = wet.R * mix + in.R * (1-mix);
  return disperseOut;
}
