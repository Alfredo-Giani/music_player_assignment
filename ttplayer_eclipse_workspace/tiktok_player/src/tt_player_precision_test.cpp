/*
 * TTPlayerPrecision_test.cpp
 *
 *  Created on: 12 Nov 2020
 *      Author: alfre
 */

#include "tt_player_precision.h"
#include <math.h>
#include <stdio.h>

/*
bool test_inverse_lut()
{
	bool retval = true;

	FILE* fid = fopen("tt_player_test_inverse_lut_log.txt", "wb");

	//generate a unsigned range (16 bit) with 64 (6 bit) step
	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += (1 << 4))
	{
		// normalise the input range so that the interval [1...255] represents the floating point number [1/256, 1-1/256]
		float x_norm = static_cast<float>(x_in)/pow(2.0, 8);

		// calculate the renormalised lut output
		float y = static_cast<float>(TTPlayerPrecision::ttp_lut_inverse(x_in));

		// renormalise
		float y_ren = y*pow(2.0,-LUT_PRECISION);

		// normalise the output so that
		//
		// ttp_lut_inverse(1) = 1/(1/255) = 255.0,
		// ttp_lut_inverse(256) = 1.0
		// ttp_lut_inverse(512) = 2.0
		// etc

		float y_norm = y_ren * pow(2.0, 8);

		// calculate the golden reference
		float y_ideal = 1/x_norm;
		fprintf(fid  , "%3.5f , %3.8f , %3.8f \n", x_norm, y_norm, y_ideal);

	}

	fclose(fid);
	retval = true;

	return retval;
}
*/
