#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

const int PIXELS_COUNT_X = 28;
const int PIXELS_COUNT_Y = 28;

const int PIXEL_SIZE_X = 30;
const int PIXEL_SIZE_Y = 30;

int main() {
    RenderWindow* window = new RenderWindow(VideoMode(PIXELS_COUNT_X * PIXEL_SIZE_X, PIXELS_COUNT_Y * PIXEL_SIZE_Y), "Number Recognition");
    window->setFramerateLimit(60);

    bool bigPixels[PIXELS_COUNT_X][PIXELS_COUNT_Y] = {0};
    RectangleShape** pixels = new RectangleShape*[PIXELS_COUNT_X];

    for(int i = 0; i < PIXELS_COUNT_X; i++){
        pixels[i] = new RectangleShape[PIXELS_COUNT_Y];


        for(int j = 0; j < PIXELS_COUNT_Y; j++){
            pixels[i][j].setSize(Vector2f(PIXEL_SIZE_X, PIXEL_SIZE_Y));
            pixels[i][j].setPosition(i*PIXEL_SIZE_X, j*PIXEL_SIZE_Y);
            pixels[i][j].setFillColor(Color::White);
            pixels[i][j].setOutlineColor(Color::Red);
            pixels[i][j].setOutlineThickness(1);
        }
    }

    while(window->isOpen()){
        Event event;

        while(window->pollEvent(event)){
            if(event.type == Event::Closed)
                window->close();
            if(event.type == Event::MouseButtonPressed){
                int pos_x = Mouse::getPosition(*window).x / PIXEL_SIZE_X;
                int pos_y = Mouse::getPosition(*window).y / PIXEL_SIZE_Y;

                std::cout << pos_x << " " << pos_y << std::endl;

                if(bigPixels[pos_x][pos_y])
                    bigPixels[pos_x][pos_y] = 0;
                else
                    bigPixels[pos_x][pos_y] = 1;
            }
        }

        window->clear(Color::Black);


        for(int i = 0; i < PIXELS_COUNT_X; i++){
            for(int j = 0; j < PIXELS_COUNT_Y; j++){
                if(bigPixels[i][j])
                    pixels[i][j].setFillColor(Color::Black);
                else
                    pixels[i][j].setFillColor(Color::White);

                window->draw(pixels[i][j]);
            }
        }

        window->display();
    }

    delete window;
    delete[] pixels;
    return 0;
}
