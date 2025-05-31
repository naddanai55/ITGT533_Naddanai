#pragma once
#include "Shape.hpp"

namespace NP

{
    //Inheritance
    class Tri : public Shape
    {
    public:
        //Constructor
        Tri();
        Tri(float base, float height);

        void setDimension(float base, float height);
        //Inheritance
        float getArea() const override;
        void printStat() const override;

    private:
        float m_base;
        float m_height;
    };
}