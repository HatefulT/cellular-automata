#include <iostream>
#include <cmath>
#include "Image.h"

void calculate(const float *cells, float *nextCells, uint32_t W,
    float a, float b, float c, float d)
{
    for(uint32_t x=0; x<W; x++) {
        float tmp = d;
        if(x != 0)
            tmp += a * cells[x-1];
        else
            tmp += a * cells[W-1];

        tmp += b * cells[x];

        if(x != W-1)
            tmp += c * cells[x+1];
        else
            tmp += c * cells[0];

        if(tmp > 1.f)
            tmp -= floor(tmp);
        if(tmp < 0.f)
            tmp += floor(1.f-tmp);

        nextCells[x] = tmp;
    }
}

int main() {
    srand((unsigned) time(NULL));
    uint32_t W;
    uint32_t H;
    cout << "Width of image: ";
    cin >> W;
    cout << "Height of image: ";
    cin >> H;

    float *cells = new float[W];
    for(uint32_t x=0; x<W; x++)
        cells[x] = (rand() % 100) / 100.f;
    float *nextCells = new float[W];

    float ruleA, ruleB, ruleC, ruleD;

    cout << "Rule float quad (a, b, c, d): ";
    cin >> ruleA >> ruleB >> ruleC >> ruleD;

    Image img{ W, H };
    auto bwConv = [](float x) -> uint8_t {
        float tmp = (x * 255);
        if(tmp > 255.f)
            return 255U;
        if(tmp < 0.f)
            return 0U;
        return static_cast<uint32_t>(tmp);
    };

    for(uint32_t x=0; x<W; x++) {
        img.values[0][3*x]   = bwConv(cells[x]);
        img.values[0][3*x+1] = bwConv(cells[x]);
        img.values[0][3*x+2] = bwConv(cells[x]);
    }
    for(uint32_t y=1; y<H; y++) {
        calculate(cells, nextCells, W, ruleA, ruleB, ruleC, ruleD);
        for(uint32_t x=0; x<W; x++) {
            img.values[y][3*x]   = bwConv(cells[x]);
            img.values[y][3*x+1] = bwConv(cells[x]);
            img.values[y][3*x+2] = bwConv(cells[x]);
        }
        float *tmp = nextCells;
        nextCells = cells;
        cells = tmp;
    }
    img.write("output.bmp");

    delete [] cells;
    delete [] nextCells;
}
