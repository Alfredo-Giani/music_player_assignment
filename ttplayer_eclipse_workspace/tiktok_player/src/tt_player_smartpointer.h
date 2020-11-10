/*
 * tt_player_smartpointer.h
 *
 *  Created on: 10 Nov 2020
 *      Author: alfre
 */

#ifndef TT_PLAYER_SMARTPOINTER_H_
#define TT_PLAYER_SMARTPOINTER_H_

#include "tt_player_globaldefs.h"
#include "tt_player_object.h"
#include <iostream>
using namespace std;

class ReferenceCount
{
private:
  int m_RefCount{ 0 };

public:

  ReferenceCount(){};
  void Increment(){++m_RefCount;};

  int Decrement(){return --m_RefCount;};

  int GetCount() const {return m_RefCount;};
};

typedef int DEREF_TYPE;
typedef DEREF_TYPE* SP_RAW;

class TTPlayerSmartPointer
{
private:
	SP_RAW m_Object{ nullptr };
	ReferenceCount* m_ReferenceCount{ nullptr };

public:
	TTPlayerSmartPointer(){};
	//TTPlayerSmartPointer(T* object);

	TTPlayerSmartPointer(SP_RAW object)
	: m_Object{ object }
	, m_ReferenceCount{ new ReferenceCount() }
	{
		m_ReferenceCount->Increment();

#ifdef _DEBUG_
		cout << "Created TTPlayerSmartPointerr! Ref count is " << m_ReferenceCount->GetCount() << endl;
#endif
	};

	//Destructor
	~TTPlayerSmartPointer()
	{
		if (m_ReferenceCount)
		{
			int decrementedCount = m_ReferenceCount->Decrement();

#ifdef _DEBUG_
			cout << "Destroyed TTPlayerSmartPointer! Ref count is " << decrementedCount << endl;
#endif

			if (decrementedCount <= 0)
			{
				delete m_ReferenceCount;
				delete m_Object;
				m_ReferenceCount = nullptr;
				m_Object = nullptr;
			}
		}
	};
	// Copy Constructor
	TTPlayerSmartPointer(const TTPlayerSmartPointer& other)
	:m_Object{ other.m_Object }
	,m_ReferenceCount{ other.m_ReferenceCount }
	{
		m_ReferenceCount->Increment();

	#ifdef _DEBUG_
		cout << "Copied TTPlayerSmartPointer! Ref count is " << m_ReferenceCount->GetCount() << endl;
	#endif

	}
	// Overloaded Assignment Operator
	TTPlayerSmartPointer& operator=(const TTPlayerSmartPointer& other)
	{
		if (this != &other)
		{
			if (m_ReferenceCount && m_ReferenceCount->Decrement() == 0)
			{
				delete m_ReferenceCount;
				delete m_Object;
			}

			m_Object = other.m_Object;
			m_ReferenceCount = other.m_ReferenceCount;
			m_ReferenceCount->Increment();
		}

#ifdef _DEBUG_
		cout << "Assigning TTPlayerSmartPointer! Ref count is " << m_ReferenceCount->GetCount() << endl;
#endif

		return *this;
	}

	//Dereference operator
	DEREF_TYPE& operator*()
	{
		return *m_Object;
	}

	//Member Access operator
	SP_RAW operator->()
	{
		return m_Object;
	}

};

#endif /* TT_PLAYER_SMARTPOINTER_H_ */
