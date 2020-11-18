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
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <string>
#include <sstream>

#include "tt_player_globaldefs.h"
#include "tt_player_precision.h"
#include "tt_player_processor.h"
#include "tt_player_console_manager.h"

#include "tt_player_manager.h"
#include "tt_player_cursor.h"
#include "tt_player_progress_slider.h"

using namespace std;

#define _TO_CSV // enable test data dump to csv file


// test inverse LUT (reciprocal)
int test_inverse_lut()
{
	int retval = 1;

#ifdef _TO_CSV
	std::ofstream fstream( "tt_player_test_inverse_lut_log.csv", std::ofstream::out | std::ofstream::trunc );
	// TODO csv dump should be managed by the debug manager at some point
	std::ostringstream csv_osstream;
	csv_osstream << "x_in" << "," << "y_out" << "," << "x_norm" << "," << "y_norm" << ","  << "y_ideal" << "\n";
#endif

	int subsamp = 4; // subsample the range with (1 << subsamp)
	/*
	 * generate a sub sampled unsigned int range from 1 to (1 << 16) -1
	 *
	 * 0 is never hit
	 * 1 is always hit ( so we have an input for the minimum value)
	 * other values are always multiples of (1 << subsamp)
	 *
	 *
	 * note that x_in is 32 bit, although we want to generate int16 numbers.
	 * this is to avoid overflow in  x_in += (1 << subsamp) - which would cause
	 * an infinite loop.
	 *
	 */
	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += (1 << subsamp) )
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

		/*
		 * normalise the output so that
		 *
		 * ttp_lut_inverse(1) = 1 / ( 1/(1 << LUT_FULL) ) = (1 << LUT_FULL)
		 *
		 * ttp_lut_inverse((1 << LUT_FULL)) = 1.0
		 *
		 * ttp_lut_inverse((1 << (LUT_FULL+1) ) = 2.0
		 *
		 * etc
		 */
		float y_norm = y_ren * pow(2.0, LUT_FULL - LUT_OUT_FRACT);


		/*
		 * normalise the input range so that the interval
		 *
		 * [1...(1 << LUT_FULL)-1]
		 *
		 * represents the floating point number
		 *
		 * [ (1 <<LUT_FULL)^-1, 1 - (1 <<LUT_FULL)^-1]
		 *
		 */
		float x_norm = static_cast<float>(x_in)/pow(2.0, LUT_FULL);
		// calculate the golden reference
		float y_ideal = 1./x_norm;

		std::string message;
		std::ostringstream osstream;

		osstream << "x_in = " << x_in << " y_out = " << y_out << " x_norm = " << x_norm << " y_norm = " << y_norm << " y_ideal = " << y_ideal << "\n";

		message.append(osstream.str());

		TTPlayerConsoleMessage mess(message,CONSOLE_MESSAGE::PROGRESS_STATUS);
		TTPlayerConsoleManager::getInstance().processConsoleMessage(mess);

		//std::cout << osstream.str();
#ifdef _TO_CSV
		csv_osstream << x_in << "," << y_out << "," << x_norm << "," << y_norm << "," << y_ideal << "\n";
#endif
	}

#ifdef _TO_CSV
	fstream << csv_osstream.str();
	fstream.close();
#endif

	retval = 1;

	return retval;
}

// test hyperbolic tangent
int test_tanh() // ported from python
{

	int retval = 1;

#ifdef _TO_CSV
	std::ofstream fstream("tt_player_test_tanh_log.csv");
	// TODO all this will be managed by the debug manager at some point
	std::ostringstream csv_osstream;
	csv_osstream << "x_in" << "," << "y_out" << "," << "x_norm" << "," << "y_norm" << ","  << "y_ideal" << "\n";
#endif

	int subsamp = 2;
	/*
	 * generate a sub sampled unsigned range from 1 to 2 << 16 making sure that
	 *
	 * 0 is never hit
	 * 1 is always hit (1/256 in fixed point precision)
	 * other samples are always powers  of 2
	 */

	TangentHSoftClipper* tanh_clipper = new TangentHSoftClipper();


	/*
	 * generate a sub sampled unsigned int range from 0 to (2 << 16) - 1
	 *
	 * note that x_in is 32 bit, although we want to generate int16 numbers.
	 * this is to avoid overflow in  x_in += (1 << subsamp) - which would cause
	 * an infinite loop.
	 *
	 */
	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += (1 << subsamp))
	{
		float gain = 1.0;

		// calculate gain in fixed precision: remove extra fractional numbers
		float gain_fp = floor(gain * POW2(TANH_GAIN_FRACT)) * POW2(-TANH_GAIN_FRACT);

		// now clip gain to the max fixed point value
		CLAMP(gain_fp, 0 , POW2(TANH_GAIN_INTEG) - POW2(-TANH_GAIN_FRACT) );

		// convert to raw - TODO this should be compacted in a defined cast function
		TTP_RAW x_s = static_cast<TTP_RAW>(static_cast<TTP_S32>(x_in) - (1 << 15));

		//apply tanh
		TTP_RAW y_out = tanh_clipper->getCurveValue(x_s, gain_fp);

		// normalise to -1.0, 1.0
		float y_norm = static_cast<float>(y_out)/pow(2.0, 15);

		// normalise x in -1, 1 with -1 corresponding to -256 (signed integer) and 1 corresponding to 255
		float x_norm = static_cast<float>(x_s)/pow(2.0, 15);

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

#ifdef _TO_CSV
		csv_osstream << x_in << "," << y_out << "," << x_norm << "," << y_norm << "," << y_ideal << "\n";
#endif
	}

#ifdef _TO_CSV
	fstream << csv_osstream.str();
	fstream.close();
#endif

	delete tanh_clipper;


	retval = 1;

    return retval;
}

// very basic communication test
int test_play_loop()
{
	int retval = 1;

	TTPlayerManager* theManager = new TTPlayerManager();
	theManager->setName("the Manager");


	TTPlayerProgressSlider* theSlider = new TTPlayerProgressSlider();
	theSlider->setName("the Slider");
	theManager->addComponent(theSlider);

	//----------------------------------------------------------------------
	TTPlayerCursor* theCursor = new TTPlayerCursor();
	theCursor->setName("the Cursor");

	RAW_HANDLE theStreamHandler;

	StreamParameters streamParameters;
	streamParameters.bitPerSample = 16;
	streamParameters.samplingFrequency = 100;
	streamParameters.lengthInSeconds = 3.0;
	streamParameters.lengthInSamples =
	streamParameters.lengthInSeconds * streamParameters.samplingFrequency;

	theCursor->setCurrentPosition(0.0);
	theCursor->setWavHandler(theStreamHandler);
	theCursor->setStreamParameters(streamParameters);

	// shared pointer because other cursors might use the same effect?
	std::shared_ptr<TTPlayerEffect> peff = std::shared_ptr<TTPlayerEffect>( new TTPlayerProcessor() );

	theCursor->addEffect(peff);

	//----------------------------------------------------------------------

	theCursor->addComponent(theManager);
	theManager->addComponent(theCursor);

	//----------------------------------------------------------------------
	// simulate the click on the play button
	theManager->onPlayButtonClicked();

	return retval;
}

int main() {


	int retval = 1;
	// initialise the manager, that will hold subclasses of the other components


	// TESTS
	retval = test_inverse_lut();
	retval = test_tanh();
	//retval = test_play_loop();


	if (retval == 1)
		cout << "done!";
	else
		cout << "ops...";


	return retval;
}
