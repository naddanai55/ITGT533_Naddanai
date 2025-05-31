#pragma once

namespace NP

{
    //Abstract
    class Shape
    {
    public:
        //Parent
        virtual float getArea() const = 0;
        virtual void printStat() const = 0;

    private:
    };
}