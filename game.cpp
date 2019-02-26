#include "game.h"

Game::Game() {

}

// Executes/runs the game object that has been created.
void Game::run_game(bool &restart) {

    sf::RenderWindow window;
    window.create(sf::VideoMode(windowWidth, windowHeigth), "Gladiator Manager", sf::Style::Titlebar | sf::Style::Close);

    // Font for texts.
    if(!font.loadFromFile("arial.ttf"))
         std::cout << "Issue!" << std::endl;

    // Set up window size from Vector2i to Vector2f.
    sf::Vector2i windowSizei;
    windowSizei.x = windowWidth;
    windowSizei.y = windowHeigth;
    windowSize = static_cast<sf::Vector2f>(windowSizei);

    // Names
    std::ifstream ad_file("adjectives.txt");
    std::ifstream c_file("classes.txt");

    std::vector<std::string> first_names{};
    std::vector<std::string> last_names{};

    // std::copy(InputIt first, InputIt last, OutputIt out)
    // istream_iterator() is an input iterator that reads items from the named file stream.
    // back_inserter() returns an interator that performs "push_back" on the named vector.
    std::copy(std::istream_iterator<std::string>(ad_file), std::istream_iterator<std::string>(), std::back_inserter(first_names));
    std::copy(std::istream_iterator<std::string>(c_file), std::istream_iterator<std::string>(), std::back_inserter(last_names));


    // ********************** Mechanics **********************

    // The game mechanics is implemented through this object.
    // It works and stores team, combatants, market, combat and all related functions.
    Mechanics mecha(first_names, last_names);

    // The combat index is used to print the combat log. The log must know when to stop printing new rows.
    unsigned int combat_log_index(0);
    // Money to start with.
    mecha.set_money(5);
    // Selected combatant in team and market screens.
    unsigned int selected_combatant_team{0};
    unsigned int selected_combatant_market{0};


    // ********************** Load textures **********************
    // Vector button_textures.

    // Screen Button normal. Index 0
    sf::Texture scr_button_normal;
    if (!scr_button_normal.loadFromFile("textures/norm_scr.jpg"))
        std::cerr << "Error loading norm_scr.jpg" << std::endl;
    button_textures.push_back(scr_button_normal);

    // Screen Button clicked. Index 1
    sf::Texture scr_button_clicked;
    if (!scr_button_clicked.loadFromFile("textures/click_scr.jpg"))
        std::cerr << "Error loading click_scr.jpg" << std::endl;
    button_textures.push_back(scr_button_clicked);

    // Select Button normal. Index 2
    sf::Texture sel_button_normal;
    if (!sel_button_normal.loadFromFile("textures/norm_sel.jpg"))
        std::cerr << "Error loading norm_sel.jpg" << std::endl;
    button_textures.push_back(sel_button_normal);

    // Select Button clicked. Index 3
    sf::Texture sel_button_clicked;
    if (!sel_button_clicked.loadFromFile("textures/click_sel.jpg"))
        std::cerr << "Error loading click_sel.jpg" << std::endl;
    button_textures.push_back(sel_button_clicked);

    // Vector background_textures.

    // Menu. Index 0
    sf::Texture menu_texture;
    if(!menu_texture.loadFromFile("textures/background.jpeg"))
         std::cerr << "Error loading background.jpeg" << std::endl;
    background_textures.push_back(menu_texture);

    // Combat menu. Index 1
    sf::Texture combat_texture;
    if(!combat_texture.loadFromFile("textures/combat.jpeg"))
         std::cerr << "Error loading combat.jpeg" << std::endl;
    background_textures.push_back(combat_texture);


    // ********************** Load sounds **********************
    // Vector sound_buffers.

    // Load coin sound. Plays when buying and selling. Index 0
    sf::SoundBuffer coin_buffer;
    if(!coin_buffer.loadFromFile("sounds/coin_on_table.wav"))
         std::cerr << "Error loading coin_on_table.wav" << std::endl;
    sound_buffers.push_back(coin_buffer);

    // Load team from market sound. Index 1
    sf::SoundBuffer team_buffer;
    if(!team_buffer.loadFromFile("sounds/place_your_bets.wav"))
         std::cerr << "Error loading place_your_bets.wav" << std::endl;
    sound_buffers.push_back(team_buffer);

    // Load victory sound. Index 2
    sf::SoundBuffer vic_buffer;
    if(!vic_buffer.loadFromFile("sounds/applause.wav"))
         std::cerr << "Error loading applause.wav" << std::endl;
    sound_buffers.push_back(vic_buffer);

    // Load defeat sound. Plays when fighting starts. Index 3
    sf::SoundBuffer def_buffer;
    if(!def_buffer.loadFromFile("sounds/thunder.wav"))
         std::cerr << "Error loading thunder.wav" << std::endl;
    sound_buffers.push_back(def_buffer);

    // Load market sound. Plays when market opens. Index 4
    sf::SoundBuffer prices_buffer;
    if(!prices_buffer.loadFromFile("sounds/best_prices.wav"))
         std::cerr << "Error loading best_prices.wav" << std::endl;
    sound_buffers.push_back(prices_buffer);

    // Load start combat sound. Plays when fighting starts. Index 5
    sf::SoundBuffer combat_buffer;
    if(!combat_buffer.loadFromFile("sounds/cheering.wav"))
         std::cerr << "Error loading cheering.wav" << std::endl;
    sound_buffers.push_back(combat_buffer);


    // ********************** Create screens **********************
    // Create menu window. Found in screen_vec.
    std::shared_ptr<Screen> menu = std::make_shared<Screen>(button_textures, background_textures,
                                                            sound_buffers, sound, font, windowSize);
    menu->create_menu(0);
    screen_vec.push_back(menu);

    // Create team window.
    std::shared_ptr<Screen> team = std::make_shared<Screen>(button_textures, background_textures,
                                                            sound_buffers, sound, font, windowSize);
    team->create_team(mecha, 1);
    screen_vec.push_back(team);

    // Create market window.
    std::shared_ptr<Screen> market = std::make_shared<Screen>(button_textures, background_textures,
                                                              sound_buffers, sound, font, windowSize);
    market->create_market(mecha, 2);
    screen_vec.push_back(market);

    // Create combat window.
    std::shared_ptr<Screen> combat = std::make_shared<Screen>(button_textures, background_textures,
                                                              sound_buffers, sound, font, windowSize);
    combat->create_combat(mecha, 3);
    screen_vec.push_back(combat);

    // Create escape menu.
    std::shared_ptr<Screen> esc_menu = std::make_shared<Screen>(button_textures, background_textures,
                                                                sound_buffers, sound, font, windowSize);
    esc_menu->create_esc_menu(4);
    screen_vec.push_back(esc_menu);

    // Create game over menu.
    std::shared_ptr<Screen> game_over = std::make_shared<Screen>(button_textures, background_textures,
                                                                sound_buffers, sound, font, windowSize);
    game_over->create_game_over(5);
    screen_vec.push_back(game_over);


    // curr_screen ptr points on menu at the start.
    curr_screen = screen_vec[0];
    // Quit is true when game closes. Note: Bool "restart" is true for restart and false for quit.
    bool quit{false};
    // Event loop. Change window depending on input.
    while (!quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                restart = false;
                quit = true;
                break;
            // The following lines of code must be stay updated with the used screens.
            case sf::Event::MouseButtonPressed:
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    // Convert Vector2i to Vector2f. Must be float when checking global bounds.
                    sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

                    // Menu?
                    if(curr_screen == screen_vec[0]) {
                        curr_screen->update_menu(mecha, mousePositionFloat, screen_vec, curr_screen, quit, restart);
                    }
                    // Team?
                    else if(curr_screen == screen_vec[1]) {
                        curr_screen->update_team(mecha, mousePositionFloat, screen_vec, curr_screen, selected_combatant_team);
                    }
                    // Market?
                    else if(curr_screen == screen_vec[2]) {
                        curr_screen->update_market(mecha, mousePositionFloat, screen_vec, curr_screen,
                                                   selected_combatant_market, selected_combatant_team);
                    }
                    // Combat?
                    else if(curr_screen == screen_vec[3]) {
                        curr_screen->update_combat(mecha, mousePositionFloat, screen_vec, curr_screen,
                                                   selected_combatant_team, combat_log_index);
                    }
                    // Escape menu?
                    else if(curr_screen == screen_vec[4]) {
                        curr_screen->update_esc_menu(mecha, mousePositionFloat, screen_vec, curr_screen, quit, restart);
                    }
                    // Game over menu?
                    else if(curr_screen == screen_vec[5]) {
                        curr_screen->update_game_over(mecha, mousePositionFloat, screen_vec, curr_screen, quit, restart);
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                // Buttons change texture when clicked. This functions changes them back to nomral texture.
                curr_screen->change_released_buttons();
                break;
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    if(curr_screen != screen_vec[0] && curr_screen != screen_vec[3] && curr_screen != screen_vec[4]
                            && curr_screen != screen_vec[5]) {
                        curr_screen = screen_vec[4];
                    }
                    else if(curr_screen == screen_vec[4]) {
                        curr_screen = screen_vec[1];
                    }
                }
                break;
            }
        }

        // Check if victory condition is met.
        if(mecha.get_money() >= 100 && !quit) {
            curr_screen = screen_vec[5];
        }

        // Renders a new window after an update.
        window.clear();

        // Draw the objects.
        curr_screen->draw_screen(window);

        // Display universe.
        window.display();
    }
}

