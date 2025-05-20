#include <iostream>
#include <cassert>
#include "dog.hpp"

using namespace std;

void makeSay(Dog& d)
{
  d.say();
}

void main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::string s = "hello this is a string";
    std::string s2 = "hello string 2";
    s = s2;
    std::string s3 = s + s2;

    Dog* p_d1 = new Dog("Mark"); // constructor is called

    makeSay(*p_d1);

    delete p_d1;

  assert(_CrtCheckMemory());
  _CrtDumpMemoryLeaks();

}