#ifndef SCREEN_H
#define SCREEN_H

#include "button.h"
#include "Mechanics.h"
#include "storage.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <algorithm>    // For for_each algo.

/* Screen
 * Screen is used to handle every window in the game.
 * It's used to create and update the screens for main menu, team, market, combat, escape menu and victory.
 * It also updates data and mechanics accordingly.
 */
class Screen {
public:
    Screen(std::vector<sf::Texture> &button_textures, std::vector<sf::Texture> &background_textures,
           std::vector<sf::SoundBuffer> &sound_buffers, sf::Sound &sound, sf::Font &font, sf::Vector2f &windowSize);
    ~Screen(){}

    // Function that draws the screen. Used in game for drawing current screen.
    void draw_screen(sf::RenderWindow &window);

    // Change to unclicked sprites when buttons aren't clicked.
    void change_released_buttons();

    // ************************** Create main menu window. **************************
    void create_menu(const int id);

    void update_menu(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                            std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart);

    // ************************** Create team window. **************************
    void create_team(Mechanics &mecha, const int id);

    void update_team(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                            std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_team);

    // ************************** Create market window. **************************
    void create_market(Mechanics &mecha, const int id);

    void update_market(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                              std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_market, unsigned int &sel_comb_team);

    // ************************** Create combat window. **************************
    void create_combat(Mechanics &mecha, const int id);

    void update_combat(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                              std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_team, unsigned int combat_log_index);

    // ************************** Create escape menu window. **************************
    void create_esc_menu(const int id);

    void update_esc_menu(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                              std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart);

    // ************************** Create game over window. **************************
    void create_game_over(const int id);

    void update_game_over(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                              std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart);

    // Get the id value to identify screen.
    const unsigned int get_id() const;

protected:
    // The buttons used. For changing windows, buying, selling, etc.
    std::vector<Button> buttons;

    // Background sprites.
    std::vector<sf::Sprite> sprites;

    // Background texts.
    std::vector<sf::Text> texts;

    // Screen count/id. Used for debugging.
    unsigned int id{};

    // ************* The following are from the Game. Inserted in construction. *************

    // Size of window.
    sf::Vector2f windowSize;

    // FONT FOR ALL TEXTS!
    sf::Font font;

    // Vector with button textures.
    std::vector<sf::Texture> button_textures;

    // Background textures.
    std::vector<sf::Texture> background_textures;

    // Sounds that are played throughout the code. A sound buffer are being sent to a sound to be played.
    std::vector<sf::SoundBuffer> sound_buffers;

    // Sound channel that are played.
    sf::Sound sound;
};

#endif // SCREEN_H
