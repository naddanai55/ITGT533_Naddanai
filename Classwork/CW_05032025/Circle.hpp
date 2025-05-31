#pragma once
#include "Shape.hpp"

namespace NP

{
    const float PI = 3.14f;
    //Inheritance
    class Circle: public Shape
    {
    public:
        //Constructor
        Circle();
        Circle(float radius);

        void setRadius(float radius);
        //Inheritance
        float getArea() const override;
        void printStat() const override;

    private:
        float m_radius;
    };
}