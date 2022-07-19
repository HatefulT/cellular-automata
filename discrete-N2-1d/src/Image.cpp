#include "Image.h"

Image::Image() : header(), values(nullptr) {}

Image::Image(string filename)
{
    ifstream ifs(filename, ios::binary);
    if(!ifs) abort();
    ifs.read(reinterpret_cast<char *>(&header), sizeof(BMPHeader));
    if(header.type != 0x4d42) abort();
    if(header.bits_per_pixel != 24) abort();
    values = new uint8_t*[header.height_px];
    for(int y=0; y<header.height_px; y++)
        values[y] = new uint8_t[header.width_px * 3];

    for(int y=0; y<header.height_px; y++)
        ifs.read(reinterpret_cast<char *>(values[y]), header.width_px * 3);
    ifs.close();
}

Image::Image(uint32_t width, uint32_t height)
    : header()
{
    header.width_px = width;
    header.height_px = height;
    header.image_size_bytes = width * height * header.bits_per_pixel / 8;
    header.size = header.image_size_bytes + header.offset;
    values = new uint8_t*[header.height_px];
    for(int y=0; y<header.height_px; y++)
        values[y] = new uint8_t[header.width_px * 3];

    for(int y=0; y<header.height_px; y++)
        for(int x1=0; x1<header.width_px*3; x1++)
            values[y][x1] = 0;
}

Image::~Image()
{
    for(int y=0; y<header.height_px; y++)
        delete [] values[y];
    delete [] values;
}

void Image::write(string filename)
{
    ofstream ofs(filename, ios::binary);
    ofs.write(reinterpret_cast<char *>(&header), sizeof(BMPHeader));

    for(int y=0; y<header.height_px; y++)
        ofs.write(reinterpret_cast<char *>(values[y]), header.width_px * 3);

    ofs.close();
}

uint32_t Image::getRGB(uint32_t x, uint32_t y)
{
    if(x >= header.width_px)
        cout << "58 jopa x:" << x << " " << header.width_px << endl;
    if(y >= header.height_px)
        cout << "60 jopa y:" << y << " " << header.height_px << endl;
    return (values[y][3*x + 0] << 16) |
            (values[y][3*x + 1] << 8) |
            (values[y][3*x + 2]);
}
