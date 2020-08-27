#include "Queue.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <string>

void Wrapper()
{
	// Int type queue
	cout << "Int Queue" << endl;
	Queue<int> intQueue(new int());
	intQueue.IsEmpty(); // Checks if the queue is empty or not
	intQueue.Push(44); // Adds to the queue
	intQueue.Push(12); // Adds to the queue and then organizes it
	intQueue.Push(28);
	intQueue.Pop(); // Removes the first object in the queue
	intQueue.Push(3);
	intQueue.Print(); // Prints out all the items in the queue
	intQueue.Pop();
	intQueue.Pop();
	intQueue.Push(6);
	intQueue.Print();
	intQueue.GetSize();
	intQueue.IsEmpty(); // Checks if the queue is empty or not again
	cout << endl << endl;

	// Double type queue
	cout << "Double Queue" << endl;
	Queue<double> doubleQueue(new double());
	doubleQueue.IsEmpty();
	doubleQueue.Push(32.5);
	doubleQueue.Push(1.8);
	doubleQueue.Push(32.4);
	doubleQueue.Pop();
	doubleQueue.Push(5);
	doubleQueue.Push(5);
	doubleQueue.Print();
	doubleQueue.Pop();
	doubleQueue.Pop();
	doubleQueue.Push(65.0);
	doubleQueue.Print();
	doubleQueue.GetSize();
	doubleQueue.IsEmpty();
	cout << endl << endl;

	// String type queue
	cout << "String Queue" << endl;
	Queue<string> stringQueue(new string());
	stringQueue.IsEmpty();
	stringQueue.Push("Hello");
	stringQueue.Push("This");
	stringQueue.Push("Out");
	stringQueue.Pop();
	stringQueue.Push("Of");
	stringQueue.Push("Order");
	stringQueue.Print();
	stringQueue.Pop();
	stringQueue.Pop();
	stringQueue.Push("From");
	stringQueue.Push("Garrett");
	stringQueue.Print();
	stringQueue.GetSize();
	stringQueue.IsEmpty();
	cout << endl << endl;
}

int main()
{
	Wrapper();
	_CrtDumpMemoryLeaks();
}