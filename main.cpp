#include <iostream>
#include <vector>

using namespace std;

// Функция для выполнения LU-разложения
void LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    U = A;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            L[j][i] = U[j][i] / U[i][i];
        }

        for (int k = i + 1; k < n; k++) {
            for (int j = i; j < n; j++) {
                U[k][j] = U[k][j] - L[k][i] * U[i][j];
            }
        }
    }
}

// Функция для решения системы Ly = b
void solveLy(const vector<vector<double>>& L, vector<double>& y, const vector<double>& b, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
}

// Функция для решения системы Ux = y
void solveUx(const vector<vector<double>>& U, vector<double>& x, const vector<double>& y, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}


void show(const vector<vector<double>>& A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\t" << A[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Введите размер матрицы n: ";
    cin >> n;

   
    vector<vector<double>> A(n, vector<double>(n)), L(n, vector<double>(n)), U(n, vector<double>(n));
    vector<double> b(n), y(n), x(n);

    cout << "Введите элементы матрицы A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> A[i][j];
        }
    }

    
    cout << "Введите элементы вектора b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    // LU-разложение
    LU(A, L, U, n);

    cout << "Матрица A:" << endl;
    show(A, n);

    cout << "Матрица L:" << endl;
    show(L, n);

    cout << "Матрица U:" << endl;
    show(U, n);

    // Решение системы Ly = b
    solveLy(L, y, b, n);

    // Решение системы Ux = y
    solveUx(U, x, y, n);

    cout << "Решение вектора x:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}