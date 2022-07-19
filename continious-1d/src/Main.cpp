#include <iostream>
#include "Image.h"

void calculate(const float *cells, float *nextCells, uint32_t W,
    float a, float b, float c, float d)
{
    for(uint32_t x=0; x<W; x++) {
        float tmp = 0;
        if(x != 0)
            tmp += a * cells[x-1];
        else
            tmp += a * cells[W-1];

        tmp += b * cells[x];

        if(x != W-1)
            tmp += c * cells[x+1];
        else
            tmp += c * cells[0];

        nextCells[x] = tmp + d;
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
    for(uint32_t x=0; x<W; x++) {
        auto bwConv = [](float x) -> uint8_t {
            float tmp = (x * 255);
            if(tmp > 255)
                return 255U;
            if(tmp < 0)
                return 0U;
            return static_cast<uint32_t>(tmp);
        };
        img.values[0][3*x]   = bwConv(cells[x]);
        img.values[0][3*x+1] = bwConv(cells[x]);
        img.values[0][3*x+2] = bwConv(cells[x]);
    }
    for(uint32_t y=1; y<H; y++) {
        calculate(cells, nextCells, W, ruleA, ruleB, ruleC, ruleD);
        for(uint32_t x=0; x<W; x++) {
            auto bwConv = [](float x) -> uint8_t {
                float tmp = (x * 255);
                while(tmp > 255.f)
                    tmp -= 255.f;
                while(tmp < 0.f)
                    tmp += 255.f;
                return static_cast<uint32_t>(tmp);
            };
            img.values[y][3*x]   = bwConv(cells[x]);
            img.values[y][3*x+1] = bwConv(cells[x]);
            img.values[y][3*x+2] = bwConv(cells[x]);
        }
        float *tmp = nextCells;
        nextCells = cells;
        cells = tmp;
    }
    img.write("output.bmp");
}
