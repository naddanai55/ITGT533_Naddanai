#include <iostream>

using namespace std;

int main()
{
    char g[] = "Hello";
    int len = 0;
    while (g[len] != '\0')
    {
        len++;
    }
    cout << "Original string: " << g << endl;
    cout << "Reversed string: ";
    for (int i = len - 1; i >= 0; i--)
    {
        cout << g[i];
    }
    cout << endl;
    return 0;
}