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
#include <memory>

#define MAX_PIPELINE (64)

#define CLAMP(X,MIN,MAX) X < MIN ? MIN : ( X > MAX ? MAX : X )

#define LUT_PRECISION (21)
#define LUT_FULL (10)
#define LUT_OUT_FRACT (16)



typedef int8_t TTP_S8;
typedef int16_t TTP_S16;
typedef int32_t TTP_S32;
typedef int64_t TTP_S64;

typedef uint8_t TTP_U8;
typedef uint16_t TTP_U16;
typedef uint32_t TTP_U32;
typedef uint64_t TTP_U64;

typedef TTP_S16 TTP_RAW;

typedef shared_ptr<TTP_RAW> RAW_HANDLE;

// precision declarations along the pipeline (only few examples here)
#define TANH_GAIN_INTEG (4)
#define TANH_GAIN_FRACT (4)
#define TANH_GAIN_FRACT_MULT ( 1 << TANH_GAIN_FRACT)
#define TANH_GAIN_INTEG_CLIP (( 1 << TANH_GAIN_INTEG) -1)

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
	static void clip(float &x, precision p_in, precision p_out){};
	static void roundclip(float &x, precision p_in, precision p_out){};

	static TTP_U64 ttp_lut_inverse( TTP_U32 n ) noexcept;


};

#endif /* TT_PLAYER_PRECISION_H_ */
