#include <cmath>
#include "../include/curves.hpp"
#include <iostream>
#include <stdexcept>


Point3D::Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

void Point3D::printPoint() const {
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}


Vector3D::Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

double Vector3D::length() const {
    return std::sqrt((x*x) + (y*y) + (z*z));
}

Vector3D Vector3D::normalize() const {
    double len = length();
    if (len < 1e-10) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    return Vector3D(x/len, y/len, z/len);
}


Circle::Circle(double r, Point3D center_) : radius(r), center(center_) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}

Point3D Circle::getPoint(double t) {
    return Point3D(
        center.x + (radius * std::cos(t)),
        center.y + (radius * std::sin(t)),
        center.z
    );
}

Vector3D Circle::getDerivative(double t) {
    return Vector3D(
        -radius * std::sin(t),
        radius * std::cos(t),
        0
    );
}

double Circle::getRadius() const {
    return radius;
}

Ellipse::Ellipse(double a_, double b_, Point3D center_) 
    : a(a_), b(b_), center(center_) {
    if (a <= 0 || b <= 0) {
        throw std::invalid_argument("Semi-axes must be positive");
    }
}

Point3D Ellipse::getPoint(double t) {
    return Point3D(
        center.x + (a * std::cos(t)),
        center.y + (b * std::sin(t)),
        center.z
    );
}

Vector3D Ellipse::getDerivative(double t) {
    return Vector3D(
        -a * std::sin(t),
        b * std::cos(t),
        0
    );
}


Spiral::Spiral(double r, double s, Point3D center_) 
    : radius(r), step(s), center(center_) {
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
}

Point3D Spiral::getPoint(double t) {
    return Point3D(
        center.x + (radius * std::cos(t)),
        center.y + (radius * std::sin(t)),
        center.z + (step * t / (2 * M_PI)) // полный виток на каждые 2π
    );
}

Vector3D Spiral::getDerivative(double t) {
    return Vector3D(
        -radius * std::sin(t),
        radius * std::cos(t),
        step / (2 * M_PI)
    );
}