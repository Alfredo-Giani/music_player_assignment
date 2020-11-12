/*
 * tt_player_cursor.h
 *
 *  Created on: 9 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_CURSOR_H_
#define TT_PLAYER_CURSOR_H_

#include <memory>

#include "tt_player_component.h"
#include "tt_player_effect.h"
#include "tt_player_smartpointer.h"

enum FX_PS
{
	DOWNSTREAM,
	UPSTREAM
};

class TTPlayerCursor : public TTPlayerComponent {
public:
	TTPlayerCursor();
	virtual ~TTPlayerCursor();
	TTPlayerCursor(const TTPlayerCursor &other);

	void setWavHandler(TTPlayerSmartPointer wavhandler);
	void setStreamParameters(const StreamParameters params);

	void play(float speed = 1.0){};
	void stop();
	void pause();

	void fastforward(float speed = 3.0)
	{
		play(speed);
	}
	void rewind(float speed = 3.0)
	{
		play(-speed);
	}

	int getCurrentPosition(); ///< current position is returned in samples
	float getCurrentSample(); ///< the floating point value at the current position
	int getCurrentSampleRAW(); ///< the RAW integer (fixed point) value at the current position

	void setCurrentPosition(int pos); ///< set the current position in samples
	void setCurrentSample(float val); ///< set the current value (floating point)at the current position
	void setCurrentSampleRAW(int raw); ///< set the RAW integer (fixed point) value at the current position


	void addEffect(std::shared_ptr<TTPlayerEffect> peff, FX_PS pos = UPSTREAM)///< add a new effect in the specified position
	{
		effects.push_back(peff);///< add an effect downstream
	};
	void removeEffect(std::shared_ptr<TTPlayerEffect> peff);
	void moveEffectEffectDownstream(std::shared_ptr<TTPlayerEffect> peff);
	void moveEffectEffectUpstream(std::shared_ptr<TTPlayerEffect> peff);

	float produce(float currsamp)
	{
		for (auto it = effects.begin(); it != effects.end() ; it++ )
		{
			currsamp = (*it)->output(currsamp);
		}

		return currsamp;
	};

	int produceRAW(int currsamp)
	{
		for (auto it = effects.begin(); it != effects.end() ; it++ )
		{
			currsamp = (*it)->outputRAW(currsamp);
		}

		return currsamp;
	};

private:

	vector<std::shared_ptr<TTPlayerEffect>> effects;
	TTPlayerSmartPointer wavHandler;
	StreamParameters streamParameters;


};

#endif /* TT_PLAYER_CURSOR_H_ */
