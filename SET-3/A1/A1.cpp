#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Structure for representing a circle
struct Circle {
    double x, y, r;
};

// Check if a point (px, py) is inside the circle
bool isInsideCircle(double px, double py, const Circle& circle) {
    return (px - circle.x) * (px - circle.x) + (py - circle.y) * (py - circle.y) <= circle.r * circle.r;
}

int main() {
    // Read input data
    Circle circle1, circle2, circle3;
    std::cin >> circle1.x >> circle1.y >> circle1.r;
    std::cin >> circle2.x >> circle2.y >> circle2.r;
    std::cin >> circle3.x >> circle3.y >> circle3.r;
    
    // Set the bounds for the region in which we will generate points
    // For simplicity, use the region that contains all three circles
    double x_min = std::min(circle1.x - circle1.r, std::min(circle2.x - circle2.r, circle3.x - circle3.r));
    double x_max = std::max(circle1.x + circle1.r, std::max(circle2.x + circle2.r, circle3.x + circle3.r));
    double y_min = std::min(circle1.y - circle1.r, std::min(circle2.y - circle2.r, circle3.y - circle3.r));
    double y_max = std::max(circle1.y + circle1.r, std::max(circle2.y + circle2.r, circle3.y + circle3.r));

    // Area of the rectangular region
    double area_rect = (x_max - x_min) * (y_max - y_min);
    
    // Start Monte Carlo simulation
    const int num_points = 1000000;  // Number of random points
    int count_inside = 0;
    
    // Initialize random number generator
    std::srand(std::time(nullptr));
    
    for (int i = 0; i < num_points; ++i) {
        // Generate a random point within the region
        double px = x_min + (x_max - x_min) * (rand() / double(RAND_MAX));
        double py = y_min + (y_max - y_min) * (rand() / double(RAND_MAX));
        
        // Check if the point lies inside the intersection of all three circles
        if (isInsideCircle(px, py, circle1) && isInsideCircle(px, py, circle2) && isInsideCircle(px, py, circle3)) {
            count_inside++;
        }
    }
    
    // Estimated area of the intersection
    double estimated_area = (double(count_inside) / num_points) * area_rect;
    
    // Output the result
    std::cout.precision(12);
    std::cout << estimated_area << std::endl;

    return 0;
}
