#include <iostream>

using namespace std;

void textSwap(char* ptr_g);

int main()
{
    char g[100] = ""; 
    cout << "Original: ";
    cin >> g; 
    char* ptr_g = g;
    cout << "Reversed: ";
    textSwap(ptr_g);
    return 0;
}

void textSwap(char* ptr_g)
{
    int len = strlen(ptr_g);
    for (int i = len - 1; i >= 0; i--)
    {
        cout << *(ptr_g + i);
    }
}