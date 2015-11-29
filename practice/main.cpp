#include <iostream>
#include "Conversions.h"
#include "LinkedList.h"
#include "Heap.h"
#include "PriorityQueue.h"
#include "Polynomial.h"
#include "ExcelColumns.h"

#include <vector>
#include <list>
#include <memory>
#include <queue>

void testConversions()
{
	std::cout << DP::ConvertToString(1025,16) << std::endl;
	std::cout << DP::ConvertToExcel(53) << std::endl;
}

void testLinkedList()
{
	LinkedList<int> list;

	list.Append(1);
	list.Append(2);
	list.Append(3);
	list.Append(100);
	list.Append(4);
	list.Append(5);
	list.Prepend(0);
	list.Remove(4);

	std::cout << list.Count();
}

void testHeap()
{
	Heap<int> heap;

	heap.Insert(54);
	heap.Insert(23);
	heap.Insert(0);
	heap.Insert(2);
	heap.Insert(100);
	heap.Insert(3);

	for (int i = heap.Count(); i > 0; i--)
	{
		std::cout << "MAX: " << heap.GetMax() << endl;
		std::cout << "COUNT: " << heap.Count() << endl;
		std::cout << "--------------------" << endl;

		heap.Delete();
	}
	std::cout << "FINAL COUNT: " << heap.Count();
}

void testPriorityQueue()
{
	PriorityQueue<int> q;
	q.Push(3,High);
	q.Push(100,Low);
	q.Push(77,High);
	q.Push(77,Low);
	q.Push(3,Low);
	q.Push(14,Medium);

	for (int i = q.Count(); i > 0; i--)
	{
		std::cout << "Next Value: " << q.Top() << endl;
		std::cout << "Count: " << q.Count() << endl;
		q.Pop();

		std::cout << "-----------------" << endl;
	}
	std::cout << "Final Count: " << q.Count() << endl;
}

void testPolynomial()
{
	float vals[] = {0,1};

	Polynomial<float> f(vals,2);

	std::cout << "f(x) = x" << endl;
	std::cout << "f(5) = " << f(5) << endl;
	std::cout << "f'(5) = " << (f >> 1)(5) << endl;
	std::cout << "integral(5) = " << (f << 1)(5) << endl;
	std::cout << "integral(1,10) = " << (f << 1).Diff(1,10) << endl;
	std::cout << "-----------------------" << endl;

	Polynomial<float> g(f);
	g[5] = 100;
	g += 2;

	std::cout << "g(x) = 100x^5 + x + 2" << endl;
	std::cout << "g(5) = " << g(5) << endl;
	std::cout << "g'(5) = " << (g >> 1)(5) << endl;
	std::cout << "--------------------" << endl;

	Polynomial<float> h = f * 5;
	std::cout << "h(x) = 5x" << endl;
	std::cout << "h(5) = " << h(5) << endl;
}
/*
bool buildbreak(int nums[]) {
	int num = nums[0];
	while (num != 0)
		if (num == 1)
			return true;
}
*/
void pause()
{
	int n;
	std::cin >> n;
}

void testExcelColumns()
{
	std::cout << "Please enter number of iterations: ";

	unsigned int iterations;
	std::cin >> iterations;
	
	ExcelSimulation simulation;
	std::cout << "-------------------" << endl << simulation.HeaderTitles << "-----------------------" << endl;
	for (unsigned int i = 0; i < iterations; i++) {
		std::cout << simulation;
		simulation.AdvanceToNextColumn();
	}
}
/*keep this for future practice problems*/
struct Node;
typedef unique_ptr<Node> NodePtr;
struct Node {
	int Value;
	NodePtr Left, Right;

	void Print(int tablevel = 0) {
		for (int i = 0; i < tablevel; i++)
			std::cout << '\t';
		std::cout << Value << std::endl;

		if (Left)
			Left->Print(tablevel + 1);
		else
			std::cout << "[NOLEFT]" << std::endl;

		if (Right)
			Right->Print(tablevel + 1);
		else
			std::cout << "[NORIGHT]" << std::endl;
	}

	Node* AddLeft(int value) {
		Left.reset(new Node{ value });
		return Left.get();
	}
	Node* AddRight(int value) {
		Right.reset(new Node{ value });
		return Right.get();
	}
	void AddBoth(int left, int right) {
		AddLeft(left);
		AddRight(right);
	}
};

/*Problem Specific Stuff*/
bool CheckBST(Node &root, int &min, int &max) {
	int lmin = root.Value,
		rmax = root.Value,
		lmax = 0,
		rmin = 0;

	if (root.Left)
		if (!CheckBST(*root.Left, lmin, lmax) || lmax >= root.Value)
			return false;
	if (root.Right)
		if (!CheckBST(*root.Right, rmin, rmax) || rmin < root.Value)
			return false;

	min = lmin;
	max = rmax;
	return true;
}

bool IsBST(Node &root) {
	int dummy1, dummy2;
	return CheckBST(root, dummy1, dummy2);
}

int main()
{/*
	NodePtr root(new Node{ 5 });
	root->AddLeft(4)->AddLeft(3)->AddLeft(2);
	root->AddRight(6)->AddRight(8)->AddBoth(7, 10);*/
	NodePtr root(new Node{ 5 });
	root->AddLeft(4)->AddBoth(3, 6);
	root->AddRight(2);

	bool ret = IsBST(*root);
}