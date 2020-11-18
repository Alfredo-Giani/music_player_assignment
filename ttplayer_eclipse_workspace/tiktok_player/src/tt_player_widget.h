/*
 * tt_player_widget.h
 *
 *  Created on: 15 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_WIDGET_H_
#define TT_PLAYER_WIDGET_H_

#include "tt_player_component.h"


struct Rect
{
	float x;
	float y;
	float w;
	float h;

	Rect()
	:x(0),y(0),w(0),h(0){};

	Rect(Rect &other)
		:x(other.x),y(other.y),w(other.w),h(other.h){};

	Rect& operator = (const Rect &other)
	{
		x = other.x;
		y = other.y;
		w = other.w;
		h = other.h;

		return *this;

	};
};

class TTPlayerWidget: public TTPlayerComponent {
public:
	TTPlayerWidget();
	virtual ~TTPlayerWidget();
	TTPlayerWidget(const TTPlayerWidget &other);



private:

	Rect drawArea;

	virtual void draw(){};
};

#endif /* TT_PLAYER_WIDGET_H_ */
