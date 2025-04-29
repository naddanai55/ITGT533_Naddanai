#include <iostream>
#include "orc.hpp"

namespace ORC
{
    Orc::Orc()
    {
        std::cout << "Orc init" << std::endl;
    }

    void Orc::attack()
    {
        std::cout << "Orc attack" << std::endl;
    }

    void Orc::die()
    {
        std::cout << "Orc die" << std::endl;
    }
}