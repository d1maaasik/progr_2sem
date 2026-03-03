#ifndef RHOMBUS_H
#define RHOMBUS_H

class Rhombus {
private:
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;

    void calculateFourthVertex();

public:
    Rhombus(double x1, double y1, double x2, double y2, double x3, double y3);

    void printParameters() const;

    bool isPointOnBorder(double x, double y, double epsilon = 0.005) const;

    bool intersectsXAxis() const;
    bool intersectsYAxis() const;

    double calculateArea() const;

    double getX4() const { return x4; }
    double getY4() const { return y4; }

    // доступ к вершинам для наследника
    void getVertices(double& ax, double& ay,
                     double& bx, double& by,
                     double& cx, double& cy,
                     double& dx, double& dy) const;

    // установка вершин
    void setVertices(double ax, double ay,
                     double bx, double by,
                     double cx, double cy);

    // центр ромба
    void getCenter(double& cx, double& cy) const;
};

#endif // RHOMBUS_H