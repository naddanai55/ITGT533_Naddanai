#include <iostream>
#include "Vector3.hpp"
#include "Matrix.hpp"
#include <iomanip>

using namespace std;

template<typename T>
void print_matrix(const NP::Matrix4<T>& mat) 
{
    cout << fixed << setprecision(2);
    for (int row = 0; row < 4; row++) 
    {
        cout << "[ ";
        for (int col = 0; col < 4; col++) 
        {
            cout << setw(6) << mat.m[col * 4 + row] << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main()
{
    using NP::vec3f;
    using NP::mat4f;

    vec3f my_point(1.0f, 1.0f, 1.0f);
    mat4f translation_matrix = mat4f::Translate(vec3f(10.0f, 20.0f, 30.0f));

    cout << "Original point: " << my_point << endl;
    cout << endl;
    cout << "Translation Matrix:" << endl;
    print_matrix(translation_matrix);

    vec3f transformed_point = translation_matrix * my_point;
    cout << "Transformed point with translation_matrix " << transformed_point << endl;
    cout << endl;

    cout << "scale matrix with 2" << endl;
    mat4f scale_matrix(2.0f);
    mat4f model_matrix = translation_matrix * scale_matrix;
    print_matrix(model_matrix);

    cout << "--- Transpose a Matrix ---" << endl;
    mat4f original = mat4f::Translate(vec3f(1.0f, 2.0f, 3.0f));
    cout << "Original Matrix:" << endl;
    print_matrix(original);

    mat4f transposed = original.Transposed();
    cout << "Transposed Matrix:" << endl;
    print_matrix(transposed);

    cout << "--- Inverse a Matrix ---" << endl;
    cout << "Original Model Matrix:" << endl;
    print_matrix(model_matrix);

    mat4f inverse_matrix = model_matrix.Inversed();
    cout << "Inverse Matrix:" << endl;
    print_matrix(inverse_matrix);

    mat4f identity = model_matrix * inverse_matrix;
    cout << "Result of M * M_inverse :" << endl;
    print_matrix(identity);

    return 0;
}