#include <iostream>
#include <cassert>
#include "String.hpp"

using namespace std;
using namespace NP;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    String s1("Hello");
    String s2(s1);
    String s3(" World");
    String s4 = s1 + s3;
    String s5 = s4.substring(0, 5);
    String a("Apple");
    String b("Banana");

    if (s1.getLength() == 5)
    {
        cout << "C-string is OK" << endl;
        cout << "getLength is OK" << endl;
    }
    if (s1.charAt(4) == 'o')
    {
        cout << "charAt() is OK" << endl;
    }
    if (s2 == s1)
    {
        cout << "copy constructor is OK" << endl;
        cout << "operator== is OK" << endl;
    }
    if (s4 == String("Hello World"))
    {
        cout << "operator+ is OK" << endl;
    }
    if (s5 == s1)
    {
        cout << "substring is OK" << endl;
    }
    if (s1[0] == 'H')
    {
        cout << "operator[] is OK" << endl;
    }
    if (a != b)
    {
        cout << "operator!= is OK" << endl;
    }
    if (a < b) 
    {
        cout << "operator< is OK" << endl;
    }
    if (b > a)
    {
        cout << "operator> is OK" << endl;
    }
    if (a.equals(String("Apple")))
    {
        cout << "equals is OK" << endl;
    }
    if (a.compare(b) < 0)
    {
        cout << "compare is OK" << endl;
    }

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}
