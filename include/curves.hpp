#pragma once
#define CURVES_API

struct CURVES_API Point3D {
    Point3D() = default;
    Point3D(double x_, double y_, double z_);
    double x = 0;
    double y = 0;
    double z = 0;
    void printPoint() const;
    ~Point3D() = default;
};

struct CURVES_API Vector3D {
    Vector3D() = default;
    Vector3D(double x_, double y_, double z_);
    double x = 0, y = 0, z = 0;
    double length() const;
    Vector3D normalize() const;
};

class CURVES_API Curves {
public:
    virtual Point3D getPoint(double t) = 0;
    virtual Vector3D getDerivative(double t) = 0;
    virtual ~Curves() = default;
};

class CURVES_API Circle : public Curves {
private:
    double radius;
    Point3D center;
public:
    Circle(double r, Point3D center_ = Point3D(0, 0, 0));
    Point3D getPoint(double t) override; 
    Vector3D getDerivative(double t) override;
    double getRadius() const;
};

class CURVES_API Ellipse : public Curves {
private:
    double a;
    double b;
    Point3D center;
public:
    Ellipse(double a_, double b_, Point3D center_ = Point3D(0, 0, 0));
    Point3D getPoint(double t) override; 
    Vector3D getDerivative(double t) override;
};

class CURVES_API Spiral : public Curves {
private:
    double radius;
    double step;
    Point3D center;
public:
    Spiral(double r, double s, Point3D center_ = Point3D(0, 0, 0));
    Point3D getPoint(double t) override; 
    Vector3D getDerivative(double t) override;
};