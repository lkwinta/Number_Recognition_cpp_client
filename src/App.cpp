//
// Created by Lukasz on 09.07.2022.
//

#include "../headers/App.h"

App::App(const std::string &name, Uint32 pixel_count_x, Uint32 pixel_count_y, Uint32 pixel_size_x, Uint32 pixel_size_y) :
        PIXELS_COUNT_X(pixel_count_x), PIXELS_COUNT_Y(pixel_count_y), PIXEL_SIZE_X(pixel_size_x), PIXEL_SIZE_Y(pixel_size_y) {
    paddings = new PaddingStruct(50, 0, 0, 0);

    VideoMode windowSize(PIXELS_COUNT_X * PIXEL_SIZE_X + paddings->right + paddings->left,
                         PIXELS_COUNT_Y * PIXEL_SIZE_Y + paddings->top + paddings->bottom);

    window = new RenderWindow(windowSize, name);
    window->setFramerateLimit(60);
    window->setActive(false);

    font = new Font();
    if(!font->loadFromFile("fonts/Roboto-Light.ttf/Roboto-Light.ttf")){
        std::cout << "Could not load font " << std::endl;
    }

    predictText = new Text("a", *font);
    predictText->setPosition(200 ,10);
    predictText->setFillColor(Color::White);

    predictButton = new Button("Predict");
    predictButton->setPosition(Vector2f(10, 10));
    predictButton->setFillColor(Color::Red);


    bigPixels = new float *[PIXELS_COUNT_X];
    for (int i = 0; i < PIXELS_COUNT_X; i++) {
        bigPixels[i] = new float[PIXELS_COUNT_Y]();
    }

    event = Event();

    renderThread = new Thread(&App::renderFunc, this);
    renderThread->launch();
}

void App::renderFunc() {
    window->setActive(true);

    auto** pixels = new RectangleShape*[PIXELS_COUNT_X];

    for(int i = 0; i < PIXELS_COUNT_X; i++){
        pixels[i] = new RectangleShape[PIXELS_COUNT_Y];

        for(int j = 0; j < PIXELS_COUNT_Y; j++){
            pixels[i][j].setSize(Vector2f((float)PIXEL_SIZE_X, (float)PIXEL_SIZE_Y));
            pixels[i][j].setPosition((float)(i*PIXEL_SIZE_X)+(float)paddings->left, (float)(j*PIXEL_SIZE_Y) + (float)paddings->top);
            pixels[i][j].setFillColor(Color::White);
            pixels[i][j].setOutlineColor(Color::Red);
            pixels[i][j].setOutlineThickness(1);
        }
    }

    while(window->isOpen()){
        window->clear(Color::Black);

        for(int i = 0; i < PIXELS_COUNT_X; i++){
            for(int j = 0; j < PIXELS_COUNT_Y; j++){
                if(bigPixels[i][j] == 0)
                    pixels[i][j].setFillColor(Color::White);
                else {
                    pixels[i][j].setFillColor(Color(255 - Uint8(255 * bigPixels[i][j]), 255 - Uint8(255 * bigPixels[i][j]), 255 - Uint8(255 * bigPixels[i][j])));

                    //std::cout << bigPixels[i][j] << " " << pixels[i][j].getFillColor().r << " " << pixels[i][j].getFillColor().g << " " << pixels[i][j].getFillColor().b << std::endl ;
                }

                window->draw(pixels[i][j]);
            }
        }

        window->draw(*predictText);
        window->draw(*predictButton);

        window->display();
    }

    delete[] pixels;
}

void App::run(){
    while(window->isOpen()){
        while(window->pollEvent(event)){
            if(event.type == Event::Closed)
                window->close();
            if(Mouse::isButtonPressed(Mouse::Button::Left) && mouseOnWindow(Mouse::getPosition(*window))){
                Uint32 pos_x = (Mouse::getPosition(*window).x - paddings->left) / PIXEL_SIZE_X;
                Uint32 pos_y = (Mouse::getPosition(*window).y - paddings->top ) / PIXEL_SIZE_Y;


                //std::cout << Mouse::getPosition(*window).x  << " " << Mouse::getPosition(*window).y << std::endl;
                setPixelValue(pos_x, pos_y, 1);
                setPixelValue(pos_x-1, pos_y, 0.8);
                setPixelValue(pos_x+1, pos_y, 0.8);
                setPixelValue(pos_x, pos_y-1, 0.8);
                setPixelValue(pos_x, pos_y+1, 0.8);
                setPixelValue(pos_x+1, pos_y+1, 0.2);
                setPixelValue(pos_x-1, pos_y-1, 0.2);
                setPixelValue(pos_x-1, pos_y+1, 0.2);
                setPixelValue(pos_x+1, pos_y-1, 0.2);

            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == Keyboard::Enter){
                    predictRequest();
                }
            }

        }

        for(auto func : tickFunctions){
            func();
        }
    }
}

App::~App() {
    delete renderThread;
    delete window;
    delete[] bigPixels;
    delete paddings;
    delete predictText;
    delete font;
}

bool App::mouseOnWindow(Vector2i mousePosition) {
    Vector2<unsigned int> windowSize = window->getSize();

    if( mousePosition.x <  windowSize.x && mousePosition.y <  windowSize.y)
        return true;
    else
        return false;
}

void App::add_tick(void (*func)()) {
    tickFunctions.push_back(func);
}

void App::predictRequest() {
    Http http;
    http.setHost("http://127.0.0.1/", 2222);

    Http::Request request;
    request.setMethod(Http::Request::Post);
    request.setUri("/predict");
    request.setField("Content-Type", "application/json");

    std::string json = "{\n\t\"pixels\" : [\n";

    for(int i = 0; i < PIXELS_COUNT_X; i++){
        json += "\t\t[";
        for(int j = 0; j < PIXELS_COUNT_Y; j++){
            json += (char)(bigPixels[i][j] + 48);
            json += ",";
        }
        json[json.length() - 1] = ' ';
        json += "],\n";
    }
    json[json.length() - 2] = ' ';
    json += "\t]\n}";
    //std::cout << json << std::endl;

    for(int i = 0; i < PIXELS_COUNT_X; i++){
        for(int j = 0; j < PIXELS_COUNT_Y; j++){
            bigPixels[i][j] = false;
        }
    }

    request.setBody(json);

    Http::Response response = http.sendRequest(request);
    //std::cout << response.getBody() << std::endl;
    predictText->setString(response.getBody());
}

void App::setPixelValue(Uint32 x, Uint32 y, float value) {
    if(x < 0 || x >= PIXELS_COUNT_X)
        return;
    if(y < 0 || y >= PIXELS_COUNT_Y)
        return;
    if(bigPixels[x][y] > value)
        return;

    bigPixels[x][y] = value;
}

void App::onPredictButtonClick() {

}
