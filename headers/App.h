//
// Created by Lukasz on 09.07.2022.
//

#ifndef NUMBER_RECOGNITION_APP_H
#define NUMBER_RECOGNITION_APP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

#include "Button.h"

using namespace sf;

struct PaddingStruct {
    Uint32 top;
    Uint32 bottom;
    Uint32 left;
    Uint32 right;

    PaddingStruct(Uint32 top, Uint32 bottom, Uint32 left, Uint32 right) {
        this->top = top;
        this->bottom = bottom;
        this->left = left;
        this->right = right;
    }
};

class App {
public:
    App(const std::string &name, Uint32 pixel_count_x, Uint32 pixel_count_y, Uint32 pixel_size_x, Uint32 pixel_size_y);
    ~App();

    void run();

    void add_tick(void (*func)());
private:
    RenderWindow* window;
    Thread* renderThread;
    Event event{};
    Text* predictText;
    Font* font;
    Button* predictButton;

    const Uint32 PIXELS_COUNT_X;
    const Uint32 PIXELS_COUNT_Y;

    const Uint32 PIXEL_SIZE_X;
    const Uint32 PIXEL_SIZE_Y;

    PaddingStruct* paddings;

    float** bigPixels;

    std::vector<void (*)()> tickFunctions;

    void renderFunc();
    bool mouseOnWindow(Vector2i mousePosition);
    void predictRequest();
    void setPixelValue(Uint32 x, Uint32 y, float value);

    void onPredictButtonClick();
};


#endif //NUMBER_RECOGNITION_APP_H
