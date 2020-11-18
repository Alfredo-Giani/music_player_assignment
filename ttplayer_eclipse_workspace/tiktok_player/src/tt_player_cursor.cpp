/*
 * tt_player_cursor.cpp
 *
 *  Created on: 9 Nov 2020
 *      Author: alfre
 */

#include "tt_player_cursor.h"
#include "tt_player_console_manager.h"

TTPlayerCursor::TTPlayerCursor()
:wavHandler(0)
,state(CURSOR_IDLE)
,playSpeed(1.0)
{
	streamParameters.bitPerSample = 16;
	streamParameters.samplingFrequency = 44000;

	streamParameters.lengthInSamples = 0;
	streamParameters.lengthInSeconds = streamParameters.lengthInSamples/streamParameters.samplingFrequency;
}

TTPlayerCursor::~TTPlayerCursor() {
	// TODO Auto-generated destructor stub
}

TTPlayerCursor::TTPlayerCursor(const TTPlayerCursor &other) {
	// TODO Auto-generated constructor stub

	wavHandler = other.wavHandler;

}

void TTPlayerCursor::setWavHandler(RAW_HANDLE wavhandler)
{
	wavHandler = wavhandler;
}
void TTPlayerCursor::setStreamParameters(const StreamParameters params)
{
	streamParameters = params;
}

void TTPlayerCursor::receive(pTTPlayerMessage message)
{
	TTPlayerConsoleMessage cmess;
	cmess.setMessageType( PROGRESS_STATUS );

	switch(message->getMessage())
	{
	case TTPlayerMessage::TTP_MESSAGE_EMPTY:

		cmess.setMessage(" CURSOR received empty command!");
		break;

	case TTPlayerMessage::TTP_MESSAGE_STOP:

		cmess.setMessage(" CURSOR received stop command!");
		break;

	case TTPlayerMessage::TTP_MESSAGE_PAUSE:

		cmess.setMessage(" CURSOR received pause command!");
		break;

	case TTPlayerMessage::TTP_MESSAGE_PLAY:

		cmess.setMessage(" CURSOR received play command!");
		play();
		break;

	default:

		cmess.setMessage(" CURSOR received unknown command!");

	}
	TTPlayerConsoleManager::getInstance().processConsoleMessage(cmess);

}

#ifdef _WINTHREADS
DWORD WINAPI  TTPlayerCursor::playThread(LPVOID lpParameter)
{
	/*
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	while(myCounter < 0xFFFFFFFF) ++myCounter;
	return 0;
	*/
	for (long n = 0; n < streamParameters.lengthInSamples; n++ )
	{
		TTP_RAW currentSample = wavHandler.get()[n];

		TTP_RAW produced = produce(currentSample);

		/// REAL TIME: SEND THE VALUE TO A BUFFER FOR SOUND RENDERING?

		///wavHandler[n] = produced;

	}

	return 0;
}
#endif

void TTPlayerCursor::play(float speed)
{
	switch(state)
	{
	case CURSOR_PLAY:
		if (speed == playSpeed)
			return;

		playSpeed = speed;
		break;

	case CURSOR_IDLE:
	case CURSOR_PAUSE:
	case CURSOR_STOP:

		playSpeed = speed;

		state = CURSOR_PLAY;




#ifdef _WINTHREADS

		unsigned int myCounter = 0;
		DWORD myThreadID;
		HANDLE myHandle = CreateThread(0, 0, playThread, &myCounter, 0, &myThreadID);

		if (myHandle == NULL)
			std::cout << "ops\n";

#else
		state = CURSOR_STOP;
		std::cout << "threads not implemented, can't play won't play!\n";

#endif

	}
}
