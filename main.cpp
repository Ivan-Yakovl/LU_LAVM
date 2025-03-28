#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


void LU(vector<vector<double>> A, vector<vector<double>>& L,
    vector<vector<double>>& U, int n)
{
    U = A;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            L[j][i] = U[j][i] / U[i][i];

    for (int k = 1; k < n; k++)
    {
        for (int i = k - 1; i < n; i++)
            for (int j = i; j < n; j++)
                L[j][i] = U[j][i] / U[i][i];

        for (int i = k; i < n; i++)
            for (int j = k - 1; j < n; j++)
                U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
    }
}


void matrixMultiply(vector<vector<double>> A, vector<vector<double>> B,
    vector<vector<double>>& R, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                R[i][j] += A[i][k] * B[k][j];
}


void solveLy(vector<vector<double>> L, vector<double> b, vector<double>& y, int n)
{
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
        y[i] /= L[i][i];
    }
}


void solveUx(vector<vector<double>> U, vector<double> y, vector<double>& x, int n)
{
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}


void showMatrix(vector<vector<double>> A, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << A[i][j] << " ";
        }
        cout << endl;
    }
}

void showVector(vector<double> v, int n)
{
    for (int i = 0; i < n; i++) {
        cout << "[" << i << "] = " << v[i] << endl;
    }
}

int main()
{
    int n;
    cout << "Enter matrix size n: ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n)),
        L(n, vector<double>(n, 0)),
        U(n, vector<double>(n, 0)),
        R(n, vector<double>(n, 0));
    vector<double> b(n), y(n), x(n);

    cout << "\nEnter matrix A elements:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> A[i][j];
        }
    }

    cout << "\nEnter vector b elements:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }

  
    LU(A, L, U, n);

    cout << "\nOriginal matrix A:" << endl;
    showMatrix(A, n);

    cout << "\nLower triangular matrix L:" << endl;
    showMatrix(L, n);

    cout << "\nUpper triangular matrix U:" << endl;
    showMatrix(U, n);

 
    matrixMultiply(L, U, R, n);
    cout << "\nVerification: L*U =" << endl;
    showMatrix(R, n);

  
    cout << "\nSolving the system Ax = b:" << endl;

   
    solveLy(L, b, y, n);
    cout << "\nIntermediate vector y (from Ly = b):" << endl;
    showVector(y, n);

   
    solveUx(U, y, x, n);
    cout << "\nSolution vector x (from Ux = y):" << endl;
    showVector(x, n);

    return 0;
}