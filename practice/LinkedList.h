#ifndef LINKEDLIST
#define LINKEDLIST

#include "LinkedListNode.h"

template<typename T> class LinkedList {
public:
	LinkedList():
	  head(NULL),
	  tail(NULL)
	{
	}

	void Append(const T& value)
	{
		if (tail == NULL)
			head = tail = new LinkedListNode<T>(value);
		else
			tail = tail->Append(value);
	}

	void Prepend(const T& value)
	{
		if (head == NULL)
			head = tail = new LinkedListNode<T>(value);
		else
			head = head->Insert(value,0);
	}

	void Insert(const T& value, int index)
	{
		if (head == NULL);	//exception

		head->Insert(value,index);
	}

	void Remove(int index)
	{
		if (head == NULL)
			throw 0;
		head->Remove(index);
	}

	T& Front() const
	{
		if (head != NULL)
			return head->Value;
	}

	T& Back() const
	{
		if (tail != NULL)
			return tail->Value;
	}

	int Count() const
	{
		if (head != NULL)
			return head->Count();

		return 0;
	}

	const T& operator[](int index) const
	{
		if (head != NULL)
			return (*head)[index]->Value;
	}

	T& operator[](int index)
	{
		return const_cast<T&>((*static_cast<const LinkedList*>(this))[index]);
	}

private:
	LinkedListNode<T> *head,*tail;
};

#endif
