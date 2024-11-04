/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#include "bmp.h"

void loadBMP(const std::string &filename, BMPHeader &header, BMPInfoHeader &infoHeader, std::vector<uint8_t> &data) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    // Check file format
    if (header.fileType != 0x4D42) {
        throw std::runtime_error("Not a BMP file");
    }

    // Allocate memory for pixel data
    data.resize(infoHeader.width * infoHeader.height * 3);
    file.seekg(header.offsetData, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
}

void saveBMP(const std::string &filename, const BMPHeader &header, const BMPInfoHeader &infoHeader, const std::vector<uint8_t> &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing");
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void rotate90Clockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height) {
    dst.resize(width * height * 3);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int srcIndex = (y * width + x) * 3;
            int dstIndex = ((width - 1 - x) * height + y) * 3;
            dst[dstIndex] = src[srcIndex];        // Blue
            dst[dstIndex + 1] = src[srcIndex + 1]; // Green
            dst[dstIndex + 2] = src[srcIndex + 2]; // Red
        }
    }
}

void rotate90CounterClockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height) {
    dst.resize(width * height * 3);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int srcIndex = (y * width + x) * 3;
            int dstIndex = (x * height + (height - 1 - y)) * 3;
            dst[dstIndex] = src[srcIndex];        // Blue
            dst[dstIndex + 1] = src[srcIndex + 1]; // Green
            dst[dstIndex + 2] = src[srcIndex + 2]; // Red
        }
    }
}

void applyGaussianFilter(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height) {
    // TO DO: Implement Gaussian filter
    dst = src; // Temporary solution, replace with actual implementation
}