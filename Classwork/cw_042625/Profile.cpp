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
		cout << "Hello\n";
		cout << "1: Your age\n";
		cout << "2: Your dad age\n";
		cout << "0: close\n";
		cout << "--------------------\n";
		cout << "pls select\n";
	}
	int App::calAge(int age)
	{
		return age + 1;
	}
}