// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

template <class T>
class Matrix {
  int row;
  int col;
  T **M;

 public:
  Matrix() {
    row = 0;
    col = 0;
    M = nullptr;
  }

  Matrix(int r, int c) {
    row = r;
    col = c;
    M = new T*[row];
    for (int i = 0; i < row; i++) {
      M[i] = new T[col];
      for (int j = 0; j < col; j++) {
        M[i][j] = 0;
      }
    }
  }

  T* operator[](int index) {
    return M[index];
  }

  int get_rows() {
    return row;
  }

  int get_columns() {
    return col;
  }

  Matrix(const Matrix& Mat) {
    row = Mat.row;
    col = Mat.col;
    M = new T*[row];
    for (int i = 0; i < row; i++) {
      M[i] = new T[col];
      for (int j = 0; j < col; j++) {
        M[i][j] = Mat.M[i][j];
      }
    }
  }

  Matrix& operator=(const Matrix& Mat) {
    row = Mat.row;
    col = Mat.col;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        M[i][j] = Mat.M[i][j];
      }
    }
    return *this;
  }

  Matrix operator+(Matrix& Mat) {
    if (row != Mat.row || col != Mat.col) {
      Matrix<T> matrix;
      return matrix;
    }
    Matrix<T> MaM(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        MaM.M[i][j] = M[i][j] + Mat.M[i][j];
      }
    }
    return MaM;
  }

  Matrix operator-(Matrix& Mat) {
    if (row != Mat.row || col != Mat.col) {
      Matrix<T> matrix;
      return matrix;
    }
    Matrix<T> MwM(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        MwM.M[i][j] = M[i][j] - Mat.M[i][j];
      }
    }
    return MwM;
  }

  Matrix operator*(Matrix& Mat) {
    if (this->col != Mat.row) {
      Matrix<T> matrix;
      return matrix;
    }
    Matrix<T>MM(row, Mat.col);
    for (int i = 0; i < MM.row; i++) {
      for (int j = 0; j < MM.col; j++) {
        for (int k = 0; k < col; k++) {
          MM.M[i][j] += M[i][k] * Mat.M[k][j];
        }
      }
    }
    return MM;
  }

  bool operator==(const Matrix<T>& Mat) const
  {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (abs(M[i][j] - Mat.M[i][j]) > 0.0000000000001) return false;
      }
    }
    return true;
  }
  bool operator !=(const Matrix<T>& Mat) const {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (M[i][j] == Mat.M[i][j]) return false;
      }
    }
    return true;
  }
  Matrix Inverse(){
    if (row != col){
      std::cout << "Error!";
      return *this;
    }
    Matrix<T> Mat(row, 2 * row);
    Mat = *this;
    for (int i = 0; i < row; i++) {
      Mat.M[i][row + i] = 1;
    }
    for (int i = 0; i < row; i++) {
      for (int j = i + 1; j < row; j++) {
        double t = Mat.M[j][i] / Mat.M[i][i];
        for (int k = i; k < 2 * row; k++) {
          if (i == k) {
            Mat.M[j][k] = 0;
          } else {
            Mat.M[j][k] -= t * Mat.M[i][k];
          }
        }
      }
    }
    for (int i = row - 1; i >= 0; i--) {
      for (int j = row; j < 2 * row; j++) {
        Mat.M[i][j] /= Mat.M[i][i];
      }
      for (int j = i - 1; j >= 0; j--) {
        for (int k = row; k < 2 * row; k++) {
          Mat.M[j][k] -= Mat.M[i][k] * Mat.M[j][i];
        }
      }
    }
    Matrix<T> Inv(row, row);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < row; j++) {
        Inv.M[i][j] = Mat.M[i][j + row];
      }
    }
    return Inv;
  }

  ~Matrix() {
    for (int i = 0; i < row; i++) delete[] M[i];
    delete[] M;
  }
};

#endif // INCLUDE_MATRIX_HPP_
