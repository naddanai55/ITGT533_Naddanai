#include <iostream>
#include "Profile.hpp"

using namespace std;
using namespace CW;
 
void main()
{
	App app = App();
	int age = 0;
	int code = NULL;
	while (true)
	{
		app.showInstruct();
		cin >> code;
		if (code == 0)
		{
			break;
		}
        switch (code)
		{
			case 0:
				break;
			case 1:
				cout << "how old are you\n";
				cin >> age;
				cout << "next year u will " << app.calAge(age) << " \n";
				cout << "--------------------\n";
				break;
			case 2:
				cout << "how old ur dad\n";
				cin >> age;
				cout << "next year ur dad will " << app.calAge(age) << " \n";
				cout << "--------------------\n";
				break;
        }
	}
}