// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

template <class T>
class Matrix {
  int n;
  int m;
  T **M;

 public:
  Matrix() {
    n = 0;
    m = 0;
    M = nullptr;
  }

  Matrix(int a, int b) {
    n = a;
    m = b;
    M = (T**)new T*[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = 0;
      }
    }
  }
  T* operator[](int index) {
    return M[index];
  }

  int get_rows() {
    return n;
  }

  int get_columns() {
    return m;
  }
  Matrix(const Matrix& C) {
    n = C.n;
    m = C.m;
    M = (T**)new T*[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = C.M[i][j];
      }
    }
  }

  Matrix& operator=(const Matrix& R) {
    if (n > 0) {
      for (int i = 0; i < n; i++) delete[] M[i];
    }
    if (m > 0) {
      delete[] M;
    }
    n = R.n;
    m = R.m;
    M = (T**)new T*[n];
    for (int i = 0; i < n; i++) {
      M[i] = (T*)new T[m];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M[i][j] = R.M[i][j];
      }
    }
    return *this;
  }

  Matrix& operator+(Matrix& M1) {
    if (n != M1.n || m != M1.m) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* M2 = new Matrix(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M2->M[i][j] = M[i][j] + M1.M[i][j];
      };
    };
    return *M2;
  }

  Matrix& operator-(Matrix& M1) {
    if (n != M1.n || m != M1.m) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* M2 = new Matrix(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        M2->M[i][j] = M[i][j] - M1.M[i][j];
      }
    }
    return *M2;
  }

  Matrix& operator*(Matrix& M1) {
    if (this->m != M1.n) {
      Matrix* Zero = new Matrix();
      return *Zero;
    }
    Matrix* pMatrix = new Matrix(n, M1.m);
    for (int i = 0; i < pMatrix->n; i++) {
      for (int j = 0; j < pMatrix->m; j++) {
        for (int k = 0; k < m; k++) {
          pMatrix->M[i][j] += M[i][k] * M1.M[k][j];
        }
      }
    }
    return *pMatrix;
  }

  bool operator==(const Matrix<T>& op2) const
  {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (abs(M[i][j] - op2.M[i][j]) > 0.0000000000001) return false;
      }
    }
    return true;
  }
  bool operator !=(const Matrix<T>& op2) const {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (M[i][j] == op2.M[i][j]) return false;
      }
    }
    return true;
  }
  Matrix Inverse(){
    Matrix<T> A(n, 2 * n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        A.M[i][j] = M[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      A.M[i][n + i] = 1;
    }

    for (int i = 0; i < n; i++) {
      double maxEl = abs(A.M[i][i]);
      int maxRow = i;
      for (int k = i + 1; k < n; k++) {
        if (abs(A.M[k][i]) > maxEl) {
          maxEl = A.M[k][i];
          maxRow = k;
        }
      }

      for (int k = i; k < 2 * n; k++) {
        double tmp = A.M[maxRow][k];
        A.M[maxRow][k] = A.M[i][k];
        A.M[i][k] = tmp;
      }

      for (int k = i + 1; k < n; k++) {
        double c = -A.M[k][i] / A.M[i][i];
        for (int j = i; j < 2 * n; j++) {
          if (i == j) {
            A.M[k][j] = 0;
          } else {
            A.M[k][j] += c * A.M[i][j];
          }
        }
      }
    }

    for (int i = n - 1; i >= 0; i--) {
      for (int k = n; k < 2 * n; k++) {
        A.M[i][k] /= A.M[i][i];
      }
      for (int rowMod = i - 1; rowMod >= 0; rowMod--) {
        for (int mod = n; mod < 2 * n; mod++) {
          A.M[rowMod][mod] -= A.M[i][mod] * A.M[rowMod][i];
        }
      }
    }

    Matrix<T> I(n, n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        I.M[i][j] = A.M[i][j + n];
      }
    }
    return I;
  }

  ~Matrix() {
    if (n > 0) {
      for (int i = 0; i < n; i++)
        delete[] M[i];
    }
    if (m > 0) {
      delete[] M;
    }
  }
};

#endif // INCLUDE_MATRIX_HPP_
