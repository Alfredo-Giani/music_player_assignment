//============================================================================
// Name        : tiktok_player.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <fstream>
#include <iostream>
#include <vector>
#include "tt_player_globaldefs.h"
#include "tt_player_precision.h"
#include "tt_player_processor.h"
#include "tt_player_console_manager.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

int test_inverse_lut() // ported from python
{
	int retval = 1;

	std::ofstream fstream( "tt_player_test_inverse_lut_log.csv", std::ofstream::out | std::ofstream::trunc );

	// all this will be managed by the debug manager at some point
	std::ostringstream csv_osstream;
	csv_osstream << "x_in" << "," << "y_out" << "," << "x_norm" << "," << "y_norm" << ","  << "y_ideal" << "\n";

	int subsamp = 4;
	/*
	 * generate a sub sampled unsigned range from 1 to 2 << 16 making sure that
	 *
	 * 0 is never hit
	 * 1 is always hit (1/256 in fixed point precision)
	 * other samples are always powers  of 2
	 */

	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += ((1 << subsamp)))
	{
		// so that we never divide by 0, and always divide by 1
		if (x_in == 0)
		{
			if (subsamp == 0) // 1 will be hit at the next iteration
				continue;
			else // subsamp > 0 so next iter will not be 1. force it
				x_in = 1;
		}


		// calculate the renormalised lut output
		TTP_U64 y_out = TTPlayerPrecision::ttp_lut_inverse(x_in);

		// renormalise
		float y_ren = static_cast<float>(y_out)*pow(2.0,-LUT_PRECISION);

		// normalise the output so that
		//
		// ttp_lut_inverse(1) = 1/(1/255) = 255.0,
		// ttp_lut_inverse(256) = 1.0
		// ttp_lut_inverse(512) = 2.0
		// etc
		float y_norm = y_ren * pow(2.0, 8);


		// normalise the input range so that the interval [1...255] represents the floating point number [1/256, 1-1/256]
		float x_norm = static_cast<float>(x_in)/pow(2.0, 8);
		// calculate the golden reference
		float y_ideal = 1./x_norm;

		std::string message;
		std::ostringstream osstream;

		osstream << "x_in = " << x_in << " y_out = " << y_out << " x_norm = " << x_norm << " y_norm = " << y_norm << " y_ideal = " << y_ideal << "\n";

		message.append(osstream.str());

		TTPlayerConsoleMessage mess(message,CONSOLE_MESSAGE::PROGRESS_STATUS);
		TTPlayerConsoleManager::getInstance().processConsoleMessage(mess);

		//std::cout << osstream.str();

		csv_osstream << x_in << "," << y_out << "," << x_norm << "," << y_norm << "," << y_ideal << "\n";
	}

	fstream << csv_osstream.str();
	fstream.close();
	retval = 1;

	return retval;
}


int test_tanh() // ported from python
{

	int retval = 1;

	std::ofstream fstream("tt_player_test_tanh_log.csv");

	// all this will be managed by the debug manager at some point
	std::ostringstream csv_osstream;
	csv_osstream << "x_in" << "," << "y_out" << "," << "x_norm" << "," << "y_norm" << ","  << "y_ideal" << "\n";


	int subsamp = 2;
	/*
	 * generate a sub sampled unsigned range from 1 to 2 << 16 making sure that
	 *
	 * 0 is never hit
	 * 1 is always hit (1/256 in fixed point precision)
	 * other samples are always powers  of 2
	 */

	TangentHSoftClipper* tanh_clipper = new TangentHSoftClipper();

	// single input
	//TTP_U32 x_in = (1 << 16) - 1;

	//generate a subsampled unsigned range 0...(16 bit)
	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += (1 << subsamp))
	{
		float gain = 1.0;

		// calculate gain in fixed precision: remove extra fractional numbers
		float gain_fp = floor(gain * POW2(TANH_GAIN_FRACT)) * POW2(-TANH_GAIN_FRACT);

		// now clip gain to the max fixed point value
		CLAMP(gain_fp, 0 , POW2(TANH_GAIN_INTEG) - POW2(-TANH_GAIN_FRACT) );

		//apply tanh
		TTP_U16 y_out = tanh_clipper->getCurveValue(x_in, gain_fp);

		// normalise to -1.0, 1.0
		float y_norm = (static_cast<float>( static_cast<TTP_S32>(y_out))/pow(2.0, 15) - 1.0);

		// normalise x in -1, 1 with -1 corresponding to -256 (signed integer) and 1 corresponding to 255
		float x_norm = (static_cast<float>( static_cast<TTP_S32>(x_in))/pow(2.0, 15) - 1.0);

		float y_ideal = x_norm*(27 + pow(x_norm,2.0))/(27  + 9*pow(x_norm, 2.0));

		float error = abs(y_norm - y_ideal);

		float bitloss = error > 0 ? log2(error) : 0;

		std::string message;
		std::ostringstream osstream;

		osstream
			<< " x_in = " << x_in
			<< " y_out = " << y_out
			<< " x_norm = " << x_norm
			<< " y_norm = " << y_norm
			<< " y_ideal = " << y_ideal
			<< " bitloss = " << bitloss
			<< "\n";

		message.append(osstream.str());

		TTPlayerConsoleMessage mess(message,CONSOLE_MESSAGE::PROGRESS_STATUS);
		TTPlayerConsoleManager::getInstance().processConsoleMessage(mess);

		//std::cout << osstream.str();

		//std::ostringstream csv_osstream;
		csv_osstream << x_in << "," << y_out<< "," << x_norm << "," << y_norm << "," << y_ideal << "\n";
	}

	fstream << csv_osstream.str();

	delete tanh_clipper;

	fstream.close();
	retval = 1;

    return retval;


}

int main() {


	int retval = 1;
	// initialise the manager, that will hold subclasses of the other components

	// start the thread

	//test_inverse_lut();
	retval = test_tanh();

	if (retval == 1)
		cout << "done!";
	else
		cout << "ops...";


	return retval;
}
