#pragma once
#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>

using namespace std;
#include <ctype.h>

template <class T>

class Queue
{
private:
	// All the variables used
	T* pointer;
	int size = 4;
	int current = 0;
public:
	// Constructor
	Queue(T* _ptr = NULL)
	{
		pointer = new T[size]{};
		pointer = _ptr;
	};

	// Copy Constructor
	Queue(Queue const& copy)
	{
		size = copy.size;
		pointer = new int[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = copy.pointer[i];
		}
	};

	// Copy Assignment Constructor
	Queue& operator=(Queue const& copy)
	{
		if (this == &copy)
		{
			return *this;
		}
		if (pointer != nullptr)
		{
			delete[] pointer;
			pointer = nullptr;
			size = 0;
		}

		size = copy.size;
		pointer = new int[size];

		for (int i = 0; i < size; i++)
		{
			pointer[i] = copy.pointer[i];
		}

		return *this;
	};

	// Destructor
	~Queue()
	{
		delete pointer;
		pointer = nullptr;
	};

	// Adds to the queue and then calls the organize method
	void Push(T data)
	{
		if (size == current)
		{
			// Doubles thesize of the queue if it gets filled
			size *= 2;

			T* copyQueue = new T[size]{};

			for (int i = 0; i < current; i++)
			{
				copyQueue[i] = pointer[i];
			}
			// It crashes everytime I try to delete the pointer here
			// delete[] pointer
			pointer = copyQueue;
		}
		pointer[current] = data;

		current++;
		//Organize(); // Organize method causes an exception so it is commented out
	};

	// Removes the first/lowest object on the queue
	void Pop()
	{
		if (current != 0)
		{
			for (int i = 0; i < current; i++)
			{
				if (i + 1 == current)
				{
					//pointer[i] = NULL; // Causes an error everytime I try to make it NULL
				}
				else
				{
					pointer[i] = pointer[i + 1];
				}
			}
		}
		// Does not let the queue pop if there is nothing to pop
		else
		{
			cout << "Cannot pop when there is nothing in the queue" << endl;
		}
	};
	// Takes all of the objects in the queue and organizes them from smallest to largest
	// (Strings from smallest memory size to largest)
	/*
	void Organize()
	{
		T* copyQueue = new T[size]{};

		if (isdigit(pointer[0]) == false)
		{
			T placeholder;
			for (int i = 0; i < current; i++)
			{
				int amount = 0;
				for (int j = i; j < current; j++)
				{
					if (amount == 0)
					{
						amount = sizeof(pointer[j]);
						placeholder = pointer[j];
					}
					else
					{
						if (amount > sizeof(pointer[j]))
						{
							amount = sizeof(pointer[j]);
							placeholder = pointer[j];
						}
					}
				}
				copyQueue[i] = placeholder;
			}

			pointer = copyQueue;
		}
		else
		{
			for (int i = 0; i < current; i++)
			{
				T amount = 0;
				for (int j = i; j < current; j++)
				{
					if (j == i)
					{
						amount = pointer[j];
					}
					else
					{
						if (amount > pointer[j])
						{
							amount = pointer[j];
						}
					}
				}
				copyQueue[i] = amount;
			}

			pointer = copyQueue;
		}
	}
	*/

	// Prints out of the objects in the queue 
	void Print()
	{
		cout << endl << "Data on the queue:" << endl;

		for (int i = 0; i << current; i++)
		{
			cout << pointer[i] << endl; // Does not print anything for some reason
		}
	};

	// Returns the amount of entries in the queue
	int GetSize()
	{
		cout << "Current size of the queue is: " << current << endl;
		return current;
	};

	// Returns true or false depending on if the queue is empty or not
	bool IsEmpty()
	{
		if (current == 0)
		{
			cout << "The stack is empty" << endl;
			return true;
		}
		else
		{
			cout << "There is data in the array" << endl;
			return false;
		}
	}
};

#endif //_MAIN_H
