#ifndef LINKEDLISTNODE
#define LINKEDLISTNODE

template<typename T> class LinkedListNode {
public:
	LinkedListNode(T value):
	  Value(value),previous(NULL),next(NULL) {}

	//length of list containing this node and all after it
	int Count() const
	{
		int len=1;
		const LinkedListNode* ptr;

		for (ptr = this; ptr->next != NULL; ptr = ptr->next)
			len++;

		return len;
	}

	const LinkedListNode* operator[](int index) const	//should document exception that can be thrown
	{
		const LinkedListNode* ptr=this;

		for (int i = 0; i < index; ptr = ptr->next, i++)
			if (ptr == NULL)
				throw 0;

		return ptr;
	}

	LinkedListNode* operator[](int index)
	{
		return const_cast<LinkedListNode*>((*static_cast<const LinkedListNode*>(this))[index]);
	}

	const LinkedListNode* Back() const
	{
		const LinkedListNode* ptr;

		for (ptr = this; ptr->next != NULL; ptr = ptr->next);

		return ptr;
	}

	const LinkedListNode* Front() const
	{
		const LinkedListNode* ptr;

		for (LinkedListNode* ptr = this; ptr->previous != NULL; ptr = ptr->previous);

		return ptr;
	}

	LinkedListNode* Back()
	{
		return const_cast<LinkedListNode*>(static_cast<const LinkedListNode*>(this)->Back());
	}

	LinkedListNode* Front()
	{
		return const_cast<LinkedListNode*>(static_cast<const LinkedListNode*>(this)->Front());
	}

	LinkedListNode* Append(const T& value)
	{
		LinkedListNode* back = Back();

		back->next = new LinkedListNode(value);
		back->next->previous = back;

		return back->next;
	}

	LinkedListNode* Insert(const T& value, int index)
	{
		LinkedListNode* after = (*this)[index];	//might throw exception
		LinkedListNode* newNode = new LinkedListNode(value);

		newNode->next = after;
		newNode->previous = after->previous;
		if (after->previous != NULL)
			after->previous->next = newNode;
		after->previous = newNode;

		return newNode;
	}

	void Remove(int index)
	{
		LinkedListNode* node = (*this)[index];	//might throw exception

		if (node->previous != NULL)
			node->previous->next = node->next;
		if (node->next != NULL)
			node->next->previous = node->previous;

		delete node;
	}

	T Value;
private:
	LinkedListNode* previous;
	LinkedListNode* next;
};

#endif