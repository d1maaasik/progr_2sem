#ifndef TRANSFORMABLE_RHOMBUS_H
#define TRANSFORMABLE_RHOMBUS_H

#include "rhombus.h"

class TransformableRhombus : public Rhombus {
private:
    double init_x1, init_y1;
    double init_x2, init_y2;
    double init_x3, init_y3;

public:
    TransformableRhombus(double x1, double y1, double x2, double y2, double x3, double y3);

    void translateBy(double dx, double dy);
    void moveCenterTo(double cx, double cy);

    void rotateAroundCenter(double angleDeg);

    void resetToInitial();
};

#endif // TRANSFORMABLE_RHOMBUS_H