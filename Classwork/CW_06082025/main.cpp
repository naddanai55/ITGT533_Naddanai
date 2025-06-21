#include <chrono>
#include <iostream>
#include "Clock.hpp"

using milli = std::chrono::milliseconds;

const int g_n = 500;
float TestData[g_n][g_n][g_n];

void column_ordered() {
	for (int k = 0; k < g_n; k++)
		for (int j = 0; j < g_n; j++)
			for (int i = 0; i < g_n; i++)
				TestData[i][j][k] = 0.0f;
}

void row_ordered() {
	for (int i = 0; i < g_n; i++)
		for (int j = 0; j < g_n; j++)
			for (int k = 0; k < g_n; k++)
				TestData[i][j][k] = 0.0f;
}

#pragma pack(push, 1)
struct MyStruct
{
	int age = 0;
	char c;
};
#pragma pack(pop)

int main()
{
	NP::Clock c1;
	column_ordered();
	c1.print_elapsed();

	c1.start();
	row_ordered();
	c1.print_elapsed();

	MyStruct sa;
	sa.age = 100;

	std::cout << sizeof(sa);

	return 1;
}