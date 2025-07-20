#pragma once

namespace NP
{
	class Vector2
	{
	public:
		float m_x;
		float m_y;

		Vector2(): m_x(0.0f), m_y(0.0f) {}
		Vector2(float x, float y) : m_x(x), m_y(y) {}

		Vector2& operator=(const Vector2& other)
		{
			m_x = other.m_x;
			m_y = other.m_y;
			return *this;
		}
		Vector2& operator +=(const Vector2& other)
		{
			m_x += other.m_x;
			m_y += other.m_y;
			return *this;
		}
	};
}  