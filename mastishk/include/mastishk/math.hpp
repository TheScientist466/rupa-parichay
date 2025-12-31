#pragma once

#include <cmath>
#include <cassert>
#include <cstddef>
#include <stdint.h>

template <class T> struct Matrix {
  size_t rows;
  size_t cols;
  T *data;
};

/// @brief Multiplies 2 matrices
/// @tparam T
/// @param left Matrix on the left side of the multiply operation
/// @param right Matrix on the right side of the multiply operation
/// @return Product of matrices
/// @note returned matrix must be freed from memory after used.
template <class T> Matrix<T> multiplyMatrix(Matrix<T> left, Matrix<T> right) {
  Matrix<T> out = {.rows = left.rows, .cols = right.cols};
  out.data = new float[out.rows * out.cols];

  for (size_t y = 0; y < out.cols; y++) {
    for (size_t x = 0; x < out.rows; x++) {
      out.data[y * out.rows + x] = 0;
      for (size_t i = 0; i < left.cols; i++) {
        out.data[y * out.rows + x] +=
            left.data[y * left.cols + i] * right.data[i * right.cols + x];
      }
    }
  }
  return out;
}

/// @brief Addition of two matrix
/// @tparam T
/// @param left Left side matrix
/// @param right right side matrix
/// @return returned matrix must be freed from memory after used.
template <class T> Matrix<T> addMatrix(Matrix<T> left, Matrix<T> right) {
  assert(("Dimentions of matrices must be equal",
          (left.rows == right.rows && left.cols == right.cols)));
  Matrix<T> out = {.rows = left.rows, .cols = left.cols};
  out.data = new float[out.rows * out.cols];
  for (size_t i = 0; i < out.rows * out.cols; i++) {
    out.data[i] = left.data[i] + right.data[i];
  }
  return out;
}

// activation function
template <class T> Matrix<T> activationFunction(Matrix<T> matrix) {
  Matrix<T> out = {.rows = matrix.rows, .cols = matrix.cols};
  out.data = new float[out.rows];
  for (size_t i = 0; i < out.rows; i++) {
    out.data[i] = 1 / (1 + exp(-matrix.data[i]));
  }
  return out;
}
