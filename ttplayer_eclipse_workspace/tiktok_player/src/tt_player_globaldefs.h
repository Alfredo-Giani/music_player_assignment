
#ifndef TT_GLOBALDEFS_H_
#define TT_GLOBALDEFS_H_

#define _DEBUG_

#define RAW_BITDEPTH (16)

#define DEFAULT_LUT_BITDEPTH (10)
#define DEFAULT_CURVE ATAN

#define EUL (2.71828)
#define EUL_SQUARED (7.3890461584)

//#define _FIXED_IMP
#define INVLN2 (1.44269)

#include "tt_player_message.h"
#include "tt_player_exception.h"
//#include "tt_player_smartpointer.h"
//typedef TTPlayerSmartPointer<int> SP_STREAM;
struct StreamParameters
{
	int bitPerSample;
	float samplingFrequency;
};

#endif /* TT_GLOBALDEFS_H_ */
