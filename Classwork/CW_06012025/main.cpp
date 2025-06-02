#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Animal 
{
public:
    virtual void makeSound() = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() override { std::cout << "Woof!" << std::endl; }
    void fetch() { std::cout << "Fetching ball!" << std::endl; }
};

class Cat : public Animal 
{
public:
    void makeSound() override { std::cout << "Meow!" << std::endl; }
    void scratch() { std::cout << "Scratching post!" << std::endl; }
};

// TODO: Create Animal pointers pointing to Dog and Cat
// TODO: Try both static_cast and dynamic_cast to convert them
// TODO: Test what happens when casting to wrong type

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    double d = 3.14159;
    float f = 2.71828;
    int i = 42;

    int d2 = static_cast<int>(d);
    cout << d2 << endl;

    double f2 = static_cast<double>(f);
    cout << f2 << endl;

    float i2 = static_cast<float>(i);
    cout << i2 << endl;

    Animal* dog = new Dog();
    Animal* cat = new Cat();

    //dog->makeSound();
    //cat->makeSound();

 /*   Dog* new_dog = static_cast<Dog*>(cat);
    Cat* new_cat = static_cast<Cat*>(dog);*/

    Dog* new_dog = dynamic_cast<Dog*>(cat);

    shared_ptr<Dog> ptr_dog = make_shared<Dog>();
    weak_ptr<Dog> ptr_dog_weak = ptr_dog;

    ptr_dog->fetch();
    ptr_dog_weak.lock()->fetch();

    return 1;


    //if (new_dog) 
    //{
    //    new_dog->makeSound();
    //}
    //else 
    //{
    //    std::cout << "dynamic_cast failed!\n";
    //}

    //delete dog;


    //vector<int> arr;
    //arr.push_back(1);
    //arr.push_back(2);
    //arr.push_back(3);

    //for (int i = 1; i < arr.size(); i++)
    //{
    //    cout << arr[i];
    //}

    //for (vector<int>::iterator it = arr.begin(); it != arr.end(); it++)
    //{
    //    cout << *it << endl;
    //}
    //for (auto it = arr.begin(); it != arr.end(); it++)
    //{
    //    cout << *it << endl;
    //}

    //std::vector<int> numbers = { 1, 2, 3, 4, 5 };

    //for (int number : numbers) {
    //    std::cout << number << " ";
    //}
    //std::cout << std::endl;

    //// Using auto for type deduction
    //for (auto number : numbers) {
    //    std::cout << number << " ";
    //}
    //std::cout << std::endl;

    //// Using reference to modify elements
    //for (int& number : numbers) {
    //    number *= 2;
    //}

    //for (int number : numbers) {
    //    std::cout << number << " ";
    //}
    //std::cout << std::endl;

    //// Using const reference to avoid copying
    //for (const int& number : numbers) {
    //    std::cout << number << " ";
    //}
    //std::cout << std::endl;

    //float a = 0.5f;
    //cout << static_cast<int>(a);

    assert(_CrtCheckMemory());
    _CrtDumpMemoryLeaks();
}
