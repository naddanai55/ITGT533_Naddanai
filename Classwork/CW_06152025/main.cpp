#include <iostream>
#include "GameEngine.hpp"

using namespace NP;
using namespace std;

int main() 
{
	unique_ptr<GameEngine> myGameEngine;

	myGameEngine->init();

	while (true)
	{
		char input;
		cin >> input;
		if (input == 'x')
		{
			break;
		}

		myGameEngine->handleInput();
		myGameEngine->update();
		myGameEngine->render();
	}

	myGameEngine->release();

	return 0;
}