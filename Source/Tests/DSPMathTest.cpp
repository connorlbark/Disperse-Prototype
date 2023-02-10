////
////  LinearInterpolationTest.cpp
////  Disperse
////
////  Created by Connor Barker on 1/30/23.
////
//
//#include "DSPMathTest.hpp"
//#include "../DSP/Math.hpp"
//
//void DSPMathTest::runAllTests() {
//  linearInterpolationTest();
//}
//
//
//void DSPMathTest::linearInterpolationTest() {
//  beginTest("Linear Interpolation Test");
//  
//  CircularBuffer<float> buf = CircularBuffer<float>(2, 10);
//  
//  buf.writeCircular({ 0.0, 9.0});
//  buf.writeCircular({ 1.0, 8.0});
//  buf.writeCircular({ 2.0, 7.0});
//  buf.writeCircular({ 3.0, 6.0});
//  buf.writeCircular({ 4.0, 5.0});
//  buf.writeCircular({ 5.0, 4.0});
//  buf.writeCircular({ 6.0, 3.0});
//  buf.writeCircular({ 7.0, 2.0});
//  buf.writeCircular({ 8.0, 1.0});
//  buf.writeCircular({ 9.0, 0.0});
//  
//  // check "pure" indices - backwards
//  expectEquals(linearInterpolation(buf, 0.0), stereofloat(9.0, 0.0));
//  expectEquals(linearInterpolation(buf, 1.0), stereofloat(8.0, 1.0));
//  expectEquals(linearInterpolation(buf, 2.0), stereofloat(7.0, 2.0));
//  expectEquals(linearInterpolation(buf, 3.0), stereofloat(6.0, 3.0));
//  expectEquals(linearInterpolation(buf, 4.0), stereofloat(5.0, 4.0));
//  expectEquals(linearInterpolation(buf, 5.0), stereofloat(4.0, 5.0));
//  expectEquals(linearInterpolation(buf, 6.0), stereofloat(3.0, 6.0));
//  expectEquals(linearInterpolation(buf, 7.0), stereofloat(2.0, 7.0));
//  expectEquals(linearInterpolation(buf, 8.0), stereofloat(1.0, 8.0));
//  expectEquals(linearInterpolation(buf, 9.0), stereofloat(0.0, 9.0));
//  
//  // check "impure" indices
//  
//  expectEquals(linearInterpolation(buf, 0.5), stereofloat(8.5, 0.5));
//  expectEquals(linearInterpolation(buf, 0.6), stereofloat(8.4, 0.6));
//  expectEquals(linearInterpolation(buf, 0.9), stereofloat(8.1, 0.9));
//  expectEquals(linearInterpolation(buf, 2.6), stereofloat(6.4, 2.6));
//  
//  buf.writeCircular({ 0.0, 56.0});
//  buf.writeCircular({ 5.0, 54.0});
//  buf.writeCircular({ 10.0, 30.0});
//  buf.writeCircular({ 13.0, 20.0});
//  buf.writeCircular({ 14.0, 22.0});
//  buf.writeCircular({ 17.0, 12.0});
//  buf.writeCircular({ 10.0, 17.0});
//  buf.writeCircular({ 10.0, 20.0});
//  buf.writeCircular({ 3.0, 2.0});
//  buf.writeCircular({ 0.0, 0.0});
//  
//  // check with deltas bigger than 1.0
//  expectEquals(linearInterpolation(buf, 0.5), stereofloat(1.5, 1.0));
//  expectEquals(linearInterpolation(buf, 1.5), stereofloat(6.5, 11.0));
//  expectEquals(linearInterpolation(buf, 3.25), stereofloat(11.75, 15.75));
//
//
//
//}
