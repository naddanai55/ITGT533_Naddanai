#pragma once
#ifndef PROFILE_HPP
#define PROFILE_HPP

namespace CW
{
    class App
    {
    public:
        App();

        void showInstruct();
        float calRec(float width, float length);   
        float calTri(float base, float height);    
        float calCir(float radius);
    };
}

#endif