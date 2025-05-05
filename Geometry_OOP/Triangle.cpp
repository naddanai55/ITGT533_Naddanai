#include <iostream>
#include <cassert>
#include "Triangle.hpp"

using namespace std;
namespace NP

{
	//Constructor
	Tri::Tri() :m_base{0.0f}, m_height{0.0f}{}
	Tri::Tri(float base, float height) :m_base(base), m_height(height)
	{
		assert(m_base and m_height > 0.0f);
	}

	void Tri::setDimension(float base, float height)
	{
		assert(base > 0.0f);
		assert(height > 0.0f);

		this->m_base = base;
		this->m_height = height;

		assert(this->m_base and m_height > 0.0f);
	}
	float Tri::getArea() const
	{
		return 0.5f * m_base * m_base;
	}
	void Tri::printStat() const
	{
		cout << "Base: " << this->m_base << endl;
		cout << "Height: " << this->m_height << endl;
	}
}