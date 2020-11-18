/*
 * tt_player_component.cpp
 *
 *  Created on: 6 Nov 2020
 *      Author: alfredo Giani
 */

#include "tt_player_component.h"
#include <iostream>

TTPlayerComponent::TTPlayerComponent() {

}

TTPlayerComponent::~TTPlayerComponent() {
	// TODO Auto-generated destructor stub
}

TTPlayerComponent::TTPlayerComponent(const TTPlayerComponent &other) {
	// TODO Auto-generated constructor stub

}
void TTPlayerComponent::update(pTTPlayerComponent pCaller)
{
	// note the condition to avoid circular calling. not sure it works...
	for (auto it = components.begin(); (it != components.end()) && (*it != pCaller); it++ )
	{
		(*it)->update(pCaller);
	}
}

void TTPlayerComponent::receive(pTTPlayerMessage const pMessage)
{
	//&& (*it != pMessage->getCaller())

	for (auto it = components.begin(); it != components.end() && *it != pMessage->getCaller(); ++it )
	{
		(*it)->receive(pMessage);
	}
}

void TTPlayerComponent::send(pTTPlayerMessage pMessage)
{
	for (auto it = components.begin(); it != components.end() && *it != pMessage->getCaller(); ++it )
	{
		(*it)->receive(pMessage);
	}
}

void TTPlayerComponent::addComponent(pTTPlayerComponent pComponent)
{
	components.push_back(pComponent);
}

void TTPlayerComponent::removeComponent(pTTPlayerComponent pComponent)
{
}


