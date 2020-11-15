/*
 * ttplayer_exception.h
 *
 *  Created on: 6 Nov 2020
 *      Author: alfre
 */

#ifndef TTPLAYER_EXCEPTION_H_
#define TTPLAYER_EXCEPTION_H_

#include <exception>
#include <cstdio>
using namespace std;

class TTPlayerException : public exception
{
public:
	virtual char const * what() const noexcept { return "Generic TTPlayerException"; }
};

class TTPlayerFileNotFoundException : public TTPlayerException
{
public:
	virtual char const * what() const noexcept { return "File not found exception"; }
};

class TTPlayerProcessorMemoryAllocationException : public TTPlayerException
{
public:
	virtual char const * what() const noexcept { return "Processor memory allocation exception"; }
};

class TTPlayerDivisionByZeroException : public TTPlayerException
{
public:
	virtual char const * what() const noexcept { return "Division by zero exception"; }
};



#endif /* TTPLAYER_EXCEPTION_H_ */
