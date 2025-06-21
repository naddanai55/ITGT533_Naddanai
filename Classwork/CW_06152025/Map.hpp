#pragma once

namespace NP 
{
	class Map
	{
	public:
		Map();
		void draw();

	private:
		const unsigned int width = 20;
		const unsigned int height = 20;
		char* tiles;
	};

}

