/*
 * tt_player_object.h
 *
 *  Created on: Nov 2020
 *  Author: alfredo Giani for TikTok
 *
 *
 */

#ifndef TT_PLAYER_OBJECT_H_
#define TT_PLAYER_OBJECT_H_

//#include "tt_player_globaldefs.h"
#include <string>

using namespace std;

class TTPlayerObject ///< TTPlayer base class for objects
{
public:
	TTPlayerObject();
	virtual ~TTPlayerObject();
	TTPlayerObject(const TTPlayerObject &other);

	void setID(int i){id = i;};
	void setName(string n){name = n;};

	int getID() const {return id;};
	string getName() const {return name;};

private:
	int id;
	string name;
};

#endif /* TT_PLAYER_OBJECT_H_ */
