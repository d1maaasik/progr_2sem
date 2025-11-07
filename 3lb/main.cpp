// 10 вариант по списку
#include <iostream>
#include <vector>


int main() {
    // блок 1: чтение данных
    const int SIZE = 15;
    std::vector<int> arr(SIZE);
    
    std::cout << "Введите 15 элементов массива (через пробел или Enter):\n";
    for (int i = 0; i < SIZE; i++) {
        std::cin >> *(arr.data() + i); // через арифметику указателя
    }
    
    // вывод исходного массива
    std::cout << "\nИсходный массив:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << *(arr.data() + i) << " ";
    }
    std::cout << std::endl;
    
    // блок 2: обработка данных
    int negativeCount = 0; // отрц числа счетчик
    std::vector<int> positionsToRemove; // индексы элементов для удаления
    
    // поиск 5-го и 7-го отрицательных элементов
    for (int i = 0; i < arr.size(); i++) {
        if (*(arr.data() + i) < 0) {
            negativeCount++;
            if (negativeCount == 5 || negativeCount == 7) {
                positionsToRemove.push_back(i);
            }
        }
    }
    
    // удаление элементов (с конца чтобы индексы не сдвигались)
    for (int i = positionsToRemove.size() - 1; i >= 0; i--) {
        arr.erase(arr.begin() + positionsToRemove[i]);
    }
    
    // блок 3: вывод результатов
    std::cout << "\nМассив после удаления 5-го и 7-го отрицательных элементов:\n";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << *(arr.data() + i) << " ";
    }
    std::cout << std::endl;
    
    return 0;
}