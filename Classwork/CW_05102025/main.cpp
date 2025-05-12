#include <iostream>

using namespace std;

void main()
{
	//string test = "Nai";
	//string *ptr = &test;
	//int *ptr2 = NULL;
	//int nai = 5;
	//bool tt = true;

	//cout << test << endl;
	//cout << &tt << endl;
	//cout << &nai << endl;
	//cout << &test << endl;
	//cout << sizeof(ptr) << endl;
	//cout << *ptr2 << endl;

	//char s[] = "strawberry";
	//int count = 0;
	//string ls = s;
	//cout << ls << endl;
	////int ls = s.length();
	////cout << ls << endl;
	//cout << s[0];

	//char* ptr = s;
	//int count = 0;

	//ptr[2] = 'z';
	//cout << s << endl;

	char g[] = "strawberry";
	char c = 'r';
	char* ptr_g = g;
	unsigned int count = 0;
	unsigned int count_2 = 0;
	int* ptr_a = nullptr;
	int** pptr_a = &ptr_a;

	cout << pptr_a << endl;
	
	//cout << sizeof(g) << " " << ptr_g << " " << ptr_a << endl;
	//cout << strlen(g) << " " << ptr_g << " " << ptr_a << endl;
	cout << ptr_g + (strlen(g) - 1) << endl;

	int i = 0;
	while (i < sizeof(g))
	{
		if (*(ptr_g + i) == c)
		{
			count++;
		}
		i++;
	}
	//cout << count << endl;

	while (*ptr_g != '\0')
	{
		if (*ptr_g == c)
		{
			count_2++;
		}
		ptr_g++;
	}
	//cout << count_2 << endl;
}