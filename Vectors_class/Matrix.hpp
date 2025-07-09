#pragma once

#include "Vector3.hpp"
#include <iostream>

namespace NP 
{

    template<typename T>
    class Matrix4 {
    public:
        T m[16];
        Matrix4() 
        {
            m[0] = 1; m[4] = 0; m[8] = 0;  m[12] = 0;
            m[1] = 0; m[5] = 1; m[9] = 0;  m[13] = 0;
            m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
            m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
        }

        explicit Matrix4(T scalar)
        {
            m[0] = scalar; m[4] = 0;     m[8] = 0;      m[12] = 0;
            m[1] = 0;      m[5] = scalar; m[9] = 0;      m[13] = 0;
            m[2] = 0;      m[6] = 0;      m[10] = scalar; m[14] = 0;
            m[3] = 0;      m[7] = 0;      m[11] = 0;      m[15] = 1;
        }


        Matrix4& Transpose()
        {
            std::swap(m[1], m[4]);
            std::swap(m[2], m[8]);
            std::swap(m[3], m[12]);
            std::swap(m[6], m[9]);
            std::swap(m[7], m[13]);
            std::swap(m[11], m[14]);
            return *this;
        }

        Matrix4 Transposed() const 
        {
            return Matrix4(*this).Transpose();
        }

        Matrix4& Inverse() 
        {
            T inv[16];

            inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
            inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
            inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
            inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
            inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
            inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
            inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
            inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
            inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
            inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
            inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
            inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
            inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
            inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
            inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
            inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

            T det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

            if (det == 0) return *this; // Or handle error appropriately

            det = 1.0 / det;
            for (int i = 0; i < 16; i++) m[i] = inv[i] * det;
            return *this;
        }

        Matrix4 Inversed() const {
            return Matrix4(*this).Inverse();
        }

        static Matrix4 Translate(const Vector3<T>& v) 
        {
            Matrix4 res;
            res.m[12] = v.x;
            res.m[13] = v.y;
            res.m[14] = v.z;
            return res;
        }

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (int i = 0; i < 4; ++i) { // column
                for (int j = 0; j < 4; ++j) { // row
                    T sum = 0.0;
                    for (int k = 0; k < 4; ++k) {
                        sum += m[k * 4 + j] * other.m[i * 4 + k];
                    }
                    result.m[i * 4 + j] = sum;
                }
            }
            return result;
        }

        Vector3<T> operator*(const Vector3<T>& vec) const {
            T x = m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12]; 
            T y = m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13];
            T z = m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14];
            T w = m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15];

            // Perspective divide
            if (w != 0 && w != 1) {
                return Vector3<T>(x / w, y / w, z / w);
            }
            return Vector3<T>(x, y, z);
        }

        Matrix4 operator*(T scalar) const {
            Matrix4 result;
            for (int i = 0; i < 16; ++i) {
                result.m[i] = m[i] * scalar;
            }
            return result;
        }
    };

    using mat4f = Matrix4<float>;
    using mat4d = Matrix4<double>;
}