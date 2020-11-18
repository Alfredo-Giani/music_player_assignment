/*
 * tt_player_progress_slider.h
 *
 *  Created on: 16 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_PROGRESS_SLIDER_H_
#define TT_PLAYER_PROGRESS_SLIDER_H_

#include "tt_player_widget.h"

class TTPlayerProgressSlider: public TTPlayerWidget {
public:
	TTPlayerProgressSlider();
	virtual ~TTPlayerProgressSlider();
	TTPlayerProgressSlider(const TTPlayerProgressSlider &other);

	// override
	virtual void receive(pTTPlayerMessage message)
	{
		// TODO this does not work because it uses the base class overload instead of the specific one.
		// need to find the way...
		TTPlayerComponent* pp = message->getCaller();
		std::cout
			<< "TTplayerProgressSlider received message from: "
			<<  *pp
			<< " at: "
			<< pp
			<< "\n";
	};
};

#endif /* TT_PLAYER_PROGRESS_SLIDER_H_ */
