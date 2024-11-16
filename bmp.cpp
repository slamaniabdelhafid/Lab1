/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#include "bmp.h"

void BMPImage::load(const std::string &filename) {
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

void BMPImage::save(const std::string &filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing");
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void BMPImage::rotate90Clockwise() {
    std::vector<uint8_t> rotatedData;
    rotate90Clockwise(data, rotatedData);
    data = std::move(rotatedData);
}

void BMPImage::rotate90CounterClockwise() {
    std::vector<uint8_t> rotatedData;
    rotate90CounterClockwise(data, rotatedData);
    data = std::move(rotatedData);
}

void BMPImage::rotate90Clockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    dst.resize(infoHeader.height * infoHeader.width * 3);
    for (int y = 0; y < infoHeader.height; ++y) {
        for (int x = 0; x < infoHeader.width; ++x) {
            int srcIndex = (y * infoHeader.width + x) * 3;
            int dstIndex = ((infoHeader.width - 1 - x) ) * infoHeader.height + y) * 3;
            dst[dstIndex] = src[srcIndex];       // Blue
            dst[dstIndex + 1] = src[srcIndex + 1]; // Green
            dst[dstIndex + 2] = src[srcIndex + 2]; // Red
        }
    }
}

void BMPImage::rotate90CounterClockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    dst.resize(infoHeader.height * infoHeader.width * 3);
    for (int y = 0; y < infoHeader.height; ++y) {
        for (int x = 0; x < infoHeader.width; ++x) {
            int srcIndex = (y * infoHeader.width + x) * 3;
            int dstIndex = (x * infoHeader.height + (infoHeader.height - 1 - y)) * 3;
            dst[dstIndex] = src[srcIndex];       // Blue
            dst[dstIndex + 1] = src[srcIndex + 1]; // Green
            dst[dstIndex + 2] = src[srcIndex + 2]; // Red
        }
    }
}

void BMPImage::applyGaussianFilter(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst) {
    // Implementation of Gaussian filter would go here
    // This is a placeholder for the actual filter logic
}
