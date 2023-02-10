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


float Disperse::getRandomUniform(int parallelIdx, int seriesIdx, int paramIdx) {
  std::mt19937 gen(this->seed * this->simpleParamHash(parallelIdx, seriesIdx, paramIdx));
  std::uniform_real_distribution<> dist(-1, 1);

  return dist(gen);
}

void Disperse::resetDelays() {
  this->delays.clear();
  
  for (int parallelIdx = 0; parallelIdx < this->arrangement.size(); parallelIdx++) {
    int serialMax = this->arrangement.at(parallelIdx);
    
    std::vector<std::shared_ptr<Delay>> serialDelays;
    for (int serialIdx = 0; serialIdx < serialMax; serialIdx++) {
      serialDelays.push_back(this->createDelay(parallelIdx, serialIdx));
    }
    
    this->delays.push_back(serialDelays);
  }
  
  updateAllRandomParams();
}

void Disperse::updateDelays(std::function< void(std::shared_ptr<Delay>, int, int) > lambda) {
  for (int parallelIdx = 0; parallelIdx < this->delays.size(); parallelIdx ++) {
    std::vector<std::shared_ptr<Delay>> serialDelays = this->delays.at(parallelIdx);
    
    for (int serialIdx = 0; serialIdx < serialDelays.size(); serialIdx++) {
      
      lambda(serialDelays.at(serialIdx), parallelIdx, serialIdx);

    }
    
  }
}

void Disperse::updateAllRandomParams() {
  updateFeedback();
  updateTimeMs();
  updatePan();
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
  updateFeedback();
}

void Disperse::setTimeMs(float timeMs) {
  this->timeMs = timeMs;
  updateTimeMs();
}

void Disperse::setSpread(float spread) {
  this->spread = spread;
  updateSpread();
}
void Disperse::setDispersion(float dispersion) {
  this->dispersion = dispersion;
  updateDispersion();
}

void Disperse::updateFeedback() {
  this->updateDelays([&](std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
    float randValue = this->getRandomUniform(parallelIdx, serialIdx, FEEDBACK_IDX);
    
    randValue *= MAX_FEEDBACK_SPREAD;
    randValue *= this->dispersion;

    delay->setFeedback(this->feedback + randValue);
  });
}

void Disperse::updateTimeMs() {
  this->updateDelays([&](std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
    float randValue = this->getRandomUniform(parallelIdx, serialIdx, TIME_IDX);
    
    randValue *= MAX_TIME_SPREAD;

    randValue *= this->dispersion;
    delay->setTimeMs(this->timeMs + randValue);
  });
}

void Disperse::updatePan() {
  this->updateDelays([&](std::shared_ptr<Delay> delay, int parallelIdx, int serialIdx) {
    float randValue = this->getRandomUniform(parallelIdx, serialIdx, PAN_IDX);
    
    randValue *= MAX_PAN_SPREAD;
    randValue *= this->spread;

    delay->setPan(randValue);
  });

}

void Disperse::updateSpread() {
  updatePan();
}

void Disperse::updateDispersion() {
  updateTimeMs();
  updateFeedback();

}

void Disperse::setRandomSeed(int seed) {
  updateAllRandomParams();
}

void Disperse::setVoiceArrangement(std::vector<int> arrangement) {
  this->arrangement = arrangement;

  resetDelays();
}


stereofloat Disperse::process(stereofloat in) {
  stereofloat wet = stereofloat(0.0, 0.0);
  
  
//  std::cout << "start. " << this->delays.size() << std::endl;
  std::vector<std::vector<std::shared_ptr<Delay>>>::iterator parallelIt;
  for (parallelIt = this->delays.begin(); parallelIt != this->delays.end(); ++parallelIt){
      
//    std::cout << "Parallel Delays!" << std::endl;
    
    stereofloat serialVal = stereofloat(in.L, in.R);
    std::vector<std::shared_ptr<Delay>>::iterator serialIt;
    for (serialIt = parallelIt->begin(); serialIt != parallelIt->end(); ++serialIt){
      
      serialVal = serialIt->get()->process(serialVal);
    }
    
    wet = stereofloat(serialVal.L/this->arrangement.size() + wet.L, serialVal.R/this->arrangement.size() + wet.R
                      );
  }
    
  return stereofloat((in.L + wet.L) / 2.0, (in.R + wet.R)/ 2.0);
}
