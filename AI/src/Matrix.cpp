#include "../include/Matrix.h"
#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>

//DISCLAIMER
//this code is written entirely by chatgpt, I have modified it here and there, but
//it's not my code
//
//my code got lost when my laptop burned out and I was too lazy (and angry) to
//write it again. Hope you understand. I'm not a vibe programmer :>


Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0)) {}

void Matrix::randomize() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0); // weights from -1 to 1

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            data[i][j] = dis(gen);
}

void Matrix::print() const {
    for (const auto& row : data) {
        for (double val : row)
            std::cout << std::setw(8) << val << " ";
        std::cout << std::endl;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix sizes must match for addition");
   
    Matrix result(rows, cols);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            result.data[y][x] = data[y][x] + other.data[y][x];

    return result;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix sizes must match for subtraction");

    Matrix result(rows, cols);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            result.data[y][x] = data[y][x] - other.data[y][x];

    return result;
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");

    Matrix result(rows, other.cols);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < other.cols; x++)
            for (int e = 0; e < cols; e++)
                result.data[y][x] += data[y][e] * other.data[e][x];

    return result;
}

Matrix Matrix::scalar_multiply(double scalar) const {
    Matrix result(rows, cols);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            result.data[y][x] = data[y][x] * scalar;

    return result;
}

std::vector<double> Matrix::vector_multiply(const std::vector<double>& mult_vector) const {
    if (static_cast<size_t>(cols) != mult_vector.size())
        throw std::invalid_argument("Matrix cols must match vector size");

    std::vector<double> result(rows, 0);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            result[y] += data[y][x] * mult_vector[x];

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            result.data[x][y] = data[y][x];

    return result;
}
double Matrix::determinant() const {
    if (rows != cols)
        throw std::invalid_argument("Determinant is only defined for square matrices");

    if (rows == 1)
        return data[0][0];

    if (rows == 2)
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];

    double det = 0;
    for (int x = 0; x < cols; x++) {
        Matrix subMatrix(rows - 1, cols - 1);

        for (int i = 1; i < rows; i++) {
            int subCol = 0;
            for (int j = 0; j < cols; j++) {
                if (j == x) continue;
                subMatrix.data[i - 1][subCol] = data[i][j];
                subCol++;
            }
        }

        double sign = (x % 2 == 0) ? 1 : -1;
        det += sign * data[0][x] * subMatrix.determinant();
    }

    return det;
}

