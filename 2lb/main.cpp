#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(nullptr));

    const int N = 6;
    int A[N][N], B[N][N];
    int b[N] = {0};

    // B — от -2 до 5, с повышенным шансом нуля
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() % 9 - 3;  // -3..5
            int r = rand() % 10;
            if (r < 3) B[i][j] = 0;    // 30% вероятность нуля
            else B[i][j] = rand() % 8 - 2; // -2..5
        }
    }

    // вывод матриц
    cout << "Матрица A:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(4) << A[i][j];
        cout << endl;
    }

    cout << "\nМатрица B:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << setw(4) << B[i][j];
        cout << endl;
    }

    // подсчёт bi
    for (int i = 0; i < N; ++i) {
        int posA = 0, posB = 0;
        int negA = 0, nonNegB = 0;

        for (int j = 0; j < N; ++j) {
            if (A[i][j] > 0) posA++;
            if (B[i][j] > 0) posB++;
            if (A[i][j] < 0) negA++;
            if (B[i][j] >= 0) nonNegB++;
        }

        bool cond1 = (posA + posB) <= 3;
        bool cond2 = (negA == nonNegB);

        // логика "ИЛИ"
        if (cond1 || cond2)
            b[i] = 1;
        else
            b[i] = 0;
    }

    // вывод последовательности
    cout << "\nПоследовательность b:\n";
    for (int i = 0; i < N; ++i)
        cout << "b" << (i + 1) << " = " << b[i] << endl;

    return 0;
}
