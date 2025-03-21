#include <iostream>
#include <vector>

using namespace std;

// ������� ��� ���������� LU-����������
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

// ������� ��� ������� ������� Ly = b
void solveLy(const vector<vector<double>>& L, vector<double>& y, const vector<double>& b, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
}

// ������� ��� ������� ������� Ux = y
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
    cout << "������� ������ ������� n: ";
    cin >> n;

   
    vector<vector<double>> A(n, vector<double>(n)), L(n, vector<double>(n)), U(n, vector<double>(n));
    vector<double> b(n), y(n), x(n);

    cout << "������� �������� ������� A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> A[i][j];
        }
    }

    
    cout << "������� �������� ������� b:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

    // LU-����������
    LU(A, L, U, n);

    cout << "������� A:" << endl;
    show(A, n);

    cout << "������� L:" << endl;
    show(L, n);

    cout << "������� U:" << endl;
    show(U, n);

    // ������� ������� Ly = b
    solveLy(L, y, b, n);

    // ������� ������� Ux = y
    solveUx(U, x, y, n);

    cout << "������� ������� x:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return 0;
}