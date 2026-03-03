#ifndef RHOMBUS_H
#define RHOMBUS_H

class Rhombus {
private:
    double x1, y1; // вершина a
    double x2, y2; // вершина b
    double x3, y3; // вершина c
    double x4, y4; // вершина d (вычисляется)

    void calculateFourthVertex(); // вычисление 4-й вершины

public:
    Rhombus(double x1, double y1, double x2, double y2, double x3, double y3);

    void printParameters() const;

    bool isPointOnBorder(double x, double y, double epsilon = 0.005) const;

    bool intersectsXAxis() const;
    bool intersectsYAxis() const;

    double calculateArea() const;

    double getX4() const { return x4; }
    double getY4() const { return y4; }
};

#endif