#include <iostream>
#include <cassert>
#include "DynamicArray.hpp"

using namespace std;
using namespace NP;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    DynamicArray<int> arr;
    cout << "Create DynamicArray as arr" << endl;
    cout << arr.data_ptr() << endl;

    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;
    cout << "Elements: ";
    if (arr.empty()) 
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        for (size_t i = 0; i < arr.size(); ++i) 
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Memory usage: " << arr.memory_usage() << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Adding 3 elements using push_back()" << endl;
    arr.push_back(10);
    cout << "push_back 10" << endl;
    arr.push_back(20);
    cout << "push_back 20" << endl;
    arr.push_back(30);
    cout << "push_back 30" << endl;
    cout << endl;

    cout << "After adding 3 elements" << endl;
    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;
    cout << "Elements: ";
    if (arr.empty())
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Memory usage: " << arr.memory_usage() << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Add more elements to trigger dynamic growth" << endl;
    for (int i = 4; i <= 11; ++i) 
    {
        cout << "push_back " << i * 10 << endl;
        arr.push_back(i * 10);
    }
    cout << endl;

    cout << "After triggering growth" << endl;
    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;
    cout << "Elements: ";
    if (arr.empty())
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Memory usage: " << arr.memory_usage() << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Accessing elements:" << endl;
    if (arr.size() > 5) 
    {
        cout << "Element at index 0: " << arr.front() << endl; 
        cout << "Element at index 5: " << arr[5] << endl;
        cout << "Last element: " << arr.back() << endl;
    }
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Removing last element using pop_back()" << endl;
    if (!arr.empty()) 
    {
        arr.pop_back();
        cout << "After pop_back" << endl;
        cout << "Size: " << arr.size() << endl;
        cout << "Capacity: " << arr.capacity() << endl;
        cout << "Elements: ";
        if (arr.empty())
        {
            cout << "[Empty]" << endl;
        }
        else
        {
            for (size_t i = 0; i < arr.size(); ++i)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }

        cout << "Memory usage: " << arr.memory_usage() << endl;
        cout << endl;
    }
    cout << "--------------------------------------------------" << endl;

    cout << "resiz to 30 " << endl;
    arr.resize(30);
    cout << "After resize" << endl;
    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;
    cout << "Elements: ";
    if (arr.empty())
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Memory usage: " << arr.memory_usage() << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Clearing the array using clear()" << endl;
    arr.clear();
    cout << "After clear:" << endl;
    cout << "Size: " << arr.size() << endl;
    cout << "Capacity: " << arr.capacity() << endl;
    cout << "Elements: ";
    if (arr.empty())
    {
        cout << "[Empty]" << endl;
    }
    else
    {
        for (size_t i = 0; i < arr.size(); ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    cout << "Memory usage: " << arr.memory_usage() << endl;
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    //return 0;

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}
