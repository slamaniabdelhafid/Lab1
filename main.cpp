/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdint>
#include <chrono>
#include <omp.h>

#pragma pack(push, 1) 
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

class BMPImage {
public:
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::vector<uint8_t> pixelData;

    bool load(const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Cannot open file " << filename << "!\n";
            return false;
        }

        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        if (fileHeader.bfType != 0x4D42) {
            std::cerr << "Error: Not a BMP file.\n";
            return false;
        }

        if (infoHeader.biBitCount != 24) {
            std::cerr << "Error: Only 24-bit BMP files are supported.\n";
            return false;
        }

        int rowSize = ((infoHeader.biWidth * 3 + 3) / 4) * 4;
        int dataSize = rowSize * std::abs(infoHeader.biHeight);
        pixelData.resize(dataSize);

        file.seekg(fileHeader.bfOffBits, std::ios::beg);
        file.read(reinterpret_cast<char*>(pixelData.data()), dataSize);
        file.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Load time: " << elapsed.count() << " seconds\n";

        std::cout << "Successfully loaded BMP file: " << filename << "\n";
        std::cout << "Image width: " << infoHeader.biWidth << ", height: " << infoHeader.biHeight << "\n";
        
        return true;
    }

    void save(const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Cannot save file " << filename << "!\n";
            return;
        }

        file.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
        file.write(reinterpret_cast<char*>(pixelData.data()), pixelData.size());
        file.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Save time: " << elapsed.count() << " seconds\n";

        std::cout << "Image saved as: " << filename << "\n";
    }

    void rotate90Clockwise() {
        auto start = std::chrono::high_resolution_clock::now();
        
        int width = infoHeader.biWidth;
        int height = infoHeader.biHeight;
        int rowSize = ((width * 3 + 3) / 4) * 4;
        int newRowSize = ((height * 3 + 3) / 4) * 4;

        std::vector<uint8_t> newData(newRowSize * width);
        
        #pragma omp parallel for collapse(2)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int oldIndex = y * rowSize + x * 3;
                int newIndex = x * newRowSize + (height - 1 - y) * 3;
                std::copy(pixelData.begin() + oldIndex, pixelData.begin() + oldIndex + 3, 
                          newData.begin() + newIndex);
            }
        }

        pixelData = newData;
        std::swap(infoHeader.biWidth, infoHeader.biHeight);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Clockwise rotation time: " << elapsed.count() << " seconds\n";
    }

    void rotate90CounterClockwise() {
        auto start = std::chrono::high_resolution_clock::now();
        
        int width = infoHeader.biWidth;
        int height = infoHeader.biHeight;
        int rowSize = ((width * 3 + 3) / 4) * 4;
        int newRowSize = ((height * 3 + 3) / 4) * 4;

        std::vector<uint8_t> newData(newRowSize * width);
        
        #pragma omp parallel for collapse(2)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int oldIndex = y * rowSize + x * 3;
                int newIndex = (width - 1 - x) * newRowSize + y * 3;
                std::copy(pixelData.begin() + oldIndex, pixelData.begin() + oldIndex + 3, 
                          newData.begin() + newIndex);
            }
        }

        pixelData = newData;
        std::swap(infoHeader.biWidth, infoHeader.biHeight);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Counter-clockwise rotation time: " << elapsed.count() << " seconds\n";
    }
};

int main() {
    auto total_start = std::chrono::high_resolution_clock::now();
    
    BMPImage image;

    if (!image.load("input.bmp")) {
        return 1;
    }

    image.rotate90Clockwise();
    image.save("rotated_clockwise.bmp");

    image.rotate90CounterClockwise();
    image.save("rotated_counterclockwise.bmp");

    auto total_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_elapsed = total_end - total_start;
    std::cout << "Total execution time: " << total_elapsed.count() << " seconds\n";

    return 0;
}
