/*
 * tt_player_debug_manager.h
 *
 *  Created on: 15 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_CONSOLE_MANAGER_H_
#define TT_PLAYER_CONSOLE_MANAGER_H_

#include "tt_player_globaldefs.h"
#include <string>
#include <memory>



enum CONSOLE_MESSAGE
{
	EMPTY_MESSAGE,
	DEBUG_RC_POINTS,
	DEBUG_SIGNALS,
	PROGRESS_STATUS

};

class TTPlayerConsoleMessage
{

private:
	std::string mess;
	CONSOLE_MESSAGE message_type; ///< just a generic thing to differentiate messages and decide what to do

public:

	TTPlayerConsoleMessage()
	{
		mess = string();
		message_type = EMPTY_MESSAGE;
	}
	TTPlayerConsoleMessage(string m, CONSOLE_MESSAGE mt)
	{
		mess = m;
		message_type = mt;
	};

	void setMessage(string msg)
	{
		mess = msg;
	};
	string getMessage()
	{
		return mess;
	};

	void setMessageType(CONSOLE_MESSAGE mtype)
	{
		message_type = mtype;
	};
	CONSOLE_MESSAGE getMessageType()
	{
		return message_type;
	};
};


/*
 * singleton implementation. used this ref: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
 */
class TTPlayerConsoleManager
{
public:

	static TTPlayerConsoleManager& getInstance() // return a TTPlayerDebugManager object by reference
	{
		static TTPlayerConsoleManager instance; // the object

		return instance;
	};

	//C++ 11
	TTPlayerConsoleManager(TTPlayerConsoleManager const&) = delete;
	void operator=(TTPlayerConsoleManager const&) = delete;

	void processConsoleMessage(TTPlayerConsoleMessage message)
	{
		CONSOLE_MESSAGE type = message.getMessageType();
		switch(type)
		{
		case PROGRESS_STATUS:

#ifdef _PROGRESS_CONSOLE
			std::cout << "" << message.getMessage() << "\n";
#endif
			break;

		case DEBUG_RC_POINTS:
#ifdef _DEBUG_RC_P
			std::cout << "DEBUG RC: " << message.getMessage() << "\n";
#endif
			break;
		case DEBUG_SIGNALS:
#ifdef _DEBUG_
			std::cout << "DEBUG: " << message.getMessage() << "\n";
#endif
			break;
		default:
			std::cout << "unknown console message, string: %s\n" << message.getMessage();

		}
	};


private:
	TTPlayerConsoleManager(){}; ///< private constructor



};

#endif /* TT_PLAYER_CONSOLE_MANAGER_H_ */
