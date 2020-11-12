/*
 * tt_player_processor.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */
#include "tt_player_processor.h"

// this will be defined in the unit test

#ifdef _TEST_RC_P
#include "tt_player_instrumentation.h"
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define TANH_UNIT_GAIN ( 1 << TANH_GAIN_FRACT) // fixed point (as integer) unitary squared gain. 4 bits of fractional precision therefore (1 << 4) = 16



float TangentHSoftClipper::getCurveValue(float x)
{

	float retVal = x;

	//(e^2x - 1)/(e^2x + 1)

	float expval = pow(EUL_SQUARED,x);
	retVal =  (expval - 1.0)/(expval + 1.0);

	return retVal;

}

// crudely ported from python...
TTP_U16 TangentHSoftClipper::getCurveValue(TTP_U16 x, float gain)
{

	TTP_U8 int_gain = floor(gain * TANH_UNIT_GAIN); // (1 << 4) gain has precision. this could

	// TODO: convert to signed
	//calculate the square and apply round and clip point

	TTP_S16 x_s = static_cast<TTP_S16>(static_cast<TTP_S32>(x) - (1 << 15));

	// calculate the square
    TTP_U64 x_sq = x_s *x_s;

    //clamp x_sq to remove asymmetry
    TTP_U32 x_sq_cl = CLAMP(x_sq, 0, pow(2.0,32)-1); // TODO replace with bit shift

    //apply squared gain
    TTP_U16 int_gain_sq = int_gain*int_gain;
    TTP_U64 xg = x_sq_cl * int_gain_sq;

    //apply round and clip point
    TTP_U32 xg_rc = floor(xg * pow(2.0, -15 -8));

    // calculate (27 + xg)
    TTP_U32 numerator = 27*pow(2.0,15) + xg_rc;

    //calculate denominator (n in the doc)
    TTP_U32 denominator = numerator + xg_rc * pow(2.0 , 3);

    // calculate the inverse m
	TTP_U64 m = TTPlayerPrecision::ttp_lut_inverse(denominator);

    //multiply the inverse and the numerator
    TTP_U64 ratio = m*numerator;

    //multiply by x_s
    TTP_S64 y = x_s * ratio;

    //apply output rc
    TTP_S16 y_rc = floor(y * pow(2.0, - LUT_PRECISION)); // TODO replace with bit shift

    // TO DO: CONVERT TO UNSIGNED!
    TTP_U16 y_u = static_cast<TTP_U16>(static_cast<TTP_S32>(y_rc) + (1 << 15));

    return y_u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LookupTable::LookupTable()
:npoints(2)
,address_bitdepth(8)
,value_bitdepth(10)
{
	pAddress = (int* )malloc( npoints * sizeof(int) );
	pValue = (int* )malloc( npoints * sizeof(int) );

	memset(pAddress, 0, npoints);
	memset(pValue, 0, npoints);

	// fill with default curve: 2 points identity

	pAddress[0] = 0;
	pValue[0] = 0;

	pAddress[npoints -1] = (1 << address_bitdepth) - 1;
	pValue[npoints -1] = (1   << value_bitdepth) - 1;
}

LookupTable::~LookupTable()
{
	free(pAddress);
	free(pValue);
}


TTP_U16 LookupTable::getCurveValue(TTP_U16 x)
{

	x = x >> (RAW_BITDEPTH - address_bitdepth); // normalise the input from the raw bit depth to the nominal LUT input bit depth

	unsigned int retval = x; // bypass

	long weighted_sum = 0;

	unsigned int x0, x1, y0, y1;

	for (int i = 0; i < npoints - 1; i++ )
	{
		x0 += (1 << pAddress[i]);
		x1 = x0 + (1 << pAddress[i+1]);

		if
		(
			x >= x0
			&&
			x <  x1
		 )
		{
			y0 = pValue[i];
			y1 = pValue[i + 1];

			weighted_sum = (x- x0)*(y1 - y0) + (y0 << pAddress[i+1]);

			retval = static_cast<unsigned int>( weighted_sum >> pAddress[i+1]);
		}
	}

	return retval << (RAW_BITDEPTH - value_bitdepth); // normalise the output from the nominal LUT output bit depth to the raw bit depth
}

float LookupTable::getCurveValue(float x)
{
	///TODO do a simple float to raw -> use raw function -> raw to float -> return float
	return x;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TTPlayerProcessor::TTPlayerProcessor() {

	transferFunction = new(LookupTable);

}

TTPlayerProcessor::~TTPlayerProcessor() {

	delete(transferFunction);
}

