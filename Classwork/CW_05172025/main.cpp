#include <iostream>
#include <cassert>
#include "Dog.hpp"

using namespace std;


void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Dog d = Dog();
	Dog d2 = d;
	Dog d3(d);
	d2 = d3;

	Dog* ptr_d1 = new Dog();
	Dog* ptr_d2 = new Dog(*ptr_d1);
	*ptr_d1 = *ptr_d2;

	delete ptr_d1;
	delete ptr_d2;
	
	assert(_CrtCheckMemory());
	_CrtDumpMemoryLeaks();
}