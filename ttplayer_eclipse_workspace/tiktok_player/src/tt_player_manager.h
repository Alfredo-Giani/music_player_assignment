/*
 * tt_player_manager.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_MANAGER_H_
#define TT_PLAYER_MANAGER_H_

#include <iostream>
#include <vector>

using namespace std;

#include "tt_player_component.h"
#include "tt_player_message.h"
#include "tt_player_cursor.h"
#include "tt_player_stream.h"
#include "tt_player_processor.h"

enum TTPlayerState
{
	IDLE,
	START,
	STOPPED
};

class TTPlayerManager final : public TTPlayerComponent {
public:
	TTPlayerManager();
	virtual ~TTPlayerManager();

	// overridden methods
	void update();

	// GUI menu operation callbacks
	void onOpenFileClicked();

	// GUI transport callbacks
	void onPlayButtonClicked();
	void onPauseButtonClicked();
	void onStopButtonClicked();

	void onHomeButtonClicked();
	void onEndButtonClicked();

	void onRewindButtonPressed();
	void onRewindButtonReleased();

	void onFastForwardButtonPressed();
	void onFastForwardButtonReleased();

	void onTimeSliderValueChanged(float value);///< react to a manual change of the transport slider


	// time slider interface
	float getTrackLength();///< get track length in In milliseconds
	int getCurrentPlaybackPosition();///< get current play back position in milliseconds

	// exit callback
	void onExit();

private:
	TTPlayerCursor* 	cursor;
	TTPlayerStream* 	stream;
	TTPlayerProcessor* 	processor;

	TTPlayerState 	state;
};

#endif /* TT_PLAYER_MANAGER_H_ */
