#pragma once

class Dog
{
public:
  
  Dog();
  Dog(const char* _name);

  // rule of three
  Dog(const Dog& other); // copy constructor
  Dog& operator=(const Dog& other);
  ~Dog();

  void say();

private:
  int leg;
  char* name;
};

