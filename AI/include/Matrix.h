#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
private:
    
    int rows, cols;

public:
    std::vector<std::vector<double>> data; //this should be private but I don't fucking care
    Matrix();
    Matrix(int rows, int cols);
    void randomize();
    void print() const;

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    Matrix scalar_multiply(double scalar) const;
    std::vector<double> vector_multiply(const std::vector<double>& mult_vector) const;
    Matrix transpose() const;

    double determinant() const;
    Matrix inverse() const;
    Matrix multiply_cols_vector(const std::vector<double>& mult_vector) const;
};

#endif // MATRIX_H
