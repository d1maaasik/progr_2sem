#include "rhombus.h"
#include <iostream>
#include <cmath>

Rhombus::Rhombus(double x1, double y1, double x2, double y2, double x3, double y3)
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {
    calculateFourthVertex();
}

void Rhombus::calculateFourthVertex() {
    const double center_x = (x1 + x3) / 2.0;
    const double center_y = (y1 + y3) / 2.0;
    x4 = 2.0 * center_x - x2;
    y4 = 2.0 * center_y - y2;
}

void Rhombus::printParameters() const {
    std::cout << "Ромб с вершинами:\n";
    std::cout << "A(" << x1 << ", " << y1 << ")\n";
    std::cout << "B(" << x2 << ", " << y2 << ")\n";
    std::cout << "C(" << x3 << ", " << y3 << ")\n";
    std::cout << "D(" << x4 << ", " << y4 << ")\n";
    std::cout << "Площадь: " << calculateArea() << std::endl;
}

bool Rhombus::isPointOnBorder(double x, double y, double epsilon) const {
    const auto dist = [](double ax, double ay, double bx, double by) {
        return std::sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
    };

    const double ab = dist(x1, y1, x2, y2);
    const double ap = dist(x1, y1, x, y);
    const double pb = dist(x, y, x2, y2);
    if (std::abs(ap + pb - ab) < epsilon) return true;

    const double bc = dist(x2, y2, x3, y3);
    const double bp = dist(x2, y2, x, y);
    const double pc = dist(x, y, x3, y3);
    if (std::abs(bp + pc - bc) < epsilon) return true;

    const double cd = dist(x3, y3, x4, y4);
    const double cp = dist(x3, y3, x, y);
    const double pd = dist(x, y, x4, y4);
    if (std::abs(cp + pd - cd) < epsilon) return true;

    const double da = dist(x4, y4, x1, y1);
    const double dp = dist(x4, y4, x, y);
    const double pa = dist(x, y, x1, y1);
    if (std::abs(dp + pa - da) < epsilon) return true;

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
    const double d1 = std::sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    const double d2 = std::sqrt((x4 - x2) * (x4 - x2) + (y4 - y2) * (y4 - y2));
    return (d1 * d2) / 2.0;
}

void Rhombus::getVertices(double& ax, double& ay,
                          double& bx, double& by,
                          double& cx, double& cy,
                          double& dx, double& dy) const {
    ax = x1; ay = y1;
    bx = x2; by = y2;
    cx = x3; cy = y3;
    dx = x4; dy = y4;
}

void Rhombus::setVertices(double ax, double ay,
                          double bx, double by,
                          double cx, double cy) {
    x1 = ax; y1 = ay;
    x2 = bx; y2 = by;
    x3 = cx; y3 = cy;
    calculateFourthVertex();
}

void Rhombus::getCenter(double& cx, double& cy) const {
    cx = (x1 + x3) / 2.0;
    cy = (y1 + y3) / 2.0;
}