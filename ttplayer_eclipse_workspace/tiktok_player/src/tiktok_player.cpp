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
#include "tt_player_precision.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

bool test_inverse_lut()
{
	bool retval = true;

	std::ofstream fstream("tt_player_test_inverse_lut_log.csv");

	//generate a unsigned range (16 bit) with 64 (6 bit) step
	for (TTP_U32 x_in = 0; x_in < (1 << 16); x_in += (1 << 4))
	{
		// normalise the input range so that the interval [1...255] represents the floating point number [1/256, 1-1/256]
		float x_norm = static_cast<float>(x_in)/pow(2.0, 8);

		// calculate the renormalised lut output
		//TTP_U64 y = TTPlayerPrecision::ttp_lut_inverse(x_in);
		TTP_U64 y = TTPlayerPrecision::ttp_lut_inverse(x_in);

		// renormalise
		float y_ren = static_cast<float>(y)*pow(2.0,-LUT_PRECISION);

		// normalise the output so that
		//
		// ttp_lut_inverse(1) = 1/(1/255) = 255.0,
		// ttp_lut_inverse(256) = 1.0
		// ttp_lut_inverse(512) = 2.0
		// etc

		float y_norm = y_ren * pow(2.0, 8);

		// calculate the golden reference
		//float y_ideal = 1./x_norm;

		std::string message;


		std::ostringstream osstream;
		osstream << "x_in = " << x_in << " y = " << y << " x_norm = " << x_norm << " y_norm = " << y_norm << "\n";

		message.append(osstream.str());

		std::cout << osstream.str();

		std::ostringstream csv_osstream;
		csv_osstream << x_in << "," << y << "," << x_norm << "," << y_norm << "\n";
		fstream << csv_osstream.str();

	}

	fstream.close();
	retval = true;

	return retval;
}


int main() {

	// initialise the manager, that will hold subclasses of the other components

	// start the thread

	test_inverse_lut();

	cout << "done!";

	return 0;
}
