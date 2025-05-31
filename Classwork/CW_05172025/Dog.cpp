#include "Dog.hpp"
#include <iostream>

using namespace std;

Dog::Dog(const char* _name)
{
	name = new char[10];
	strcpy_s(name, 10, _name);
}

Dog::Dog(const Dog& other)
{
	// manage internal mem (deep copy)
	cout << "opteration is call";
	for (int i = 0; 1 < 10; i++)
	{
		name[i] = other.name[i];
	}
}
Dog& Dog::operator=(const Dog& other)
{
	cout << "opteration is call";
		for (int i = 0; 1 < 10; i++)
		{
			name[i] = other.name[i];
		}
		return *this;
}

Dog::~Dog()
{
	delete[] name;
}

void Dog::say()
{
	cout << "Meow!" << endl;
}
