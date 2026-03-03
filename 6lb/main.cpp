#include <windows.h>
#include <iostream>
#include "rhombus.h"

static void display_menu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Создать ромб\n";
    std::cout << "2. Проверить принадлежность точки границе\n";
    std::cout << "3. Проверить пересечение с осью X\n";
    std::cout << "4. Проверить пересечение с осью Y\n";
    std::cout << "5. Вывести параметры ромба\n";
    std::cout << "6. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    Rhombus* rhombus = nullptr; // текущий объект
    int choice = 0;

    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, x3 = 0.0, y3 = 0.0;
    double x = 0.0, y = 0.0;

    do {
        display_menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // создаём новый ромб
                delete rhombus;
                rhombus = nullptr;

                std::cout << "Введите координаты трех вершин ромба (x1 y1 x2 y2 x3 y3): ";
                std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

                rhombus = new Rhombus(x1, y1, x2, y2, x3, y3);

                std::cout << "Ромб создан. Координаты 4-й вершины: ("
                          << rhombus->getX4() << ", " << rhombus->getY4() << ")\n";
                break;
            }

            case 2: {
                if (rhombus == nullptr) {
                    std::cout << "Сначала создайте ромб!\n";
                    break;
                }

                std::cout << "Введите координаты точки (x y): ";
                std::cin >> x >> y;

                if (rhombus->isPointOnBorder(x, y)) {
                    std::cout << "Точка принадлежит границе ромба.\n";
                } else {
                    std::cout << "Точка не принадлежит границе ромба.\n";
                }
                break;
            }

            case 3: {
                if (rhombus == nullptr) {
                    std::cout << "Сначала создайте ромб!\n";
                    break;
                }

                if (rhombus->intersectsXAxis()) {
                    std::cout << "Ромб пересекает ось X.\n";
                } else {
                    std::cout << "Ромб не пересекает ось X.\n";
                }
                break;
            }

            case 4: {
                if (rhombus == nullptr) {
                    std::cout << "Сначала создайте ромб!\n";
                    break;
                }

                if (rhombus->intersectsYAxis()) {
                    std::cout << "Ромб пересекает ось Y.\n";
                } else {
                    std::cout << "Ромб не пересекает ось Y.\n";
                }
                break;
            }

            case 5: {
                if (rhombus == nullptr) {
                    std::cout << "Сначала создайте ромб!\n";
                    break;
                }

                rhombus->printParameters();
                break;
            }

            case 6: {
                std::cout << "Выход из программы.\n";
                break;
            }

            default: {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
    } while (choice != 6);

    delete rhombus; // освобождаем память перед выходом
    return 0;
}