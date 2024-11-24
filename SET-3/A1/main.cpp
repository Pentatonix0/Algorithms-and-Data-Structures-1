#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Structure to store the parameters of a circle
struct Circle {
    double x, y, r;
};

// Function to check if a point (x, y) lies inside a given circle
bool isInsideCircle(double x, double y, const Circle& circle) {
    return (x - circle.x) * (x - circle.x) + (y - circle.y) * (y - circle.y) <= circle.r * circle.r;
}

// Monte Carlo method to estimate the intersection area of three circles
double monteCarlo(int num_points, const Circle& circle1, const Circle& circle2, const Circle& circle3) {
    // Calculate the bounding box of all three circles
    double x_min = std::min(circle1.x - circle1.r, std::min(circle2.x - circle2.r, circle3.x - circle3.r));
	double x_max = std::max(circle1.x + circle1.r, std::max(circle2.x + circle2.r, circle3.x + circle3.r));
	double y_min = std::min(circle1.y - circle1.r, std::min(circle2.y - circle2.r, circle3.y - circle3.r));
	double y_max = std::max(circle1.y + circle1.r, std::max(circle2.y + circle2.r, circle3.y + circle3.r));

    // Area of the bounding rectangle
    double area_rect = (x_max - x_min) * (y_max - y_min);
    
    // Counter for points inside the intersection of the three circles
    int count_inside = 0;

    // Initialize the random number generator
    std::srand(std::time(nullptr));

    // Monte Carlo simulation
    for (int i = 0; i < num_points; ++i) {
        // Generate a random point within the bounding box
        double px = x_min + (x_max - x_min) * (rand() / double(RAND_MAX));
        double py = y_min + (y_max - y_min) * (rand() / double(RAND_MAX));
        
        // Check if the point lies inside all three circles
        if (isInsideCircle(px, py, circle1) && isInsideCircle(px, py, circle2) && isInsideCircle(px, py, circle3)) {
            count_inside++;
        }
    }
    
    // Estimate the intersection area using the ratio of points inside the circles
    double estimated_area = (double(count_inside) / num_points) * area_rect;
    return estimated_area;
}

int main() {
    // Initialize the random seed
    std::srand(std::time(nullptr));
    
    // Define the parameters of the circles
    Circle circle1 = {1, 1, 1};
    Circle circle2 = {1.5, 2, std::sqrt(5) / 2};
    Circle circle3 = {2, 1.5, std::sqrt(5) / 2};
    
    // Output file to store the results
    std::ofstream output("monte_carlo_results.txt");
    
    // Loop through different numbers of points (from 100 to 100000 with step 500)
    for (int N = 100; N <= 100000; N += 500) {
        // Perform the Monte Carlo simulation for each number of points
        double estimated_area = monteCarlo(N, circle1, circle2, circle3);
        
        // Write the results to the file and print them to the console
        output << N << " " << estimated_area << std::endl;
        std::cout << "N = " << N << ", Estimated intersection area: " << estimated_area << std::endl;
    }
    
    // Close the output file
    output.close();
    
    return 0;
}
