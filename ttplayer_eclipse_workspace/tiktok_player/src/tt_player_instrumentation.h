/*
 * tt_player_instrumentation.h
 *
 *  Created on: 12 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_INSTRUMENTATION_H_
#define TT_PLAYER_INSTRUMENTATION_H_

#include <cmath>
#include "tt_player_globaldefs.h"
#include "tt_player_component.h"
#include "tt_player_precision.h"

// just a bunch of measurements likely to be useful
struct signal_comparison_report
{
	float harmonic_distortion;
	float error_mean;
	float error_std;
	float error_max;

	signal_comparison_report()
	{
		harmonic_distortion = 0;
		error_mean = 0;
		error_std = 0;
		error_max = 0;
	}
	void reset()
	{
		harmonic_distortion = 0;
		error_mean = 0;
		error_std = 0;
		error_max = 0;
	}
};


class TTPlayerInstrumentation final : public TTPlayerComponent {
public:
	TTPlayerInstrumentation();
	virtual ~TTPlayerInstrumentation();
	TTPlayerInstrumentation(const TTPlayerInstrumentation &other);

	// A function that tests a rc point for LSB and MSB loss on the input. It can be used to test rc points
	//
	// TODO
	// NOTE: 	this is temporary! it should be a template method for TTP integer types
	//			in general can be done better
	// NOTE: this diagnostic check if p_out has enough precision to represent x lossless, regardless the nominal input precision
	//
	static bool testTruncation(long long x, precision p_in, precision p_out, const char* rcpoint_name) noexcept
	{
		bool retval = false;

		// check if the input sign is compatible with the input nominal sign
		if (x < 0 && p_in.is_signed)
		{
			printf
			(
					"WARNING: x should be unsigned. in %s \n "
					"\n"
					"input is				: %I64d \n"
					, rcpoint_name
					, x
			);

			retval = false;
			return retval;
		}

		// convert x in floating point
		float x_fixed = x *pow(2.0, -p_in.fract);

		// check if the output fractional precision drops LSBs
		float x_cond =	(x_fixed * static_cast<float>(1 << p_out.fract));

		if ( x_cond != floor(x_cond) ) // if there is still fractional part
		{
			float x_lsb_truncated = floor(x_cond * static_cast<float>(1 >> p_out.fract));

			printf
			(
					"WARNING: LSB truncation error in  %s \n "
					"\n"
					"fixed point input is				: %f \n"
					"lsb truncated is					: %f \n"
					, rcpoint_name
					, x_fixed
					, x_lsb_truncated
			);

			retval = false;
			return retval;
		}

		// check if the output integer precision drops MSBs
		float max_out = pow(2.0,p_out.integ) -1;
		if ( x_fixed > max_out )
		{
			printf
			(
					"WARNING: MSB truncation error in  %s \n "
					"\n"
					"fixed point input is				: %f \n"
					"max fixed point output is			: %f \n"
					, rcpoint_name
					, x_fixed
					, max_out
			);

			retval = false;
			return retval;
		}

		retval = true;

		return retval;
	};

	static bool compareTwoFixedPointSignals(const float* x1, const float* x2, unsigned long length,  signal_comparison_report& report) // VERY simple
	{
		report.reset(); // just in case...

		for(unsigned long i = 0; i < length; i++)
		{
			report.error_mean += (x1[i] - x2[i]);
		}
		report.error_mean /= length;

		// ETC.....
		return false;
	};
};



#endif /* TT_PLAYER_INSTRUMENTATION_H_ */
