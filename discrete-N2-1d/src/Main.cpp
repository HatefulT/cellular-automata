#include <iostream>
#include "Image.h"

void calculate(const bool *cells, bool *nextCells, uint32_t W, uint32_t rule)
{
    for(uint32_t x=0; x<W; x++) {
        uint32_t bit = 0;
        auto lambda = [](bool a, uint32_t ret) { return a ? ret : 0; };
        if(x != 0)
            bit += lambda(cells[x-1], 4U);
        else
            bit += lambda(cells[W-1], 4U);

        bit += lambda(cells[x], 2U);

        if(x != W-1)
            bit += lambda(cells[x+1], 1U);
        else
            bit += lambda(cells[0], 1U);

        nextCells[x] = static_cast<bool>((rule >> (7 - bit)) & 1U);
    }
}

int main() {
    srand((unsigned) time(NULL));
    uint32_t W;
    uint32_t H = 200;
    cout << "Width of image: ";
    cin >> W;
    cout << "Height of image: ";
    cin >> H;

    bool *cells = new bool[W];
    for(uint32_t x=0; x<W; x++) {
        cells[x] = static_cast<bool>(rand() % 2);
    }
    bool *nextCells = new bool[W];
    uint32_t rule;

    cout << "Rule: ";
    cin >> rule;

    Image img{ W, H };
    for(uint32_t x=0; x<W; x++) {
        auto bwConv = [](bool x) -> uint8_t {
            if(x) return 255U;
            return 0U;
        };
        img.values[0][3*x]   = bwConv(cells[x]);
        img.values[0][3*x+1] = bwConv(cells[x]);
        img.values[0][3*x+2] = bwConv(cells[x]);
    }
    for(uint32_t y=1; y<H; y++) {
        calculate(cells, nextCells, W, rule);
        for(uint32_t x=0; x<W; x++) {
            auto bwConv = [](bool x) -> uint8_t {
                if(x) return 255U;
                return 0U;
            };
            img.values[y][3*x]   = bwConv(nextCells[x]);
            img.values[y][3*x+1] = bwConv(nextCells[x]);
            img.values[y][3*x+2] = bwConv(nextCells[x]);
        }
        bool *tmp = nextCells;
        nextCells = cells;
        cells = tmp;
    }
    img.write("output.bmp");
}
