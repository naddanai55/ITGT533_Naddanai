#pragma once
#include "Shape.hpp"

namespace NP

{
    //Inheritance
    class Rect : public Shape
    {
    public:
        //Constructor
        Rect();
        Rect(float width, float length);

        void setDimension(float width, float length);
        //Inheritance
        float getArea() const override;
        void printStat() const override;

    private:
        float m_width;
        float m_length;
    };
}