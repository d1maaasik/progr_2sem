#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <clocale>
#include <windows.h>

double** readMatrix(int rows, int cols) { // функция для ввода матрицы
    double** matrix = new double*[rows]; // выделяем память под массив указателей на строки

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols]; // выделяем память под столбцы текущей строки

        for (int j = 0; j < cols; ++j) {
            std::cout << "Введите элемент [" << i << "][" << j << "]: "; // вывод запроса на ввод элемента
            std::cin >> matrix[i][j]; // ввод элемента матрицы
        }
    }
    return matrix; // возвращаем указатель на созданную матрицу
}

double calculateAverage(double** matrix, int rows, int cols) { // функция вычисления среднего арифметического
    double sum = 0.0; // переменная для накопления суммы элементов

    for (int i = 0; i < rows; ++i) { // перебор строк
        for (int j = 0; j < cols; ++j) { // перебор столбцов
            sum += matrix[i][j]; // прибавляем текущий элемент к сумме
        }
    }

    return sum / (rows * cols); // возвращаем среднее арифметическое
}

void findClosestToAverage(double** matrix, int rows, int cols, double average,
                          double& closestValue, int& closestRow, int& closestCol) { // функция поиска элемента

    double minDiff = std::numeric_limits<double>::max(); // задаем максимально возможную разность

    for (int i = 0; i < rows; ++i) { // перебор строк
        for (int j = 0; j < cols; ++j) { // перебор столбцов

            double diff = std::fabs(matrix[i][j] - average); // вычисляем модуль разности

            if (diff < minDiff) { // если текущая разность меньше минимальной
                minDiff = diff; // обновляем минимальную разность
                closestValue = matrix[i][j]; // сохраняем значение элемента
                closestRow = i; // сохраняем индекс строки
                closestCol = j; // сохраняем индекс столбца
            }
        }
    }
}

void printMatrix(double** matrix, int rows, int cols) { // функция вывода матрицы
    std::cout << "\nМатрица:\n"; // вывод заголовка

    for (int i = 0; i < rows; ++i) { // перебор строк
        for (int j = 0; j < cols; ++j) { // перебор столбцов
            std::cout << std::setw(8) << std::fixed << std::setprecision(2)
                      << matrix[i][j]; // форматированный вывод элемента
        }
        std::cout << std::endl; // переход на новую строку
    }
}

void freeMemory(double** matrix, int rows) { // функция освобождения памяти
    for (int i = 0; i < rows; ++i) { // перебор строк
        delete[] matrix[i]; // освобождаем память строки
    }
    delete[] matrix; // освобождаем массив указателей
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    int rows, cols; // переменные для размеров матрицы

    std::cout << "Введите количество строк матрицы: "; // запрос количества строк
    std::cin >> rows; // ввод количества строк

    std::cout << "Введите количество столбцов матрицы: "; // запрос количества столбцов
    std::cin >> cols; // ввод количества столбцов

    if (rows <= 0 || cols <= 0) { // проверка корректности размеров
        std::cerr << "Ошибка: размеры матрицы должны быть положительными числами."
                  << std::endl; // вывод сообщения об ошибке
        return 1; // завершение программы с ошибкой
    }

    double** matrix = readMatrix(rows, cols); // вызов функции ввода матрицы

    double average = calculateAverage(matrix, rows, cols); // вычисление среднего значения

    std::cout << "\nСреднее арифметическое всех элементов: "
              << std::fixed << std::setprecision(2)
              << average << std::endl; // вывод среднего значения

    double closestValue; // переменная для хранения найденного значения
    int closestRow, closestCol; // переменные для хранения индексов

    findClosestToAverage(matrix, rows, cols, average,
                         closestValue, closestRow, closestCol); // поиск нужного элемента

    printMatrix(matrix, rows, cols); // вывод матрицы

    std::cout << "\nЭлемент, наименее отличающийся от среднего:\n"; // вывод заголовка результата
    std::cout << "Значение: " << closestValue << std::endl; // вывод значения
    std::cout << "Позиция: [" << closestRow << "][" << closestCol << "]" << std::endl; // вывод позиции
    std::cout << "Разница со средним: "
              << std::fabs(closestValue - average) << std::endl; // вывод модуля разности

    freeMemory(matrix, rows); // освобождение динамической памяти

    return 0; // успешное завершение программы
}