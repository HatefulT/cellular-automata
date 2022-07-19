#pragma once

#include <string>
#include <fstream>

#include <iostream>
#include <iomanip>

using namespace std;

#pragma pack(1)
struct BMPHeader
{
    uint16_t type = 0x4d42;         // Magic identifier: 0x4d42
    uint32_t size = 0;              // File size in bytes
    uint16_t reserved1 = 0;         // Not used
    uint16_t reserved2 = 0;         // Not used
    uint32_t offset = 54;           // Offset to image data in bytes from beginning of file
    uint32_t dib_header_size = 40;   // DIB Header size in bytes
    int32_t  width_px = 0;          // Width of the image
    int32_t  height_px = 0;         // Height of image
    uint16_t num_planes = 1;        // Number of color planes
    uint16_t bits_per_pixel = 24;   // Bits per pixel
    uint32_t compression = 0;       // Compression type
    uint32_t image_size_bytes = 0;  // Image size in bytes
    int32_t  x_resolution_ppm = 0;  // Pixels per meter
    int32_t  y_resolution_ppm = 0;  // Pixels per meter
    uint32_t num_colors = 0;        // Number of colors
    uint32_t important_colors = 0;  // Important colors
};

struct Image
{
    BMPHeader header;
    uint8_t **values;

    Image();
    Image(string filename);
    Image(uint32_t width, uint32_t height);
    ~Image();

    void write(string filename);
    uint32_t getRGB(uint32_t x, uint32_t y);
};
