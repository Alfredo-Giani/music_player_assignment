/*
 * tt_player_manager.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */
#include "tt_player_manager.h"
using namespace std;

TTPlayerManager::TTPlayerManager()
{
	stream 	  = new TTPlayerStream();
	cursor 	  = new TTPlayerCursor();
	processor = new TTPlayerProcessor();
	state = IDLE;

}


TTPlayerManager::~TTPlayerManager()
{
	delete(cursor);
	delete(stream);
	delete(processor);
}

// overridden methods
void TTPlayerManager::update()
{

}

// GUI menu operation callbacks
int TTPlayerManager::onNewFileRequest(char* fullpathname)
{
	int retval = 1;

	try
	{
		stream->loadFileStream(fullpathname);

		cursor->setWavHandler(stream->getWavHandler());
		cursor->setStreamParameters(stream->getStreamParameters());

	}
	catch(TTPlayerException &ex)
	{
#ifdef _DEBUG_
		cout << ex.what() << '\n';
#endif
		return -1;
	}

	return retval;
}

// GUI transport callbacks
int TTPlayerManager::onPlayButtonClicked()
{
	int retval = 1;
	try
	{
		cursor->play(1.0);
	}
	catch(TTPlayerException &ex)
	{
#ifdef _DEBUG_
		cout << ex.what() << '\n';
#endif
		return -1;
	}

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


