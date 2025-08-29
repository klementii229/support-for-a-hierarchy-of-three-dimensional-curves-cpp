#include <memory>
#include <numbers>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <omp.h>
#include "../include/curves.hpp"

int main() {
    std::vector<std::shared_ptr<Curves>> curves;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> type_dist(0, 2);
    std::uniform_real_distribution<> param_dist(0.1, 10.0);
    
    for (int i = 0; i < 10; ++i) {
        int curve_type = type_dist(gen);
        switch (curve_type) {
            case 0: // Circle
                curves.push_back(std::make_shared<Circle>(param_dist(gen)));
                break;
            case 1: // Ellipse
                curves.push_back(std::make_shared<Ellipse>(
                    param_dist(gen), param_dist(gen)));
                break;
            case 2: // Spiral
                curves.push_back(std::make_shared<Spiral>(
                    param_dist(gen), param_dist(gen)));
                break;
        }
    }
    
    double t = std::numbers::pi / 4;
    std::cout << "Points and derivatives at t=PI/4:\n";
    for (const auto& curve : curves) {
        Point3D point = curve->getPoint(t);
        Vector3D derivative = curve->getDerivative(t);
        
        std::cout << "Point: ";
        point.printPoint();
        std::cout << "Derivative: (" 
                  << derivative.x << ", " 
                  << derivative.y << ", " 
                  << derivative.z << ")\n\n";
    }
    
    std::vector<std::shared_ptr<Circle>> circles;
    for (const auto& curve : curves) {
        if (auto circle = std::dynamic_pointer_cast<Circle>(curve)) {
            circles.push_back(circle);
        }
    }
    
    std::sort(circles.begin(), circles.end(),
        [](const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
            return a->getRadius() < b->getRadius();
        });
    
    double total_radius = 0.0;
    #pragma omp parallel for reduction(+:total_radius)
    for (size_t i = 0; i < circles.size(); ++i) {
        total_radius += circles[i]->getRadius();
    }
    
    std::cout << "Total radius of all circles: " << total_radius << std::endl;
    
    return 0;
}
