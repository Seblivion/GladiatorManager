#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory> // shared_ptr

/*
 * Button class is for button. :)
 * The button class is the button object that will be used in Screen.
 */
class Button {
public:
    // Contructor. Sets sprites, text and location for button.
    Button(sf::Texture &normal_texture, sf::Texture &clicked_texture, std::string words, sf::Font &font,
           sf::Vector2f location, int font_size, float x_scale, float y_scale, int cnt);
    ~Button(){}

    // A function that checks if the button has been clicked.
    void change_state();

    // *************** Set ***************
    // Changes the button state if it's being clicked.
    void set_state(bool);

    // Change button text.
    void set_text(std::string words);

    // Change button position.
    void set_pos(sf::Vector2f location);

    // *************** Get ***************
    // Get the sprite of the button. To draw the sprite.
    const sf::Sprite &get_sprite() const;

    // Get the text of the button.
    const sf::Text &get_text() const;

    // Get text string. Used to check if button is empty or not.
    const std::string &get_text_str() const;

    // Get the count value to identify button. Used in screen button checks.
    const unsigned int &get_cnt() const;

    // Get boolean value for whether the button was clicked or not.
    const bool &get_current() const;

protected:
    // Sprite for button if not clicked. Use sprite or texture?
    sf::Sprite normal;

    // Sprite for button if clicked.
    sf::Sprite clicked;

    // Sprite that is being showed.
    std::shared_ptr<sf::Sprite> curr_spr = nullptr;

    // Text on button.
    sf::Text atext;

    // Text as string.
    std::string atext_str{};

    // Clicked or not clicked. Clicked = true. Not clicked = false.
    bool current;

    // Button count/id.
    unsigned int cnt{};
};

#endif // BUTTON_H
