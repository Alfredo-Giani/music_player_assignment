/*
 * tt_player_message.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_MESSAGE_H_
#define TT_PLAYER_MESSAGE_H_

#include "tt_player_object.h"

class TTPlayerMessage; // forward declaration
typedef TTPlayerMessage* pTTPlayerMessage;

class TTPlayerMessage final : public TTPlayerObject {
public:
	TTPlayerMessage();
	virtual ~TTPlayerMessage();
	TTPlayerMessage(const TTPlayerMessage &other);

	TTPlayerObject* caller;
};


#endif /* TT_PLAYER_MESSAGE_H_ */
