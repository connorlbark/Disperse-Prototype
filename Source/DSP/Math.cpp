//
//  Math.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/28/23.
//

#include "Math.hpp"


static int lowerIdx;
static float decimal;
static stereofloat lowerSample;
static stereofloat upperSample;
static stereofloat linOut;

stereofloat &linearInterpolation(CircularBuffer &buf, float idx) {
  
  lowerIdx = (int)idx;

  if (idx == lowerIdx) {
    linOut = buf.readCircular(lowerIdx);
    return linOut;
  }
  
  
  decimal = idx - lowerIdx;
  
  lowerSample = buf.readCircular(lowerIdx);
  upperSample = buf.readCircular(lowerIdx+1);
  
  linOut.L = lowerSample.L + (upperSample.L - lowerSample.L) * decimal;
  linOut.R = lowerSample.R + (upperSample.R - lowerSample.R) * decimal;

  
  return linOut;

}


float calcCubicInterpolation(
   float y0,float y1,
   float y2,float y3,
   float mu)
{
   float a0,a1,a2,a3,mu2;

   mu2 = mu*mu;
   a0 = y3 - y2 - y0 + y1;
   a1 = y0 - y1 - a0;
   a2 = y2 - y0;
   a3 = y1;

   return(a0*mu*mu2+a1*mu2+a2*mu+a3);
}



stereofloat cubicInterpolation(CircularBuffer &buf, float idx) {
  int intIdx = floorl(idx);
  float x = idx - intIdx;
  
  stereofloat y0 = buf.readCircular(intIdx-1);
  stereofloat y1 = buf.readCircular(intIdx);
  stereofloat y2 = buf.readCircular(intIdx+1);
  stereofloat y3 = buf.readCircular(intIdx+2);


  return stereofloat(
                     calcCubicInterpolation(y0.L, y1.L, y2.L, y3.L, x),
                     calcCubicInterpolation(y0.R, y1.R, y2.R, y3.R, x)
                     );
}



