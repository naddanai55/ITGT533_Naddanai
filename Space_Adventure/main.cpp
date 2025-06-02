#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    cout << "test";

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}