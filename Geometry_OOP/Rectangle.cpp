#include <iostream>
#include <cassert>
#include "Rectangle.hpp"

using namespace std;
namespace NP

{
	//Constructor
	Rect::Rect():m_width{0.0f}, m_length{0.0f}{}
	Rect::Rect(float width, float length):m_width(width), m_length(length) 
	{
		assert(m_length and m_width > 0.0f);
	}

	void Rect::setDimension(float width, float length)
	{
		assert(width > 0.0f );
		assert(length > 0.0f);

		this->m_width = width;
		this->m_length = length;

		assert(this->m_width and m_length > 0.0f);
	}
	float Rect::getArea() const
	{
		return m_width * m_length;
	}
	void Rect::printStat() const
	{
		cout << "Width: " << this->m_width << endl;
		cout << "Length: " << this->m_length << endl;
	}
}