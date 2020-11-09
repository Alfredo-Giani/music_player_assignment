/*
 * tt_player_message.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#include "tt_player_message.h"

TTPlayerMessage::TTPlayerMessage()
:caller(0)
{
	// TODO Auto-generated constructor stub

}

TTPlayerMessage::~TTPlayerMessage() {
	// TODO Auto-generated destructor stub
}

TTPlayerMessage::TTPlayerMessage(const TTPlayerMessage &other) {

	caller = other.caller;

}

