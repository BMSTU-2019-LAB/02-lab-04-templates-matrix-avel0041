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

  Matrix(int a, int b) {
    row = a;
    col = b;
    M = new T*[row];
    for (int i = 0; i < row; i++) {
      M[i] = new T[col];
    }
    for (int i = 0; i < row; i++) {
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
  Matrix(const Matrix& C) {
    row = C.row;
    col = C.col;
    M = new T*[row];
    for (int i = 0; i < row; i++) {
      M[i] = new T[col];
    }
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        M[i][j] = C.M[i][j];
      }
    }
  }

  Matrix& operator=(const Matrix& R) {
    if (row > 0) {
      for (int i = 0; i < row; i++) delete[] M[i];
    }
    if (col > 0) {
      delete[] M;
    }
    row = R.row;
    col = R.col;
    M = new T*[row];
    for (int i = 0; i < row; i++) {
      M[i] = new T[col];
    }
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        M[i][j] = R.M[i][j];
      }
    }
    return *this;
  }

  Matrix& operator+(Matrix& M1) {
    if (row != M1.row || col != M1.col) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* M2 = new Matrix(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        M2->M[i][j] = M[i][j] + M1.M[i][j];
      }
    }
    return *M2;
  }

  Matrix& operator-(Matrix& M1) {
    if (row != M1.row || col != M1.col) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* M2 = new Matrix(row, col);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        M2->M[i][j] = M[i][j] - M1.M[i][j];
      }
    }
    return *M2;
  }

  Matrix& operator*(Matrix& M1) {
    if (this->col != M1.row) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* pMatrix = new Matrix(row, M1.col);
    for (int i = 0; i < pMatrix->row; i++) {
      for (int j = 0; j < pMatrix->col; j++) {
        for (int k = 0; k < col; k++) {
          pMatrix->M[i][j] += M[i][k] * M1.M[k][j];
        }
      }
    }
    return *pMatrix;
  }

  bool operator==(const Matrix<T>& op2) const
  {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (abs(M[i][j] - op2.M[i][j]) > 0.0000000000001) return false;
      }
    }
    return true;
  }
  bool operator !=(const Matrix<T>& op2) const {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (M[i][j] == op2.M[i][j]) return false;
      }
    }
    return true;
  }
  Matrix Inverse(){
    Matrix<T> A(row, 2 * row);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < row; j++) {
        A.M[i][j] = M[i][j];
      }
    }
    for (int i = 0; i < row; i++) {
      A.M[i][row + i] = 1;
    }

    for (int i = 0; i < row; i++) {
      double maxEl = abs(A.M[i][i]);
      int maxRow = i;
      for (int k = i + 1; k < row; k++) {
        if (abs(A.M[k][i]) > maxEl) {
          maxEl = A.M[k][i];
          maxRow = k;
        }
      }

      for (int k = i; k < 2 * row; k++) {
        double tmp = A.M[maxRow][k];
        A.M[maxRow][k] = A.M[i][k];
        A.M[i][k] = tmp;
      }

      for (int k = i + 1; k < row; k++) {
        double c = -A.M[k][i] / A.M[i][i];
        for (int j = i; j < 2 * row; j++) {
          if (i == j) {
            A.M[k][j] = 0;
          } else {
            A.M[k][j] += c * A.M[i][j];
          }
        }
      }
    }

    for (int i = row - 1; i >= 0; i--) {
      for (int k = row; k < 2 * row; k++) {
        A.M[i][k] /= A.M[i][i];
      }
      for (int rowMod = i - 1; rowMod >= 0; rowMod--) {
        for (int mod = row; mod < 2 * row; mod++) {
          A.M[rowMod][mod] -= A.M[i][mod] * A.M[rowMod][i];
        }
      }
    }

    Matrix<T> I(row, row);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < row; j++) {
        I.M[i][j] = A.M[i][j + row];
      }
    }
    return I;
  }

  ~Matrix() {
    if (row > 0) {
      for (int i = 0; i < row; i++)
        delete[] M[i];
    }
    if (col > 0) {
      delete[] M;
    }
  }
};

#endif // INCLUDE_MATRIX_HPP_
