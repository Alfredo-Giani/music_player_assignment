/*
 * TTPlayerPrecision.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: alfre
 */

#include "tt_player_precision.h"
#ifdef _TEST_RC_P
#include "tt_player_instrumentation.h"
#endif

#define _TEST_SIGNAL_

TTPlayerPrecision::TTPlayerPrecision() {
	// TODO Auto-generated constructor stub

}

TTPlayerPrecision::~TTPlayerPrecision() {
	// TODO Auto-generated destructor stub
}

TTPlayerPrecision::TTPlayerPrecision(const TTPlayerPrecision &other) {
	// TODO Auto-generated constructor stub

}

// NOTE: this code has been ported from Python so is not fully C optimised.
TTP_U64 TTPlayerPrecision::ttp_lut_inverse( const TTP_U32 n )
{

    // the range of the input in nbits - 8
    TTP_U8 r = 0;

    //----------------------------------
	// this is just a very quick (and very bad) implementation of a bit range finder for the sake of the exercise.
	// hopefully I will have time to code something better. on top of my head, a set of comparators would do
	// because the input is bandwidth (bitdepth) bound.
	TTP_S16 r_temp = 0;
	if (n > (1 << LUT_FULL) - 1)
		r_temp = (floor(log2( static_cast<float>(n) )) - LUT_FULL ) + 1;

	r_temp = (r_temp < 0) ? 0 : r_temp;
	r = static_cast<TTP_U8>(r_temp);

	//--------------------------------------------------------------------------------------------------------------------------------------------
	// INPUT CONDITIONING
	//
	// NOTE: all this section needs refactoring when the truncate() function is completed
	//
	// input range right bit shift. this is part of the LUT input rc point since it does not extra r LSB (i.e. it does not fractional precision)
	// in the documentation right shift operations are considered lossless i.e. the simply move the floating point to the left
	// in C a right shift is lossy i.e. fractional precision is lost

	// apply range shift
	TTP_U32 n_ishift = n >> r;

    // this clamp simulates a truncation point
    TTP_U32 n_clamp = CLAMP( n_ishift, 1, (1 << LUT_FULL) -1 );


#ifdef _TEST_SIGNAL_
    std::cout << "n = " << n << " n_ishift = " << n_ishift << " n_clamp = " << n_clamp << " r = " << r << "\n";

#endif

#ifdef _TEST_RC_P

    //printf("n = %d n_ishift = %d n_clamp = %d range = %d\n", n, n_ishift, n_clamp, r);

    // test the truncation point
    precision p_in, p_out;
    p_in.integ = 25 - r;
    p_in.fract = 0; // in the documentation this is -r, but the clip of the fractional part has happened already (see above)
    p_in.is_signed = false;

    p_out.integ = LUT_FULL;
    p_out.fract = 0;
	p_in.is_signed = false;

    TTPlayerInstrumentation::testTruncation(n_ishift, p_in, p_out, "reciprocal LUT input RC in tt_player_processor");
#endif

    //-------------------------------------------------------------------------------------------------------------------------------------------



    // 8 bit lookup table output (simulation of the values stored in a memory)
    TTP_U64 lut_output = floor(pow(2.0 , LUT_PRECISION)/n_clamp);

    // rescaling for range and output fractional precision
    TTP_U64 lut_output_resc = ( (lut_output << LUT_OUT_FRACT ) >> r );

    return lut_output_resc;
}

