/*
 * TTPlayerPrecision.h
 *
 *  Created on: 12 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_PRECISION_H_
#define TT_PLAYER_PRECISION_H_

#include "tt_player_globaldefs.h"
#include <bitset>

#define MAX_PIPELINE (64)

#define CLAMP(X,MIN,MAX) X < MIN ? MIN : ( X > MAX ? MAX : X )

#define LUT_PRECISION (21)
#define LUT_FULL (10)

typedef short TTP_S8;
typedef int TTP_S16;
typedef long TTP_S32;
typedef long long TTP_S64;

typedef unsigned short TTP_U8;
typedef unsigned int TTP_U16;
typedef unsigned long TTP_U32;
typedef unsigned long long TTP_U64;

// precision declarations along the pipeline (only few examples here)
#define TANH_GAIN_INTEG (4)
#define TANH_GAIN_FRACT (4)

struct precision
{
	bool is_signed;  ///< sign
	int integ; ///< integer part
	int fract; ///< fractional part

	float normfactor;
};


class TTPlayerPrecision
{
public:
	TTPlayerPrecision();
	virtual ~TTPlayerPrecision();
	TTPlayerPrecision(const TTPlayerPrecision &other);

	static void truncate(float &x, precision p_in, precision p_out){};
	static void clip(float &x, precision p_in, precision p_out)
	{

	};
	static void roundclip(float &x, precision p_in, precision p_out){};

	static TTP_U64 ttp_lut_inverse( TTP_U32 n );


};

#endif /* TT_PLAYER_PRECISION_H_ */
