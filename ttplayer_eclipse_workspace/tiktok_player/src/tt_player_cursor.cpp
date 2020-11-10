/*
 * tt_player_cursor.cpp
 *
 *  Created on: 9 Nov 2020
 *      Author: alfre
 */

#include "tt_player_cursor.h"

TTPlayerCursor::TTPlayerCursor()
:wavHandler(0)
{
	streamParameters.bitPerSample = 16;
	streamParameters.samplingFrequency = 44000;

}

TTPlayerCursor::~TTPlayerCursor() {
	// TODO Auto-generated destructor stub
}

TTPlayerCursor::TTPlayerCursor(const TTPlayerCursor &other) {
	// TODO Auto-generated constructor stub

	wavHandler = other.wavHandler;

}

void TTPlayerCursor::setWavHandler(TTPlayerSmartPointer wavhandler)
{
	wavHandler = wavhandler;
}
void TTPlayerCursor::setStreamParameters(const StreamParameters params)
{
	streamParameters = params;
}

