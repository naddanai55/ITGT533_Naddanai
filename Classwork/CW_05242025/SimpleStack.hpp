#pragma once
#include <iostream>

using namespace std;

namespace NP 
{
	template<typename T>
	class SimpleStack
	{
	private:
		T* ptr_buffer;
		T top;
		size_t capacity;

	public:
		SimpleStack();
		SimpleStack(size_t maxsize);

		void push(const T& value);
		T pop();

		void printStack() const; // not change
		void clear(); // empty

		size_t getSize() const;
	};
}

	template<typename T>
	SimpleStack<T>::SimpleStack() {}

	template<typename T>
	SimpleStack<T>::SimpleStack(size_t maxsize)
	{
		ptr_buffer = new T[maxsize];
		capacity = maxsize;
		top = -1;
	}

	template<typename T>
	void SimpleStack<T>::push(const T& value)
	{
		if (top == capacity - 1)
		{
			return;
		}
		ptr_buffer[++top] = value;
	}

	template<typename T>
	T SimpleStack<T>::pop()
	{
		if (top == -1)
		{
			return -1;
		}
		return ptr_buffer[top--];
	}

	template<typename T>
	void SimpleStack<T>::printStack() const
	{
		for (int i = 0; i <= top; ++i)
		{
			cout << ptr_buffer[i];
		}
		cout << endl;
	}

	template<typename T>
	void SimpleStack<T>::clear()
	{
		delete[] ptr_buffer;

	}

	template<typename T>
	size_t SimpleStack<T>::getSize() const
	{
		int size = 0;
		for (int i = 0; i <= top; ++i)
		{
			size++;
		}

		cout << size << endl;
		return size;
	}
