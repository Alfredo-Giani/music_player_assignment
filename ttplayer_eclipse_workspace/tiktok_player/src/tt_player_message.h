/*
 * tt_player_message.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_MESSAGE_H_
#define TT_PLAYER_MESSAGE_H_

#include "tt_player_globaldefs.h"
#include "tt_player_object.h"

class TTPlayerMessage; // forward declaration
typedef TTPlayerMessage* pTTPlayerMessage;

class TTPlayerComponent; // forward declaration

class TTPlayerMessage : public TTPlayerObject
{
public:

	enum MESSAGES
	{
		TTP_MESSAGE_EMPTY,
		TTP_MESSAGE_PLAY,
		TTP_MESSAGE_STOP,
		TTP_MESSAGE_PAUSE

	};

	TTPlayerMessage(MESSAGES message = TTP_MESSAGE_EMPTY, string brief = string(), TTPlayerComponent* caller = 0);

	virtual ~TTPlayerMessage();
	TTPlayerMessage(const TTPlayerMessage &other);

	TTPlayerComponent* getCaller() const {return caller;};
	MESSAGES getMessage(){return message;};


private:

	MESSAGES message; ///< message qualifier from an enumeration
	string brief; ///< further comments
	TTPlayerComponent* caller; /// a pointer to the caller. not sure how this would work with deallocation conflicts...
};


#endif /* TT_PLAYER_MESSAGE_H_ */
