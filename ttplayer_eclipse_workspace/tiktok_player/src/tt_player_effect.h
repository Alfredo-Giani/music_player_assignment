/*
 * tt_player_effect.h
 *
 *  Created on: 9 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_EFFECT_H_
#define TT_PLAYER_EFFECT_H_

#include "tt_player_component.h"
#include "tt_player_precision.h"

using namespace std;

class TTPlayerStatelessTransferFunction
{
public:

	TTPlayerStatelessTransferFunction(){};
	virtual ~TTPlayerStatelessTransferFunction(){};
	TTPlayerStatelessTransferFunction(const TTPlayerStatelessTransferFunction &other); ///< copy constructor

	virtual float getCurveValue(float x){return x;}; ///< return the output value for a given input
	virtual TTP_RAW getCurveValue(TTP_RAW x){return x;}; ///< return the output value for a given input
};

class TTPlayerEffect : public TTPlayerComponent
{
public:
	TTPlayerEffect();
	virtual ~TTPlayerEffect();

	TTPlayerEffect(const TTPlayerEffect &other);

	virtual float output(float input){return input;};
	virtual TTP_RAW outputRAW(TTP_RAW input){return input;}; // default bypass

	TTPlayerStatelessTransferFunction* pStatelessTransferFunction;
};

typedef TTPlayerEffect* pTTPlayerEffect;

#endif /* TT_PLAYER_EFFECT_H_ */
