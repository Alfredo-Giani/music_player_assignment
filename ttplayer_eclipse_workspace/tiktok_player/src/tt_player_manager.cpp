/*
 * tt_player_manager.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#include <memory>
#include "tt_player_manager.h"
#include "tt_player_message.h"
using namespace std;

TTPlayerManager::TTPlayerManager()
{
	state = IDLE;

}


TTPlayerManager::~TTPlayerManager()
{

}

// overload methods
void TTPlayerManager::update()
{
	update(); // call the base class method, for now

}

void TTPlayerManager::receive(pTTPlayerMessage message)
{
	switch (message->getMessage())
	{
	case TTPlayerMessage::TTP_MESSAGE_EMPTY:

		break;
	case TTPlayerMessage::TTP_MESSAGE_PLAY:
		break;

	case TTPlayerMessage::TTP_MESSAGE_PAUSE:
		break;

	case TTPlayerMessage::TTP_MESSAGE_STOP:
		break;

	}
}

// GUI menu operation callbacks
int TTPlayerManager::onNewFileRequest()
{
	int retval = 1;
	return retval;
}

// GUI transport callbacks
int TTPlayerManager::onPlayButtonClicked()
{
	int retval = 1;

	pTTPlayerMessage message = new TTPlayerMessage(TTPlayerMessage::TTP_MESSAGE_PLAY, "", this);

	send(message);

	return retval;
}

int TTPlayerManager::onPauseButtonClicked()
{
	// ALL THE FOLLOWING IMPLEMENTATIONS ARE SIMILAR TO TTPlayerManager::onPlayButtonClicked()
	return 1;
}

int TTPlayerManager::onStopButtonClicked()
{
	return 1;
}

int TTPlayerManager::onHomeButtonClicked()
{
	return 1;
}

int TTPlayerManager::onEndButtonClicked()
{
	return 1;
}

int TTPlayerManager::onRewindButtonPressed()
{
	return 1;
}

int TTPlayerManager::onRewindButtonReleased()
{
	return 1;
}

int TTPlayerManager::onFastForwardButtonPressed()
{
	return 1;
}

int TTPlayerManager::onFastForwardButtonReleased()
{
	return 1;
}

int TTPlayerManager::onTimeSliderValueChanged(float value)
{
	return 1;
}

// time slider interface
int getTrackLength()
{
	return 1;
}

int getCurrentPlaybackPosition()
{
	return 1;
}

// exit callback
int onExit()
{
	return 1;
}


