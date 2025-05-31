#pragma once

class Dog
{
public:
	Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	~Dog();
	void say();

private:
	int leg;
	char* name;
};

