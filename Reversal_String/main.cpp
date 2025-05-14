#include <iostream>

using namespace std;

void textSwap(char* ptr_g);

int main()
{
    char g[100] = ""; 
    cout << "Enter a string: ";
    cin.getline(g, 100);
    cout << "Original string: " << g << endl;
    char* ptr_g = g;
    cout << "Reversed string: ";
    textSwap(ptr_g);
    return 0;
}

void textSwap(char* ptr_g)
{
    for (int i = strlen(ptr_g) - 1; i >= 0; i--)
    {
        cout << *(ptr_g + i);
    }
}