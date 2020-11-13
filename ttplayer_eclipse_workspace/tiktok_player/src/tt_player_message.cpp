/*
 * tt_player_message.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#include "tt_player_message.h"

TTPlayerMessage::TTPlayerMessage(MESSAGES message, string brief, TTPlayerObject* caller)
	:message(message)
	,brief(brief)
	,caller(caller)
	{}


TTPlayerMessage::~TTPlayerMessage() {
	// TODO Auto-generated destructor stub
}

TTPlayerMessage::TTPlayerMessage(const TTPlayerMessage &other) {

	caller = other.caller;

}

