//
//  Math.cpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/28/23.
//

#include "Math.hpp"

stereofloat linearInterpolation(CircularBuffer<float> &buf, float idx) {
  
  if (idx == floor(idx)) {
    return stereofloat(buf.readCircular(0, floorl(idx)), buf.readCircular(1, floorl(idx)));
  }
  
  long lowerIdx = floorl(idx);
  
  float decimal = idx - lowerIdx;
  
  float lowerSampleL = buf.readCircular(0, (int)lowerIdx);
  float upperSampleL = buf.readCircular(0, (int)lowerIdx+1);

  float lowerSampleR = buf.readCircular(1, (int)lowerIdx);
  float upperSampleR = buf.readCircular(1, (int)lowerIdx+1);
  
  float L = lowerSampleL + (upperSampleL - lowerSampleL) * decimal;
  float R = lowerSampleR + (upperSampleR - lowerSampleR) * decimal;

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
  
  float y0L = buf.readCircular(0, intIdx-1);
  float y1L = buf.readCircular(0, intIdx);
  float y2L = buf.readCircular(0, intIdx+1);
  float y3L = buf.readCircular(0, intIdx+2);

  float y0R = buf.readCircular(1, intIdx-1);
  float y1R = buf.readCircular(1, intIdx);
  float y2R = buf.readCircular(1, intIdx+1);
  float y3R = buf.readCircular(1, intIdx+2);

  return stereofloat(
                     calcCubicInterpolation(y0L, y1L, y2L, y3L, x),
                     calcCubicInterpolation(y0R, y1R, y2R, y3R, x)
                     );
}



