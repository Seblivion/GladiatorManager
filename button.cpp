#include "button.h"

Button::Button(sf::Texture & normal_texture, sf::Texture & clicked_texture, std::string words, sf::Font & font,
               sf::Vector2f location, int font_size, float x_scale, float y_scale, int cnt) {
    this->normal.setTexture(normal_texture);
    this->clicked.setTexture(clicked_texture);

    this->normal.setPosition(location);
    this->clicked.setPosition(location);

    this->normal.setScale(x_scale, y_scale);
    this->clicked.setScale(x_scale, y_scale);

    current = false;

    curr_spr = std::make_shared<sf::Sprite>(this->normal);

    atext_str = words;

    // Add text.
    atext.setFont(font);
    atext.setStyle(sf::Text::Bold);
    atext.setColor(sf::Color::White);
    atext.setCharacterSize(font_size);
    atext.setString(words);
    atext.setPosition(sf::Vector2f(location.x + 10, location.y + curr_spr->getGlobalBounds().height/10));

    // Set cnt.
    this->cnt = cnt;
}

void Button::change_state() {
    set_state(!current);
}


// *************** Set ***************

void Button::set_state(bool which) {
    current = which;
    if(current) {
        curr_spr = std::make_shared<sf::Sprite>(this->clicked);
        return;
    }
    curr_spr = std::make_shared<sf::Sprite>(this->normal);
}

void Button::set_text(std::string words) {
    atext_str = words;
    atext.setString(words);
}

void Button::set_pos(sf::Vector2f location) {
    normal.setPosition(location);
    clicked.setPosition(location);
    atext.setPosition(sf::Vector2f(location.x + 10, location.y + curr_spr->getGlobalBounds().height/10));
}


// *************** Get ***************

const sf::Sprite &Button::get_sprite() const {
    return *curr_spr;
}

const sf::Text &Button::get_text() const {
    return atext;
}

const std::string &Button::get_text_str() const {
    return atext_str;
}

const unsigned int &Button::get_cnt() const {
    return cnt;
}

const bool &Button::get_current() const {
    return current;
}
