#include "transformable_rhombus.h"
#include <cmath>

TransformableRhombus::TransformableRhombus(double x1, double y1, double x2, double y2, double x3, double y3)
    : Rhombus(x1, y1, x2, y2, x3, y3),
      init_x1(x1), init_y1(y1), init_x2(x2), init_y2(y2), init_x3(x3), init_y3(y3) {}

void TransformableRhombus::translateBy(double dx, double dy) {
    double ax, ay, bx, by, cx, cy, dxv, dyv;
    getVertices(ax, ay, bx, by, cx, cy, dxv, dyv);

    ax += dx; ay += dy;
    bx += dx; by += dy;
    cx += dx; cy += dy;

    setVertices(ax, ay, bx, by, cx, cy);
}

void TransformableRhombus::moveCenterTo(double cx, double cy) {
    double cur_x, cur_y;
    getCenter(cur_x, cur_y);
    translateBy(cx - cur_x, cy - cur_y);
}

void TransformableRhombus::rotateAroundCenter(double angleDeg) {
    // поворот вокруг центра ромба
    const double pi = 3.14159265358979323846;
    const double a = angleDeg * pi / 180.0;
    const double cs = std::cos(a);
    const double sn = std::sin(a);

    double cx, cy;
    getCenter(cx, cy);

    double ax, ay, bx, by, cxv, cyv, dxv, dyv;
    getVertices(ax, ay, bx, by, cxv, cyv, dxv, dyv);

    auto rot = [&](double& x, double& y) {
        const double tx = x - cx;
        const double ty = y - cy;
        const double rx = tx * cs - ty * sn;
        const double ry = tx * sn + ty * cs;
        x = cx + rx;
        y = cy + ry;
    };

    rot(ax, ay);
    rot(bx, by);
    rot(cxv, cyv);

    setVertices(ax, ay, bx, by, cxv, cyv);
}

void TransformableRhombus::resetToInitial() {
    setVertices(init_x1, init_y1, init_x2, init_y2, init_x3, init_y3);
}