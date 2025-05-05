#include <iostream>
#include "App.hpp"

using namespace std;
namespace NP

{
	App::App() {}

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

	void App::closeApp()
	{
		cout << "Goodbye!" << endl;
	}
}