// вариант 10
#include <iostream>
#include "rhombus.h"

using namespace std;

void displayMenu() {
    cout << "\nМеню:\n";
    cout << "1. Создать ромб\n";
    cout << "2. Проверить принадлежность точки границе\n";
    cout << "3. Проверить пересечение с осью X\n";
    cout << "4. Проверить пересечение с осью Y\n";
    cout << "5. Вывести параметры ромба\n";
    cout << "6. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    Rhombus* rhombus = nullptr;
    int choice;
    double x1, y1, x2, y2, x3, y3, x, y;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (rhombus != nullptr) delete rhombus;
                cout << "Введите координаты трех вершин ромба (x1 y1 x2 y2 x3 y3): ";
                cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
                rhombus = new Rhombus(x1, y1, x2, y2, x3, y3);
                cout << "Ромб создан. Координаты 4-й вершины: (" 
                     << rhombus->getX4() << ", " << rhombus->getY4() << ")\n";
                break;
                
            case 2:
                if (rhombus == nullptr) {
                    cout << "Сначала создайте ромб!\n";
                    break;
                }
                cout << "Введите координаты точки (x y): ";
                cin >> x >> y;
                if (rhombus->isPointOnBorder(x, y)) {
                    cout << "Точка принадлежит границе ромба.\n";
                } else {
                    cout << "Точка не принадлежит границе ромба.\n";
                }
                break;
                
            case 3:
                if (rhombus == nullptr) {
                    cout << "Сначала создайте ромб!\n";
                    break;
                }
                if (rhombus->intersectsXAxis()) {
                    cout << "Ромб пересекает ось X.\n";
                } else {
                    cout << "Ромб не пересекает ось X.\n";
                }
                break;
                
            case 4:
                if (rhombus == nullptr) {
                    cout << "Сначала создайте ромб!\n";
                    break;
                }
                if (rhombus->intersectsYAxis()) {
                    cout << "Ромб пересекает ось Y.\n";
                } else {
                    cout << "Ромб не пересекает ось Y.\n";
                }
                break;
                
            case 5:
                if (rhombus == nullptr) {
                    cout << "Сначала создайте ромб!\n";
                    break;
                }
                rhombus->printParameters();
                break;
                
            case 6:
                if (rhombus != nullptr) delete rhombus;
                cout << "Выход из программы.\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 6);
    
    return 0;
}