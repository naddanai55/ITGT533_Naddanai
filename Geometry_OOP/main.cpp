#include <iostream>
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "App.hpp"

using namespace std;
using namespace NP;

int main()
{
    Circle cir;
    Rect rect;
    Tri tri;
	App app;

    int choice;
    float a, b;
    while (true)
    {
		app.showInstruct();
        cin >> choice;

        if (choice == 0)
        {
			app.closeApp();
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
            rect.setDimension(a, b);
            cout << "Area of Rectangle: " << rect.getArea() << endl;
            cout << "" << endl;
            break;

        case 2: // Triangle
            cout << "Enter base: ";
            cin >> a;
            cout << "Enter height: ";
            cin >> b;
            cout << "" << endl;
            tri.setDimension(a, b);
            cout << "Area of Triangle: " << tri.getArea() << endl;
            cout << "" << endl;
            break;

        case 3: // Circle
            cout << "Enter radius: ";
            cin >> a;
            cout << "" << endl;
            cir.setRadius(a);
            cout << "Area of Circle: " << cir.getArea() << endl;
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