#include <iostream>
#include "math.hpp"
#include "orc.hpp"

using namespace NS;
using namespace ORC;

int main() 
{
    std::cout << "Hello, World!" << std::endl;
    for (int i = 0; i < 3; ++i) 
    {
        std::cout << "Nai" << std::endl;
        std::cout << sum(60, 9) << std::endl;
    }

    Orc orc01 = Orc();
    orc01.attack();
    orc01.die();

    return 0;
}