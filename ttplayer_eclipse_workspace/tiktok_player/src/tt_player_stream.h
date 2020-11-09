/*
 * TTPlayer_stream.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_STREAM_H_
#define TT_PLAYER_STREAM_H_

#include "tt_player_component.h"

class TTPlayerStream final : public TTPlayerComponent
{
public:
	TTPlayerStream();
	virtual ~TTPlayerStream();

	P_WAV_HANDLER loadFileStream(char* filename) noexcept;
};

#endif /* TT_PLAYER_STREAM_H_ */
