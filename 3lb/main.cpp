// Вариант 9
// дан массив X1..X15.
// исключить из него первый и последний отрицательные элементы.

#include <iostream>
#include <vector>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    // Блок 1  ВВОД ДАННЫХ
    const int SIZE = 15;               // размер массива по условию
    std::vector<int> arr(SIZE);        // динамический массив из 15 элементов
    std::cout << "Введите 15 элементов массива:\n";
    for (int i = 0; i < SIZE; i++) {
        std::cin >> *(arr.data() + i); // доступ через арифметику указателя
    }
    // Вывод исходного массива
    std::cout << "\nИсходный массив:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << *(arr.data() + i) << " ";
    }
    std::cout << std::endl;
    // Блок 2  ОБРАБОТКА ДАННЫХ
    int firstNeg = -1;  // индекс первого отрицательного элемента
    int lastNeg = -1;   // индекс последнего отрицательного элемента
    // Проходим по массиву и ищем отрицательные элементы
    for (int i = 0; i < arr.size(); i++) {

        if (*(arr.data() + i) < 0) {  // если элемент отрицательный

            // если первый отрицательный ещё не найден
            if (firstNeg == -1) {
                firstNeg = i;
            }

            // каждый раз обновляем lastNeg
            lastNeg = i;
        }
    }
    // Удаляем найденные элементы
    if (firstNeg != -1) {  // если отрицательные вообще есть

        if (firstNeg != lastNeg) {
            // если отрицательных больше одного

            // сначала удаляем последний (чтобы индексы не сдвинулись)
            arr.erase(arr.begin() + lastNeg);

            // затем удаляем первый
            arr.erase(arr.begin() + firstNeg);

        } else {
            // если отрицательный элемент только один
            arr.erase(arr.begin() + firstNeg);
        }
    }
    // Блок 3 ВЫВОД РЕЗУЛЬТАТА
    std::cout << "\nМассив после удаления первого и последнего отрицательных элементов:\n";

    for (int i = 0; i < arr.size(); i++) {
        std::cout << *(arr.data() + i) << " ";
    }

    std::cout << std::endl;

    return 0;
}