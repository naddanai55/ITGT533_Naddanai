#pragma once
#include <iostream> 
#include <string>

using namespace std;

class Weapon 
{
protected:
    string type;
    int power;

public:
    Weapon(string t, int p) : type(t), power(p) {} // Constructor
    virtual void fire() = 0;
    virtual ~Weapon() = default;
    string getType() const 
    { 
        return type; 
    }
    int getPower() const 
    { 
        return power; 
    }
};
