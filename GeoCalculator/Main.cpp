#include <iostream>
#include "Profile.hpp"

using namespace std;
using namespace CW;

int main()
{
    App app;
    int choice;
    float a, b;

    while (true)
    {
        app.showInstruct();
        cin >> choice;

        if (choice == 0)
        {
            cout << "Goodbye!" << endl;
            break;
        }

        switch (choice)
        {
        case 1: // Rectangle
            cout << "Enter width: ";
            cin >> a;
            cout << "Enter length: ";
            cin >> b;
            cout << "" << endl;
            cout << "Area of Rectangle: " << app.calRec(a, b) << endl;
            cout << "" << endl;
            break;

        case 2: // Triangle
            cout << "Enter base: ";
            cin >> a;
            cout << "Enter height: ";
            cin >> b;
            cout << "" << endl;
            cout << "Area of Triangle: " << app.calTri(a, b) << endl;
            cout << "" << endl;
            break;

        case 3: // Circle
            cout << "Enter radius: ";
            cin >> a;
            cout << "" << endl;
            cout << "Area of Circle: " << app.calCir(a) << endl;
            cout << "" << endl;
            break;

        default:
            cout << "" << endl;
            cout << "Choice error. Please try again." << endl;
            cout << "" << endl;
            break;
        }
        break;
    }
}