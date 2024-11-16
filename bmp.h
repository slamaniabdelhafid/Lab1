/*slamani abdelhafid.  group 24.b83 . st130302@student.spbu.ru*/
#ifndef BMP_H
#define BMP_H

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <fstream>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t fileType;        // always 'BM'
    uint32_t fileSize;        // size of the file in bytes
    uint16_t reserved1;       // reserved
    uint16_t reserved2;       // reserved
    uint32_t offsetData;      // offset to the pixel data
};

struct BMPInfoHeader {
    uint32_t size;            // size of this header
    int32_t width;            // width of the bitmap in pixels
    int32_t height;           // height of the bitmap in pixels
    uint16_t planes;          // number of color planes
    uint16_t bitCount;        // bits per pixel
    uint32_t compression;     // compression type
    uint32_t sizeImage;       // size of the image data
    int32_t xPixelsPerMeter;   // horizontal resolution
    int32_t yPixelsPerMeter;   // vertical resolution
    uint32_t colorsUsed;      // number of colors in the palette
    uint32_t colorsImportant;  // important colors
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

class BMPImage {
public:
    BMPImage() = default;
    ~BMPImage() = default;

    void load(const std::string &filename);
    void save(const std::string &filename) const;
    void rotate90Clockwise();
    void rotate90CounterClockwise();
    void applyGaussianFilter();

    const std::vector<uint8_t>& getData() const { return data; }
    int getWidth() const { return infoHeader.width; }
    int getHeight() const { return infoHeader.height; }

private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<uint8_t> data;

    void rotate90Clockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst);
    void rotate90CounterClockwise(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst);
    void applyGaussianFilter(const std::vector<uint8_t> &src, std::vector<uint8_t> &dst);
};

#endif // BMP_H