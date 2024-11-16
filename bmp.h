/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <fstream>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t fileType;      // always 'BM'
    uint32_t fileSize;      // size of the file in bytes
    uint16_t reserved1;     // reserved
    uint16_t reserved2;     // reserved
    uint32_t offsetData;    // offset to the pixel data
};

struct BMPInfoHeader {
    uint32_t size;          // size of this header
    int32_t width;          // width of the bitmap in pixels
    int32_t height;         // height of the bitmap in pixels
    uint16_t planes;        // number of color planes
    uint16_t bitCount;      // bits per pixel
    uint32_t compression;   // compression type
    uint32_t sizeImage;     // size of the image data
    int32_t xPixelsPerMeter; // horizontal resolution
    int32_t yPixelsPerMeter; // vertical resolution
    uint32_t colorsUsed;    // number of colors in the palette
    uint32_t colorsImportant; // important colors
};
#pragma pack(pop)
// Это следует сделать методами класса картинки. Тут слишком много параметров, состояние картинки разделено, поэтому никаких
// инвариантов поддержано не будет
void loadBMP(const std::string &filename, BMPHeader &header, BMPInfoHeader &infoHeader, std::vector<uint8_t> &data);
void saveBMP(const std::string &filename, const BMPHeader &header, const BMPInfoHeader &infoHeader, const std::vector<uint8_t> &data);
void rotate90Clockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height);
void rotate90CounterClockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height);
void applyGaussianFilter(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst, int width, int height);

#endif // BMP_H
