#ifndef HEAP
#define HEAP

#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::swap;
using std::max;

template<class T> class Heap {
public:
	Heap()
	{
		values.resize(1);	//throw-away value
	}

	void Insert(T value)
	{
		values.push_back(value);
		fixupHeap(true);
	}

	void Delete()
	{
		if (values.size() == 1)	//could throw exception
			return;

		if (values.size() == 2)
		{
			values.pop_back();
			return;
		}

		values[1] = values.back();
		values.pop_back();

		fixupHeap(false);
	}

	const T& GetMax() const
	{
		if (values.size() == 1)	//could throw exception
			throw 0;

		return values[1];
	}

	int Count() const
	{
		return values.size() - 1;
	}

protected:
	void fixupHeap(bool fixUpwards = false)
	{
		if (values.size() == 1)
			return;

		if (fixUpwards)
		{
			for (int i = values.size()-1; i / 2 >= 1; i /= 2)
				if (values[i/2] < values[i])
					swap(values[i],values[i/2]);
		}
		else
		{
			unsigned int parent = 1;
			while (parent * 2 < values.size())
			{
				unsigned int leftChild = parent*2;
				unsigned int rightChild = leftChild + 1;
				bool hasRightChild = rightChild < values.size();
				bool leftLarger = !hasRightChild || values[rightChild] < values[leftChild];
				unsigned int largestChild = leftLarger ? leftChild : rightChild;

				if (!(values[parent] < values[largestChild]))
					break;

				swap(values[parent],values[largestChild]);
				parent = largestChild;
			}
		}
	}

	vector<T> values;
};

#endif
