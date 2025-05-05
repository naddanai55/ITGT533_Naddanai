#include <iostream>
#include <cassert>
#include "Circle.hpp"

using namespace std;
namespace NP

{
	//Constructor
	Circle::Circle() :m_radius(0.0f){} 
	Circle::Circle(float radius):m_radius(radius)
	{
		assert(radius > 0.0f);
	} 

	void Circle::setRadius(float radius)
	{
		assert(radius > 0.0f);
		this->m_radius = radius;
		assert(this->m_radius > 0.0f);
	}
	float Circle::getArea() const
	{
		return PI * m_radius * m_radius;
	}
	void Circle::printStat() const
	{
		cout << "Circle radius: " << this->m_radius << endl;
	}
}