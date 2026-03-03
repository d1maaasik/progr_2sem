#include <iostream>
#include <memory>
#include "transformable_rhombus.h"
#include <windows.h>

static void display_menu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Создать ромб\n";
    std::cout << "2. Проверить принадлежность точки границе\n";
    std::cout << "3. Проверить пересечение с осью X\n";
    std::cout << "4. Проверить пересечение с осью Y\n";
    std::cout << "5. Вывести параметры ромба\n";
    std::cout << "6. Сдвиг на (dx, dy)\n";
    std::cout << "7. Перенос центра в (cx, cy)\n";
    std::cout << "8. Поворот вокруг центра (угол в градусах)\n";
    std::cout << "9. Сброс в исходное положение\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::unique_ptr<TransformableRhombus> rhombus;

    int choice = -1;
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
    double x = 0, y = 0;
    double dx = 0, dy = 0;
    double cx = 0, cy = 0;
    double angle = 0;

    while (choice != 0) {
        display_menu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите координаты трех вершин (x1 y1 x2 y2 x3 y3): ";
                std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                rhombus = std::make_unique<TransformableRhombus>(x1, y1, x2, y2, x3, y3);
                std::cout << "Ромб создан. 4-я вершина: ("
                          << rhombus->getX4() << ", " << rhombus->getY4() << ")\n";
                break;

            case 2:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << "Введите координаты точки (x y): ";
                std::cin >> x >> y;
                std::cout << (rhombus->isPointOnBorder(x, y) ? "Точка на границе.\n" : "Точка не на границе.\n");
                break;

            case 3:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << (rhombus->intersectsXAxis() ? "Ромб пересекает ось X.\n" : "Ромб не пересекает ось X.\n");
                break;

            case 4:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << (rhombus->intersectsYAxis() ? "Ромб пересекает ось Y.\n" : "Ромб не пересекает ось Y.\n");
                break;

            case 5:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                rhombus->printParameters();
                break;

            case 6:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << "Введите dx dy: ";
                std::cin >> dx >> dy;
                rhombus->translateBy(dx, dy);
                std::cout << "Готово.\n";
                break;

            case 7:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << "Введите cx cy: ";
                std::cin >> cx >> cy;
                rhombus->moveCenterTo(cx, cy);
                std::cout << "Готово.\n";
                break;

            case 8:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                std::cout << "Введите угол (градусы): ";
                std::cin >> angle;
                rhombus->rotateAroundCenter(angle);
                std::cout << "Готово.\n";
                break;

            case 9:
                if (!rhombus) { std::cout << "Сначала создайте ромб!\n"; break; }
                rhombus->resetToInitial();
                std::cout << "Сброшено в исходное положение.\n";
                break;

            case 0:
                std::cout << "Выход.\n";
                break;

            default:
                std::cout << "Неверный выбор.\n";
        }
    }

    return 0;
}