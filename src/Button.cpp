//
// Created by Lukasz on 10.07.2022.
//

#include "Button.h"

Button::Button(const std::string& str) {
    font = new Font();
    if(!font->loadFromFile("fonts/Roboto-Light.ttf/Roboto-Light.ttf")){
        std::cout << "Could not load the font" << std::endl;
    }

    text = new Text(str, *font);
    text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height/2);

    background = new RectangleShape();
    background->setSize(Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height));

    text->setPosition(background->getSize().x/2, background->getSize().y/2);
}

Button::~Button() {
    delete text;
    delete font;
    delete background;
}

void Button::setText(const std::string &str) {
    text->setString(str);
}

void Button::setFillColor(Color color) {
    background->setFillColor(color);
}

void Button::setBorderColor(Color color) {

}

void Button::setFaceColor(Color color) {

}

void Button::setPosition(Vector2f position) {
    background->setPosition(position);
    text->setPosition(position);
}

void Button::setSize(Vector2f size) {
    background->setSize(size);
}

void Button::setFontSize(Uint32 size) {

}

void Button::draw(RenderTarget &target, RenderStates states) const {

    target.draw(*background, states);
    target.draw(*text, states);
}
