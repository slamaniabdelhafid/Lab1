/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#include <iostream>
#include <vector>
#include "bmp.h"

int main() {
    try {
        BMPHeader header;
        BMPInfoHeader infoHeader;
        std::vector<uint8_t> imageData;

        // Load BMP image
        loadBMP("input.bmp", header, infoHeader, imageData);

        // Rotate image 90 degrees clockwise
        std::vector<uint8_t> rotatedData;
        rotate90Clockwise(imageData, rotatedData, infoHeader.width, infoHeader.height);

        // Save rotated image
        saveBMP("output_rotated.bmp", header, infoHeader, rotatedData);

        // Rotate image 90 degrees counter-clockwise
        std::vector<uint8_t> rotatedCounterClockwiseData;
        rotate90CounterClockwise(imageData, rotatedCounterClockwiseData, infoHeader.width, infoHeader.height);

        // Save counter-clockwise rotated image
        saveBMP("output_rotated_counter_clockwise.bmp", header, infoHeader, rotatedCounterClockwiseData);

        // Apply Gaussian filter (to be implemented)
        std::vector<uint8_t> filteredData;
        applyGaussianFilter(rotatedData, filteredData, infoHeader.width, infoHeader.height);

        // Save filtered image
        saveBMP("output_filtered.bmp", header, infoHeader, filteredData);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}