#include <iostream>
#include "Profile.hpp"

using namespace std;

namespace CW
{
    App::App()
    {

    }

    void App::showInstruct()
    {
        cout << "==============================" << endl;
        cout << "     Geometry Calculator" << endl;
        cout << "==============================" << endl;
        cout << "1: Rectangle" << endl;
        cout << "2: Triangle" << endl;
        cout << "3: Circle" << endl;
        cout << "0: Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "Enter your choice: ";
    }

    float App::calRec(float width, float length)
    {
        return width * length;
    }

    float App::calTri(float base, float height)
    {
        return 0.5f * base * height;
    }

    float App::calCir(float radius)
    {
        const float PI = 3.14f;
        return PI * radius * radius;
    }
}