
#ifndef TT_GLOBALDEFS_H_
#define TT_GLOBALDEFS_H_

#define _DEBUG_
#ifdef _DEBUG_
	#define _DEBUG_RC_P
//	#define _TEST_SIGNAL_
#endif
#define _PROGRESS_CONSOLE

#define RAW_BITDEPTH (16)

#define DEFAULT_LUT_BITDEPTH (10)
#define DEFAULT_CURVE ATAN

#define EUL (2.71828)
#define EUL_SQUARED (7.3890461584)

//#define _FIXED_IMP
#define INVLN2 (1.44269)

#define POW2(X) ( pow(2.0, X ) )

#include <iostream>
#include "tt_player_message.h"
#include "tt_player_exception.h"
//#include "tt_player_smartpointer.h"
//typedef TTPlayerSmartPointer<int> SP_STREAM;
struct StreamParameters
{
	int bitPerSample;
	float samplingFrequency;
	float lengthInSeconds;
	long lengthInSamples;
};

#endif /* TT_GLOBALDEFS_H_ */
