#pragma once
#include <ostream>
#include <cassert>
#include <cmath>


template<typename T>
class Matrix
{
public:
    Matrix();
    Matrix(size_t row, size_t col);
    Matrix(const Matrix<T>& mat);
    Matrix(Matrix<T>&& mat);
    ~Matrix();

    // заполнение массива
    Matrix& randomize(int start, int end);

    // след
    T trace();

    // транспонирование
    Matrix& transpose();

    // определитель
    T det(const Matrix<T> mat, int size);
    // получение матрицы без строки и столбца
    void matrixWithoutRowAndCol(Matrix<T>& matrix, int size, int row, int col, Matrix<T>& newMatrix);

    Matrix& operator=(const Matrix<T>& mat);

    T& operator()(size_t i, size_t j);

    T operator()(size_t i, size_t j)const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& mat);

    template<typename U>
    friend Matrix<U> operator+(const Matrix<U>& mat1, const Matrix<U>& mat2);
    
    template<typename U>
    friend Matrix<U> operator*(const Matrix<U>& mat1, const Matrix<U>& mat2);

private:
    size_t row_;
    size_t col_;
    T* arr_;

    size_t index2D(unsigned int i, unsigned int j) const {return i * this->col_ + j; }
};

template<typename T>
Matrix<T>::Matrix(): row_{0}, col_{0}, arr_{nullptr}
{};

template<typename T>
Matrix<T>::Matrix(size_t row, size_t col): row_{row}, col_{col}
{
    this->arr_ = new T[row * col]{T()};
};

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat): row_{0}, col_{0}, arr_{nullptr}
{
    this->arr_ = new T[mat.row_ * mat.col_];

    for(size_t i{0}; i < mat.row_ * mat.col_; ++i)
        this->arr_[i] = mat.arr_[i];

    this->row_ = mat.row_;
    this->col_ = mat.col_;
};

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& mat): row_{mat.row_}, col_{mat.col_}
{
    this->arr_ = mat.arr_;
    this->row_ = mat.row_;
    this->col_ = mat.col_;
    
    mat.arr_ = nullptr;
    mat.row_ = 0;
    mat.col_ = 0;
};

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] this->arr_;
}

template<typename T>
T& Matrix<T>::operator()(size_t i, size_t j)
{
    return *(this->arr_ + index2D(i, j));
}

template<typename T>
T Matrix<T>::operator()(size_t i, size_t j)const
{
    return *(this->arr_ + index2D(i, j));
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Matrix<U>& mat)
{
    for(unsigned int i{0}; i < mat.row_; ++i)
    {
        for(unsigned int j{0}; j < mat.col_; ++j)
        {
            out << mat(i, j) << "\t";
        }
        out << std::endl;
    }
    return out;
}

template<typename T>
Matrix<T>& Matrix<T>::randomize(int start, int end)
{
    int res = end - start;
    for(size_t i{0}; i < this->row_ * this->col_; ++i)
    {
        this->arr_[i] = (rand() % res) + start;
    }

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat)
{
    if(this == &mat)
        return *this;
    
    if(this->row_ * this->col_ != mat.row_ * mat.col_)
    {
        delete[] this->arr_;
        this->arr_ = new T[mat.row_ * mat.col_];
    }

    for(size_t i{0}; i < mat.row_ * mat.col_; ++i)
        this->arr_[i] = mat.arr_[i];
    
    this->row_ = mat.row_;
    this->col_ = mat.col_;

    return *this;
}

template<typename U>
Matrix<U> operator+(const Matrix<U>& mat1, const Matrix<U>& mat2)
{
    assert
    (
        (mat1.row_ == mat2.row_) && \
        (mat1.col_ == mat2.col_) && \
        "index out of range!" \
    );

    Matrix<U> mat(mat1.row_, mat1.col_);
    for(size_t i{0}; i < mat.row_; ++i)
    {
        for(size_t j{0}; j < mat.col_; ++j)
        {
            mat(i, j) = mat1(i, j) + mat2(i, j);
        }
    }

    return mat;
}

template<typename U>
Matrix<U> operator*(const Matrix<U>& mat1, const Matrix<U>& mat2)
{
    Matrix<U> mat(mat1.row_, mat2.col_);
    for(unsigned int m{0}; m < mat1.row_; ++m)
    {
        for(unsigned int k{0}; k < mat2.col_; ++k)
        {
            for(unsigned int n{0}; n < mat1.col_; ++n)
            {
                mat(m, k) += mat1(m, n) * mat2(n, k);
            }
        }
    }

    return mat;
}

template<typename T>
T Matrix<T>::trace()
{
    assert((this->row_ == this->col_) && "The matrix is not square!");
    T res{0};
    for(unsigned int i{0}; i < this->row_; ++i)
        res += this->arr_[index2D(i, i)];
    return res;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()
{
    for(unsigned int i{0}; i < this->row_; ++i)
    {
        for(unsigned int j{i+1}; j < this->col_; ++j)
        {
            if(i != j)
                std::swap(this->arr_[index2D(i, j)], this->arr_[index2D(j, i)]);
        }
    }
    return *this;
}


template<typename T>
void Matrix<T>::matrixWithoutRowAndCol(Matrix<T>& matrix, int size, int row, int col, Matrix<T>& newMatrix)
{
    int offsetRow = 0; 
    int offsetCol = 0; 
    for(int i = 0; i < size-1; i++)
    {
        if(i == row)
        {
            offsetRow = 1; 
        }
    
        offsetCol = 0;
        for(int j = 0; j < size-1; j++) 
        {
            if(j == col)
            {
                offsetCol = 1; 
            }
            newMatrix(i,j) = matrix(i + offsetRow, j + offsetCol);
        }
    }  
}

template<typename T>
T Matrix<T>::det(Matrix<T> mat, int size)
{
    assert(this->row_ == this->col_ && "The matrix must to be squre!");

    if (mat.row_  == 1)
        return mat(0, 0);

    if(mat.row_ == 2)
    {
        return mat(0, 0) * mat(1, 1) - mat(1, 0) * mat(0, 1);
    }

    Matrix<T> matrix(size - 1, size- 1);
    int res = 0;
    int deg = 1;
    for(int i = 0; i < size; ++i)
    {
        matrixWithoutRowAndCol(mat, size, 0, i, matrix);
        res += deg * this->arr_[index2D(0, i)] * det(matrix, size-1);
        deg = -deg;
    }

    return res;
}
