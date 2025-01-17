/*
 * tt_player_component.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfredo Giani for TikTok
 *
 *      a base class containing declarations of basic player component methods
 *
 *      a component needs a series of functionalities
 *
 *      	- update it's internal state and subcomponents
 *      	- send and receive messages
 *
 *      	since all these functionalities might do different things in derived classes,
 *      	we leave the methods empty.
 */

#ifndef TT_PLAYER_COMPONENT_H_
#define TT_PLAYER_COMPONENT_H_

#include "tt_player_globaldefs.h"
#include <vector>

using namespace std;

class TTPlayerComponent; // forward declaration
typedef TTPlayerComponent* pTTPlayerComponent; ///< convenience type to use pointers to components

class TTPlayerComponent : public TTPlayerObject ///< base component class
{
public:
	TTPlayerComponent();
	virtual ~TTPlayerComponent();
	TTPlayerComponent(const TTPlayerComponent &other); ///< copy constructor

	virtual void update(pTTPlayerComponent caller);///< update function, propagated to all sub-components

	virtual void receive(pTTPlayerMessage const message); ///< called by a component to send a message to this component
	virtual void send(pTTPlayerMessage message); ///< send the message to all the sub-components

	virtual void addComponent(pTTPlayerComponent component); ///< add a sub-component
	virtual void removeComponent(pTTPlayerComponent component); ///< remover a sub-component

	friend ostream& operator<<(ostream& os, const TTPlayerComponent& c) //< overloaded outstream operator
	{
		os << "TTPlayerComponent name: " << c.getName() << " ID: " << c.getID() << "\n";
		return os;
	}

private:
	vector< pTTPlayerComponent > components;///< vector of pointers to sub-compoenents

};

#endif /* TT_PLAYER_COMPONENT_H_ */
