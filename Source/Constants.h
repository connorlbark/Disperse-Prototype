//
//  Constants.h
//  Disperse
//
//  Created by Connor Barker on 2/7/23.
//

#ifndef Constants_h
#define Constants_h

#define MIX_PARAM_ID "mix"

#define TIME_PARAM_ID "time"
#define FEEDBACK_PARAM_ID "feedback"
#define SPREAD_PARAM_ID "speed"
#define DISPERSION_PARAM_ID "dispersion"
#define NUM_VOICES_PARAM_ID "numVoices"
#define SEED_PARAM_ID "seed"

#define MAX_PARALLEL 8
#define MAX_SERIES 8
#define NUM_RANDOM_PARAMS 3

#define TIME_IDX 0
#define PAN_IDX 1
#define FEEDBACK_IDX 2

#define MAX_TIME_SPREAD 600 // can spread this much in positive and negative directions, with an overall minimum of 50ms
#define MAX_FEEDBACK_SPREAD 0.2
#define MAX_PAN_SPREAD 0.3

#define MAX_DELAY_TIME 2000.0

#define MAX_TIME_PARAM (MAX_DELAY_TIME - MAX_TIME_SPREAD)
#define MIN_TIME_PARAM 50.0



#endif /* Constants_h */
