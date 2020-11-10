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

template <typename T> class TTPlayerSmartPointer
{
private:
	T* m_Object{ nullptr };
	ReferenceCount* m_ReferenceCount{ nullptr };

public:
	TTPlayerSmartPointer(){};
	//TTPlayerSmartPointer(T* object);

	TTPlayerSmartPointer(T* object)
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
			cout << "Destroyed TTPlayerSmartPointer! Ref count is " << decrementedCount << endl;
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
	TTPlayerSmartPointer(const TTPlayerSmartPointer<T>& other)
	:m_Object{ other.m_Object }
	, m_ReferenceCount{ other.m_ReferenceCount }
	{
		m_ReferenceCount->Increment();
	#ifdef _DEBUG_
		cout << "Copied TTPlayerSmartPointer! Ref count is " << m_ReferenceCount->GetCount() << endl;
	#endif
	}
	// Overloaded Assignment Operator
	TTPlayerSmartPointer<T>& operator=(const TTPlayerSmartPointer<T>& other)
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

		cout << "Assigning TTPlayerSmartPointer! Ref count is " << m_ReferenceCount->GetCount() << endl;
		return *this;
	}

	//Dereference operator
	T& operator*()
	{
		return *m_Object;
	}

	//Member Access operator
	T* operator->()
	{
		return m_Object;
	}

};

#endif /* TT_PLAYER_SMARTPOINTER_H_ */
