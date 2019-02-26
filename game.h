#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "screen.h"
#include "Mechanics.h"
#include "storage.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> // For debugging.
#include <vector>
#include <memory>   // For shared_ptr.
#include <fstream>
#include <iterator>

/* Game
 * Game makes up the executive loop of the program.
 */
class Game
{
public:
    // Creates the object that makes up the game.
    Game();
    ~Game(){}

    // Executes/runs the game object that has been created.
    void run_game(bool &restart);

protected:
    // Window width and heigth.
    unsigned windowWidth = 1000;
    unsigned windowHeigth = 600;
    // Size of window.
    sf::Vector2f windowSize;

    // Current open window. Starts with main menu.
    std::shared_ptr<Screen> curr_screen = nullptr;

    // Vector with every window in the game.
    std::vector<std::shared_ptr<Screen>> screen_vec;

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

#endif // GAME_H
