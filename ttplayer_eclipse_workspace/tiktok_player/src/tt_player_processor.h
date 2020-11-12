/*
 * tt_player_processor.h
 *
 *  Created on: 6 Nov 2020
 *      Author: Alfredo Giani for TikTok
 *
 *  This class deals realises a memoryless transfer function.
 *
 *  In this specific implementation we use a integer (fixed point) look-up table LUT to yield the desired function.
 *
 *	the lookup table is non uniform in x to optimise bandwidth allocation i.e. the table is more densely populated where the
 *	curve departs more from a straight line
 *
 *	the output values are linearly interpolated in between LUT points
 *
 *	The design has in mind a hardware-like implementation. The input signal is considered raw i.e. signed integer precision
 *	e.g. signed 16 bit
 *
 *	in order to minimise the use of dividers, the distance between two consecutive x-points in the lookup table is a power of 2
 *	this allows in integer precision to use the binary shift as a divider (and multiplier) where relevant in the calculations
 *
 *
 */

#ifndef TT_PLAYER_PROCESSOR_H_
#define TT_PLAYER_PROCESSOR_H_

#include <iostream>
#include <cstring>
#include <math.h>
#include "tt_player_effect.h"

#include "tt_player_precision.h"

enum CurveType
{
	IDENTITY,
	LUT,
	TANH
};

class TangentHSoftClipper : public StatelessTransferFunction
{
public:
	TangentHSoftClipper(); 														///< constructor

	TTP_U16 getCurveValue(TTP_U16 x, float gain = 1.0);  	///< return the output value for a given input - fixed point
	float getCurveValue(float x); 												///< return the output value for a given input - floating point

};

// the class storing the LUT and providing the output value for a given input x
class LookupTable : public StatelessTransferFunction
{
public:
	LookupTable(); 														///< constructor with default bit depth and lookup table (identity)
	LookupTable(const char* table_name); 								///< constructor which loads the table from a file
	virtual ~LookupTable();												///< destructor

	void loadTableFromFile(const char* table_name) noexcept; 			///< load a new table. throws TTPlayerException if file not found

	TTP_U16 getCurveValue(TTP_U16 x); 								///< return the output value for a given input
	float getCurveValue(float x); 									///< return the output value for a given input

private:
	int npoints; 												///< number of points (addresses) in the LUT
	int address_bitdepth; 										///< bit depth of the input values (x)
	int value_bitdepth; 										///< bit depth of the output values (y)

	int* pAddress; 												///< the start points (left margin) of each segment in lookup table, defined as incremental exponents
	int* pValue; 												///< the output corresponding to each start point (left margin) of each segment in lookup table
};


class TTPlayerProcessor : public TTPlayerEffect
{
public:
	TTPlayerProcessor();
	virtual ~TTPlayerProcessor();

	// overrides from base class TTPlayerComponent
	virtual void update(pTTPlayerComponent caller){update(caller);};

	virtual void receive(pTTPlayerMessage message){receive(message);}; //
	virtual void send(pTTPlayerMessage message){send(message);}; //;

	// processor methods
	float output(float input)
	{
		return transferFunction->getCurveValue(input);
	};

	int outputRAW(int inputRAW)
	{
		return transferFunction->getCurveValueRAW(inputRAW);
	};

	StatelessTransferFunction* transferFunction;

};

#endif /* TT_PLAYER_PROCESSOR_H_ */
