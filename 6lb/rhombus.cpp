#include "rhombus.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

Rhombus::Rhombus(double x1, double y1, double x2, double y2, double x3, double y3) 
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {
    calculateFourthVertex();
}

void Rhombus::calculateFourthVertex() {
    double centerX = (x1 + x3) / 2;
    double centerY = (y1 + y3) / 2;
    x4 = 2 * centerX - x2;
    y4 = 2 * centerY - y2;
}

void Rhombus::printParameters() const {
    cout << "Ромб с вершинами:\n";
    cout << "A(" << x1 << ", " << y1 << ")\n";
    cout << "B(" << x2 << ", " << y2 << ")\n";
    cout << "C(" << x3 << ", " << y3 << ")\n";
    cout << "D(" << x4 << ", " << y4 << ")\n";
    cout << "Площадь: " << calculateArea() << endl;
}

bool Rhombus::isPointOnBorder(double x, double y, double epsilon) const {
    // Проверяем принадлежность точки к каждой из 4 сторон
    
    // Сторона AB
    double AB = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double AP = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
    double PB = sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
    if (abs(AP + PB - AB) < epsilon) return true;
    
    // Сторона BC
    double BC = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double BP = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
    double PC = sqrt(pow(x3 - x, 2) + pow(y3 - y, 2));
    if (abs(BP + PC - BC) < epsilon) return true;
    
    // Сторона CD
    double CD = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
    double CP = sqrt(pow(x - x3, 2) + pow(y - y3, 2));
    double PD = sqrt(pow(x4 - x, 2) + pow(y4 - y, 2));
    if (abs(CP + PD - CD) < epsilon) return true;
    
    // Сторона DA
    double DA = sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2));
    double DP = sqrt(pow(x - x4, 2) + pow(y - y4, 2));
    double PA = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
    if (abs(DP + PA - DA) < epsilon) return true;
    
    return false;
}

bool Rhombus::intersectsXAxis() const {
    if (y1 * y2 <= 0 || y1 * y3 <= 0 || y1 * y4 <= 0 ||
        y2 * y3 <= 0 || y2 * y4 <= 0 || y3 * y4 <= 0) {
        return true;
    }
    return false;
}

bool Rhombus::intersectsYAxis() const {
    if (x1 * x2 <= 0 || x1 * x3 <= 0 || x1 * x4 <= 0 ||
        x2 * x3 <= 0 || x2 * x4 <= 0 || x3 * x4 <= 0) {
        return true;
    }
    return false;
}

double Rhombus::calculateArea() const {
    double d1 = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
    double d2 = sqrt(pow(x4 - x2, 2) + pow(y4 - y2, 2));
    return (d1 * d2) / 2;
}