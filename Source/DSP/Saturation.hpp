//
//  Saturation.hpp
//  Disperse - VST3
//
//  Created by Connor Barker on 1/31/23.
//

#ifndef Saturation_hpp
#define Saturation_hpp

// p: [0, 1.0), harshness of clipping
// https://www.desmos.com/calculator/8jvusnnrxp
double softClip(double x, double p);

#endif /* Saturation_hpp */
