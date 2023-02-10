//
//  Math.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/28/23.
//

#include "Math.hpp"

stereofloat linearInterpolation(CircularBuffer<float> &buf, float idx) {
  
  if (idx == floor(idx)) {
    return buf.readCircular(floorl(idx));
  }
  
  long lowerIdx = floorl(idx);
  
  float decimal = idx - lowerIdx;
  
  stereofloat lowerSample = buf.readCircular((int)lowerIdx);
  stereofloat upperSample = buf.readCircular((int)lowerIdx+1);
  
  float L = lowerSample.L + (upperSample.L - lowerSample.L) * decimal;
  float R = lowerSample.R + (upperSample.R - lowerSample.R) * decimal;

  return stereofloat(L, R);

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



stereofloat cubicInterpolation(CircularBuffer<float> &buf, float idx) {
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



