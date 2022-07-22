#include <iostream>
#include <string>

#include <App.h>

using namespace sf;

const int PIXELS_COUNT_X = 28;
const int PIXELS_COUNT_Y = 28;

const int PIXEL_SIZE_X = 15;
const int PIXEL_SIZE_Y = 15;

int main() {
    App app = App("Number Recognition", PIXELS_COUNT_X, PIXELS_COUNT_Y, PIXEL_SIZE_X, PIXEL_SIZE_Y);
    app.run();

    return 0;
}
