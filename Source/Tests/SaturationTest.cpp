//
//  SaturationTest.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/31/23.
//

#include "SaturationTest.hpp"

#include "../DSP/Saturation.hpp"

void SaturationTest::runAllTests() {
  this->testTanhSoftClip();
}

void SaturationTest::testTanhSoftClip() {
  beginTest("Tanh soft clip");
  
  this->expectWithinAbsoluteError(softClip(.93, 0.826), .919, 0.01);
  this->expectWithinAbsoluteError(softClip(.99, 0.72), .929, 0.01);
}
