//
//  Math.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/25/23.
//

#ifndef Math_hpp
#define Math_hpp

#include "../Utils/Types.hpp"

namespace dspmath {

stereofloat pan(stereofloat stereoSample, float pan);

int msToSamps(float sampleRate, float ms);
float sampsToMs(float sampleRate, int samps);

}


#endif /* Math_hpp */
