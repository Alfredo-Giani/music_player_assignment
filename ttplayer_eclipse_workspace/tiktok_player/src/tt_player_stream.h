/*
 * TTPlayer_stream.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_STREAM_H_
#define TT_PLAYER_STREAM_H_

#include "tt_player_globaldefs.h"
#include "tt_player_component.h"
#include "tt_player_smartpointer.h"
typedef TTPlayerSmartPointer<int> SP_STREAM;

class TTPlayerStream final : public TTPlayerComponent
{
public:
	TTPlayerStream();
	virtual ~TTPlayerStream();

	void loadFileStream(const char* filename) noexcept{};///< this function loads the stream and updates the wav_handler and stream parameters

	void getWavHandler(SP_STREAM &out){};
	StreamParameters getStreamParameters(){return parameters;};

private:
	int* pWavHandler;
	StreamParameters parameters;
	//
};

#endif /* TT_PLAYER_STREAM_H_ */
