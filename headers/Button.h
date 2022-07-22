//
// Created by Lukasz on 10.07.2022.
//

#ifndef NUMBER_RECOGNITION_BUTTON_H
#define NUMBER_RECOGNITION_BUTTON_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Button : public Drawable{
public:

    explicit Button(const std::string& str);
    ~Button() override;

    void setText(const std::string& str);

    void setFillColor(Color color);
    void setBorderColor(Color color);
    void setFaceColor(Color color);

    void setSize(Vector2f size);
    void setPosition(Vector2f position);

    void setFontSize(Uint32 size);

    void draw(RenderTarget& target, RenderStates states) const override;
private:
    Font* font;
    Text* text;
    RectangleShape* background;
};


#endif //NUMBER_RECOGNITION_BUTTON_H
