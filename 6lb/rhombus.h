#ifndef RHOMBUS_H
#define RHOMBUS_H

class Rhombus {
private:
    double x1, y1; // Первая вершина
    double x2, y2; // Вторая вершина
    double x3, y3; // Третья вершина
    double x4, y4; // Четвертая вершина (вычисляется)
    
    void calculateFourthVertex(); // Вычисление 4-й вершины
    
public:
    // Конструктор с тремя вершинами
    Rhombus(double x1, double y1, double x2, double y2, double x3, double y3);
    
    // Вывод параметров ромба
    void printParameters() const;
    
    // Проверка принадлежности точки границе ромба
    bool isPointOnBorder(double x, double y, double epsilon = 0.005) const;
    
    // Проверка пересечения с осью абсцисс
    bool intersectsXAxis() const;
    
    // Проверка пересечения с осью ординат
    bool intersectsYAxis() const;
    
    // Вычисление площади ромба
    double calculateArea() const;
    
    // Геттеры для координат вершин
    double getX4() const { return x4; }
    double getY4() const { return y4; }
};

#endif // RHOMBUS_H