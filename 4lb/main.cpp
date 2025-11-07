#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// функция для чтения матрицы
double** readMatrix(int rows, int cols) { // принимаем размеры матрицы и возвр укзтл на укзтл
    double** matrix = new double*[rows]; // каждый элемент matrix[i] будет указывать на строку 
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols]; // выделяем память под колс
        for (int j = 0; j < cols; ++j) {
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        } // запрашиваем каждый элемент по и, жи и сохр в матрицу
    }
    return matrix;
}

// функция для вычисления среднего арифметического
double calculateAverage(double** matrix, int rows, int cols) { 
    double sum = 0.0; // переменная для суммы всех элементов
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += matrix[i][j];
        } // пробегаемся по матрице и суммируем все знач
    }
    return sum / (rows * cols); // среднее арифм
}

// функция для поиска элемента наименее отличающегося от среднего
void findClosestToAverage(double** matrix, int rows, int cols, double average, // результаты в перем по ссылке
                         double& closestValue, int& closestRow, int& closestCol) {
    double minDiff = numeric_limits<double>::max(); // возвр макс возм число в дабл
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double diff = fabs(matrix[i][j] - average); // модуль разности тек элем и ср
            if (diff < minDiff) {
                minDiff = diff;
                closestValue = matrix[i][j];
                closestRow = i;
                closestCol = j;
            }
        }
    }
}

// функция для вывода матрицы
void printMatrix(double** matrix, int rows, int cols) {
    cout << "\nМатрица:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << setw(8) << fixed << setprecision(2) << matrix[i][j];
        }
        cout << endl;
    }
}

// функция для освобождения памяти
void freeMemory(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
} // освобожд все строки и потом массив указателей 

int main() {
    setlocale(LC_ALL, "Russian");
    
    int rows, cols;
    
    // ввод размеров матрицы
    cout << "Введите количество строк матрицы: ";
    cin >> rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> cols;
    
    if (rows <= 0 || cols <= 0) {
        cerr << "Ошибка: размеры матрицы должны быть положительными числами." << endl;
        return 1;
    }
    
    // чтение матрицы
    double** matrix = readMatrix(rows, cols);
    
    // вычисление среднего арифметического
    double average = calculateAverage(matrix, rows, cols);
    cout << "\nСреднее арифметическое всех элементов: " << fixed << setprecision(2) << average << endl;
    
    // поиск элемента, наименее отличающегося от среднего
    double closestValue;
    int closestRow, closestCol;
    findClosestToAverage(matrix, rows, cols, average, closestValue, closestRow, closestCol);
    
    // вывод результатов
    printMatrix(matrix, rows, cols);
    cout << "\nЭлемент, наименее отличающийся от среднего:\n";
    cout << "Значение: " << closestValue << endl;
    cout << "Позиция: [" << closestRow << "][" << closestCol << "]" << endl;
    cout << "Разница со средним: " << fabs(closestValue - average) << endl;
    
    // освобождение памяти
    freeMemory(matrix, rows);
    
    return 0;
}