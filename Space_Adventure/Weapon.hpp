#pragma once
#include <iostream> 

using namespace std;

class Weapon 
{
protected:
    string type;
    int power;

public:
    Weapon(string t, int p) : type(t), power(p) {}
    virtual void fire() = 0;
    virtual unique_ptr<Weapon> clone() const = 0;
    virtual ~Weapon() = default;
    string getType() const 
    { 
        return type; 
    }

    int getPower() const 
    { 
        return power; 
    }

    void setPower(int p) 
    {
        if (p < 0) 
        {
            p = 0;
        }
        power = p;
    }
};
