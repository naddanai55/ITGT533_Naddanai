#include <iostream>
#include <cassert>
#include "DynamicArray.hpp"

using namespace std;
using namespace NP;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}