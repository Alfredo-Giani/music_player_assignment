/*
 * tt_player_object.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_OBJECT_H_
#define TT_PLAYER_OBJECT_H_

//#include "tt_player_globaldefs.h"
#include <string>

using namespace std;

class TTPlayerObject
{
public:
	TTPlayerObject();
	virtual ~TTPlayerObject();
	TTPlayerObject(const TTPlayerObject &other);

	void setID(int i){id = i;};
	void setName(string n){name = n;};

	int getID(){return id;};
	string getName(){return name;};

private:
	int id;
	string name;
};

#endif /* TT_PLAYER_OBJECT_H_ */
