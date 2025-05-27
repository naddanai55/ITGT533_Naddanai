#include <iostream>
#include <cassert>
#include "SimpleStack.hpp"

using namespace std;
using namespace NP;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    SimpleStack<int>* stack = new SimpleStack<int>(10);
    stack->push(5);
    stack->push(6);
    stack->push(7);
    stack->push(8);
    stack->printStack();


    stack->pop();
    stack->printStack();

    stack->getSize();

    stack->clear();
    stack->printStack();

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}