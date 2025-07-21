#include <opencv2/opencv.hpp>
#include <iostream>

void on_trackbar(int, void*) {
    // Callback function is required but won't do anything here
}

int main() {
    // Load an image
    cv::Mat src = cv::imread("doug.png");
    if (src.empty()) {
        std::cerr << "Error: Cannot load image!" << std::endl;
        return -1;
    }

    // Create a window
    std::string window_name = "Contrast and Brightness Adjustments";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    // Initialize contrast and brightness values
    int contrast_slider = 100;   // Equivalent to alpha = 1.0
    int brightness_slider = 50; // Equivalent to beta = 0

    // Create trackbars
    cv::createTrackbar("Contrast", window_name, &contrast_slider, 300, on_trackbar);
    cv::createTrackbar("Brightness", window_name, &brightness_slider, 100, on_trackbar);

    cv::Mat dst; // Output image

    while (true) {
        // Compute contrast and brightness
        double alpha = contrast_slider / 100.0; // Map slider to alpha (range 1.0–3.0)
        int beta = brightness_slider - 50;      // Map slider to beta (range -50 to +50)

        // Apply contrast and brightness adjustments
        src.convertTo(dst, -1, alpha, beta);

        // Display the updated image
        cv::imshow(window_name, dst);

        // Exit on 'ESC' key press
        if (cv::waitKey(10) == 27) break;
    }

    return 0;
}