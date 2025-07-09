#pragma once

#include <iostream>

namespace NP
{
    template<typename T>
    class Vector3
    {
    public:
        T x, y, z;
        Vector3() : x(T(0)), y(T(0)), z(T(0)) {}
        explicit Vector3(T scalar) : x(scalar), y(scalar), z(scalar) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vector3(const Vector3& other) = default;
        Vector3& operator=(const Vector3& other) = default;
        static Vector3 Ones() 
        { 
            return Vector3(T(1), T(1), T(1)); 
        }
        static Vector3 Zeros() 
        { 
            return Vector3(T(0), T(0), T(0)); 
        }
        static Vector3 Up() 
        { 
            return Vector3(T(0), T(1), T(0)); 
        }
        static Vector3 Down() 
        { 
            return Vector3(T(0), T(-1), T(0)); 
        }
        static Vector3 Right() 
        { 
            return Vector3(T(1), T(0), T(0)); 
        }
        static Vector3 Left() 
        { 
            return Vector3(T(-1), T(0), T(0)); 
        }
        static Vector3 Forward() 
        { 
            return Vector3(T(0), T(0), T(1)); 
        }
        static Vector3 Back() 
        { 
            return Vector3(T(0), T(0), T(-1)); 
        }
        T LengthSq() const
        {
            return x * x + y * y + z * z;
        }
        T Length() const
        {
            return sqrt(LengthSq());
        }
        void Normalize()
        {
            T len = Length();
            if (len > std::numeric_limits<T>::epsilon())
            {
                x /= len;
                y /= len;
                z /= len;
            }
        }
        Vector3 Normalized() const
        {
            Vector3 result = *this;
            result.Normalize();
            return result;
        }
        static T Dot(const Vector3& a, const Vector3& b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
        static Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return Vector3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }
        static T Angle(const Vector3& a, const Vector3& b)
        {
            T magProduct = a.Length() * b.Length();
            if (magProduct < std::numeric_limits<T>::epsilon())
            {
                return T(0);
            }
            T dot = Dot(a, b);
            T cosTheta = dot / magProduct;
            cosTheta = std::max(T(-1), std::min(T(1), cosTheta));
            return acos(cosTheta);
        }
        bool operator==(const Vector3& other) const
        {
            return (std::abs(x - other.x) < std::numeric_limits<T>::epsilon() &&
                std::abs(y - other.y) < std::numeric_limits<T>::epsilon() &&
                std::abs(z - other.z) < std::numeric_limits<T>::epsilon());
        }
        bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }
        Vector3 operator+(const Vector3& other) const 
        { 
            return Vector3(x + other.x, y + other.y, z + other.z); 
        }
        Vector3 operator-(const Vector3& other) const 
        { 
            return Vector3(x - other.x, y - other.y, z - other.z); 
        }
        Vector3 operator-() const 
        { 
            return Vector3(-x, -y, -z); 
        }
        Vector3 operator*(T scalar) const 
        { 
            return Vector3(x * scalar, y * scalar, z * scalar); 
        }
        Vector3 operator/(T scalar) const 
        { 
            return Vector3(x / scalar, y / scalar, z / scalar); 
        }
        Vector3& operator+=(const Vector3& other) 
        { 
            x += other.x; y += other.y; z += other.z; 
            return *this; 
        }
        Vector3& operator-=(const Vector3& other) 
        { 
            x -= other.x; y -= other.y; z -= other.z; 
            return *this; 
        }
        Vector3& operator*=(T scalar) 
        { 
            x *= scalar; y *= scalar; z *= scalar; 
            return *this; 
        }
        Vector3& operator/=(T scalar) 
        {
            x /= scalar; y /= scalar; z /= scalar; 
            return *this; 
        }
    };

    template<typename T>
    Vector3<T> operator*(T scalar, const Vector3<T>& vec)
    {
        return vec * scalar;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vector3<T>& vec)
    {
        os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
    using vec3f = Vector3<float>;
    using vec3i = Vector3<int>;
    using vec3d = Vector3<double>;
}