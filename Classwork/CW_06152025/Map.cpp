#include "Map.hpp"
#include <iostream>

using namespace std; 
namespace NP 
{

	Map::Map()
	{
		tiles = new char[height * width];
	}

	void Map::draw()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				cout << tiles[y * width + x];
			}
			cout << endl;
		}
	}
}