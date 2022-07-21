#include <iostream>
#include "matrix.h"
#include <ctime>



int main()
{
    srand(time(NULL));

    Matrix<int> mat(9, 9);
    mat.randomize(-10, 20);
    std::cout << "mat:\n" << mat << std::endl;
    std::cout << "transpose mat:\n\n";
    mat.transpose();
    std::cout << mat << std::endl;
    std::cout << "Sled mat = " << mat.trace();
    std::cout << "\n---------------------------------------------\n";

    Matrix<int> mat1(3, 3), mat2(3, 3);
    mat1.randomize(-5, 5);
    mat2.randomize(5, 15);
    std::cout << "mat1, mat2: \n";
    std::cout << mat1 << "\n" << mat2 << "\n";
    std::cout << "mat1 + mat2:\n\n";
    mat = mat1 + mat2;
    std::cout << mat;
    std::cout << "\n---------------------------------------------\n";

    Matrix<int> mat3(3, 4), mat4(4, 5);
    mat3.randomize(-5, 5);
    mat4.randomize(5, 15);
    std::cout << "mat3, mat4: \n";
    std::cout << mat3 << "\n" << mat4 << "\n\n";
    mat = mat3 * mat4;
    std::cout << "mat3 * mat4\n";
    std::cout << mat;
    std::cout << "\n---------------------------------------------\n";

    Matrix<int> mat5(3, 3);
    mat5.randomize(1, 10);
    std::cout << mat5 << "\n";
    std::cout << "determinate = " << mat5.det(mat5, 3);

    return 0;
}