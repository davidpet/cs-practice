#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include "Heap.h"

enum Priority
{
	Low,
	Medium,
	High
};

template<class T> class PriorityQueueMessage
{
public:
		T Value;
		Priority Priority;
		int QueueIndex;	//for the queue itself to scribble on (lower number = inserted first)

		PriorityQueueMessage(const T& value, ::Priority priority):
			Value(value),
			Priority(priority)
			{
			}

		PriorityQueueMessage()
		{
		}

		bool operator<(const PriorityQueueMessage<T>& rightMessage)
		{
			if (Priority < rightMessage.Priority)
				return true;
			if (Priority > rightMessage.Priority)
				return false;

			return QueueIndex > rightMessage.QueueIndex;
		}
};

template<class T> class PriorityQueue: private Heap<PriorityQueueMessage<T>>
{
public:
	PriorityQueue():
	  nextQueueIndex(0)
	{
	}

	void Push(T value, Priority priority)
	{
		PriorityQueueMessage<T> message (value,priority);
		message.QueueIndex = nextQueueIndex++;

		Insert(message);
	}

	const T& Top()
	{
		PriorityQueueMessage<T> message = GetMax();
		return message.Value;
	}

	void Pop()
	{
		Delete();
	}

	using Heap<PriorityQueueMessage<T>>::Count;
protected:
	int nextQueueIndex;
};

#endif