/*
 * tt_player_processor.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#include "tt_player_processor.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define CLAMP(X,MIN,MAX) X < MIN ? MIN : ( X > MAX ? MAX : X )

float TangentHSoftClipper::getCurveValue(float x)
{

	float retVal = x;

	//(e^2x - 1)/(e^2x + 1)

	float expval = pow(EUL_SQUARED,x);
	retVal =  (expval - 1.0)/(expval + 1.0);

	return retVal;

}
int TangentHSoftClipper::getCurveValueRAW(int x)
{
/*
	x = CLAMP(x, 0, 1);
	long xnorm = static_cast<long>( x*INVLN2 << 15 );
	//1 << (1 + xnorm)
	retVal =  (pow(EUL, )) - 1.0)/(pow(EUL,2*x) + 1.0);
*/

	return x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LookupTable::LookupTable()
:npoints(1 << DEFAULT_LUT_BITDEPTH)
,address_bitdepth(8)
,value_bitdepth(10)
{
	pAddress = (int* )malloc( npoints * sizeof(int) );
	pValue = (int* )malloc( npoints * sizeof(int) );

	memset(pAddress, 0, npoints);
	memset(pValue, 0, npoints);
}

LookupTable::~LookupTable()
{
	free(pAddress);
	free(pValue);
}


int LookupTable::getCurveValueRAW(int x)
{

	x = x >> (RAW_BITDEPTH - address_bitdepth); // normalise the input from the raw bit depth to the nominal LUT input bit depth

	int retval = x; // bypass

	long weighted_sum = 0;

	int x0, x1, y0, y1;

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

			retval = static_cast<int>( weighted_sum >> pAddress[i+1]);
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
