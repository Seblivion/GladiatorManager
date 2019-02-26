#include "screen.h"


Screen::Screen(std::vector<sf::Texture> &button_textures, std::vector<sf::Texture> &background_textures,
               std::vector<sf::SoundBuffer> &sound_buffers, sf::Sound &sound,
               sf::Font &font, sf::Vector2f &windowSize) {
    this->button_textures = button_textures;
    this->background_textures = background_textures;
    this->sound_buffers = sound_buffers;
    this->sound = sound;
    this->font = font;
    this->windowSize = windowSize;
}

void Screen::draw_screen(sf::RenderWindow &window) {

    // Draw all sprites.
    std::for_each(sprites.begin(), sprites.end(), [&window](sf::Sprite &n){
        window.draw(n);
    });

    // Draw all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&window](Button &n){
        window.draw(n.get_sprite());
        window.draw(n.get_text());
    });

    // Draw all texts.
    std::for_each(texts.begin(), texts.end(), [&window](sf::Text &n){
        window.draw(n);
    });
}

void Screen::change_released_buttons() {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [](Button &n){
        if(n.get_current() == true) {
            // Change texture state of button.
            n.change_state();
        }
    });
}

// ************************** Create main menu window. **************************
void Screen::create_menu(const int id) {

    // ********************** Buttons **********************
    // Button 1
    sf::Vector2f button1_pos(windowSize.x/2, windowSize.y/3);

    Button button1(button_textures[0], button_textures[1], "New game", font, button1_pos, 30, 1, 1, 0);

    buttons.push_back(button1);

    // Button 2
    sf::Vector2f button2_pos(windowSize.x/2, windowSize.y/2);

    Button button2(button_textures[0], button_textures[1], "Load game", font, button2_pos, 30, 1, 1, 1);

    buttons.push_back(button2);

    // Button 3
    sf::Vector2f button3_pos(windowSize.x/2, windowSize.y/1.5);

    Button button3(button_textures[0], button_textures[1], "Quit", font, button3_pos, 30, 1, 1, 2);

    buttons.push_back(button3);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[0]);

    sprites.push_back(main_sprite);

    // ********************** Text **********************
    // Add text.
    sf::Text welcome;
    welcome.setFont(font);
    welcome.setStyle(sf::Text::Bold);
    welcome.setColor(sf::Color::Black);
    welcome.setString("Gladiator Manager");
    welcome.setPosition(sf::Vector2f(windowSize.x/6, windowSize.y/6));
    texts.push_back(welcome);

    sf::Text sub_title;
    sub_title.setFont(font);
    sub_title.setStyle(sf::Text::Bold);
    sub_title.setColor(sf::Color::Black);
    sub_title.setString("Earn your living");
    sub_title.setPosition(sf::Vector2f(windowSize.x/4, windowSize.y/4));
    texts.push_back(sub_title);

    // Set cnt.
    this->id = id;
}

void Screen::update_menu(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen>> &screen_vec,
                                std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen, &quit, &restart, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();
            // Check which button that was clicked.
            // If New game:
            if(n.get_cnt() == 0) {
                // Enter team window.
                curr_screen = screen_vec[1];
            }
            // If Load game:
            else if(n.get_cnt() == 1) {
                // Load function and then enter the Team window. LOAD!!!
                mecha.load();
                // Set money for both screens.
                std::string money_str = "Gold: ";
                money_str += std::to_string(mecha.get_money());
                screen_vec[1]->texts[2].setString(money_str);
                screen_vec[2]->texts[2].setString(money_str);

                // Set the roster from what was loaded.

                // Update team roster.
                for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                    Combatant tmp = mecha.get_team_combatant(x);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value()) + ".";

                    screen_vec[1]->buttons[x].set_text(gladiator_str);
                }

                // Reset selected gladiator.
                if(screen_vec[1]->buttons[0].get_text_str() != "No combatant.") {
                    Combatant tmp = mecha.get_team_combatant(0);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value()) + ".";

                    screen_vec[1]->texts[3].setString(gladiator_str);
                }
                else {
                    screen_vec[1]->texts[3].setColor(sf::Color::Red);
                    screen_vec[1]->texts[3].setString("No combatant selected.");
                }

                // Enter team window.
                curr_screen = screen_vec[1];
            }
            // If Exit:
            else if(n.get_cnt() == 2) {
                restart = false;
                quit = true;
            }
        }
    });
}

// ************************** Create team window. **************************
void Screen::create_team(Mechanics &mecha, const int id) {

    // Generates random opponent for the first fight.
    mecha.generate_arena_opponent();

    // ********************** Buttons **********************
    // Combatants owned by the player.
    int y = 100;
    for(unsigned int x{0}; x < 4; ++x) {

        sf::Vector2f button_pos(windowSize.x/20, 0 + y);
        y += 50;

        Button button(button_textures[2], button_textures[3], "No combatant.", font, button_pos, 20, 1, 1, x);
        buttons.push_back(button);
    }

    // Buttons to other screens.
    // Market.
    sf::Vector2f market_b_pos(windowSize.x/10, windowSize.y/1.2);

    Button market_b(button_textures[0], button_textures[1], "Market", font, market_b_pos, 30, 1, 1, 4);

    buttons.push_back(market_b);

    // Combat.
    sf::Vector2f combat_b_pos(windowSize.x/2, windowSize.y/1.2);

    Button combat_b(button_textures[0], button_textures[1], "Arena", font, combat_b_pos, 30, 1, 1, 5);

    buttons.push_back(combat_b);

    // Sell.
    sf::Vector2f buy_b_pos(windowSize.x/10, windowSize.y/1.4);

    Button buy_b(button_textures[0], button_textures[1], "Sell", font, buy_b_pos, 30, 1, 1, 6);

    buttons.push_back(buy_b);

    // Bribe.
    sf::Vector2f bribe_b_pos(windowSize.x/2, windowSize.y/1.4);

    std::string bribe_str = "Bribe with " + std::to_string(mecha.get_arena_opponent().get_value()/2) + " gold";

    Button bribe_b(button_textures[0], button_textures[1], bribe_str, font, bribe_b_pos, 25, 1, 1, 7);

    buttons.push_back(bribe_b);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[0]);

    sprites.push_back(main_sprite);

    // ********************** Text **********************
    // Add title. Index: 0
    sf::Text title;
    title.setFont(font);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Black);
    title.setCharacterSize(30);
    title.setString("Roster");
    title.setPosition(sf::Vector2f(windowSize.x/12, 50));
    texts.push_back(title);

    // Intro. Index: 1
    sf::Text intro;
    intro.setFont(font);
    intro.setStyle(sf::Text::Bold);
    intro.setColor(sf::Color::Black);
    intro.setCharacterSize(25);
    intro.setString("Prepare yourself!");
    intro.setPosition(sf::Vector2f(windowSize.x/4, 50));
    texts.push_back(intro);

    // Displaying how much money you have. Index: 2
    sf::Text denarii;
    denarii.setFont(font);
    denarii.setStyle(sf::Text::Bold);
    denarii.setColor(sf::Color::Black);
    denarii.setCharacterSize(25);
    std::string money_str = "Gold: ";
    // Get money from mechanics.
    money_str += std::to_string(mecha.get_money());
    denarii.setString(money_str);
    denarii.setPosition(sf::Vector2f(windowSize.x/1.5, 50));
    texts.push_back(denarii);

    // Display the current selected combatant. Index: 3
    sf::Text gladiator;
    gladiator.setFont(font);
    gladiator.setStyle(sf::Text::Bold);
    gladiator.setColor(sf::Color::Red);
    gladiator.setCharacterSize(20);
    std::string combatant_str = "No combatant selected.";
    gladiator.setString(combatant_str);
    gladiator.setPosition(sf::Vector2f(windowSize.x/20, windowSize.y/1.8));
    texts.push_back(gladiator);

    // Display opponent's gladiator. Index 4
    sf::Text opponent;
    opponent.setFont(font);
    opponent.setStyle(sf::Text::Bold);
    opponent.setColor(sf::Color::Red);
    opponent.setCharacterSize(20);

    Combatant opp = mecha.get_arena_opponent();
    std::string opponent_str{};
    opponent_str = opp.get_first_name() + " " +
        opp.get_last_name() + ", HP:" +
        std::to_string(opp.get_hit_points()) + "/" +
        std::to_string(opp.get_max_hit_points()) + ", Str:" +
        std::to_string(opp.get_strength()) + ", Agi:" +
        std::to_string(opp.get_agility()) + ", Dmg:" +
        std::to_string(opp.get_damage()) + ", Value:" +
        std::to_string(opp.get_value());

    opponent.setString("Opponent's: " + opponent_str);
    opponent.setPosition(sf::Vector2f(windowSize.x/20, windowSize.y/1.6));
    texts.push_back(opponent);

    // Set cnt.
    this->id = id;
}

void Screen::update_team(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                         std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_team) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen, &sel_comb_team, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();

            // Check which button that was clicked.
            // If some of the gladiators?
            if(n.get_cnt() >= 0 && n.get_cnt() < 4) {
                if(n.get_text_str() != "No combatant.") {
                    // Select and print combatant from market.
                    Combatant tmp = mecha.get_team_combatant(n.get_cnt());
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());

                    texts[3].setColor(sf::Color::Blue);
                    texts[3].setString("Your: " + gladiator_str);

                    sel_comb_team = n.get_cnt();
                }
                else {
                    texts[3].setColor(sf::Color::Red);
                    texts[3].setString("No combatant selected.");
                    sel_comb_team = n.get_cnt();
                }
            }
            // Market button?
            else if(n.get_cnt() == 4) {
                //Change to market screen.
                curr_screen = screen_vec[2];

                // Market open sound. Index 4
                sound.resetBuffer();
                sound.setBuffer(sound_buffers[4]);
                sound.play();
            }
            // Combat button?
            else if(n.get_cnt() == 5) {
                if(buttons[sel_comb_team].get_text_str() != "No combatant.") {

                    // Change to combat screen.
                    curr_screen = screen_vec[3];

                    // Play combat start sound. Index 5
                    sound.resetBuffer();
                    sound.setBuffer(sound_buffers[5]);
                    sound.play();

                    // Decide which combatant that gets to hit first.
                    mecha.select_arena_fighter(sel_comb_team);

                    mecha.set_fastest(); // Agility determines who is fastest and acts first.

                    // Display your and your opponent's gladiator.
                    Combatant tmp1 = mecha.get_team_combatant(sel_comb_team);
                    std::string gladiator_str{};
                    gladiator_str = "Your: " + tmp1.get_first_name() + " " +
                        tmp1.get_last_name() + ", HP:" +
                        std::to_string(tmp1.get_hit_points()) + "/" +
                        std::to_string(tmp1.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp1.get_strength()) + ", Agi:" +
                        std::to_string(tmp1.get_agility()) + ", Dmg:" +
                        std::to_string(tmp1.get_damage()) + ", Value:" +
                        std::to_string(tmp1.get_value());

                    screen_vec[3]->texts[2].setString(gladiator_str);

                    Combatant tmp2 = mecha.get_arena_opponent();
                    gladiator_str = "Opponent's: " + tmp2.get_first_name() + " " +
                        tmp2.get_last_name() + ", HP:" +
                        std::to_string(tmp2.get_hit_points()) + "/" +
                        std::to_string(tmp2.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp2.get_strength()) + ", Agi:" +
                        std::to_string(tmp2.get_agility()) + ", Dmg:" +
                        std::to_string(tmp2.get_damage()) + ", Value:" +
                        std::to_string(tmp2.get_value());

                    screen_vec[3]->texts[3].setString(gladiator_str);
                }
            }
            // Sell button?
            else if(n.get_cnt() == 6) {
                if(buttons[sel_comb_team].get_text_str() != "No combatant.") {

                    mecha.sell_combatant(sel_comb_team);

                    // Play coin sound. Index 0
                    sound.resetBuffer();
                    sound.setBuffer(sound_buffers[0]);
                    sound.play();

                    // Update money.
                    std::string money_str = "Gold: ";
                    money_str += std::to_string(mecha.get_money());
                    // Adjust the money values on the screens.
                    screen_vec[1]->texts[2].setString(money_str);
                    screen_vec[2]->texts[2].setString(money_str);

                    // Reset the team roster.
                    for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                        Combatant tmp = mecha.get_team_combatant(x);
                        std::string gladiator_str{};
                        gladiator_str = tmp.get_first_name() + " " +
                            tmp.get_last_name() + ", HP:" +
                            std::to_string(tmp.get_hit_points()) + "/" +
                            std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                            std::to_string(tmp.get_strength()) + ", Agi:" +
                            std::to_string(tmp.get_agility()) + ", Dmg:" +
                            std::to_string(tmp.get_damage()) + ", Value:" +
                            std::to_string(tmp.get_value());

                        buttons[x].set_text(gladiator_str);
                    }

                    for(unsigned int i{mecha.get_roster_size()}; i < 4; ++i) {
                        buttons[i].set_text("No combatant.");
                    }

                    // Reset selected gladiator.
                    if(buttons[sel_comb_team].get_text_str() != "No combatant.") {
                        Combatant tmp = mecha.get_team_combatant(0);
                        std::string gladiator_str{};
                        gladiator_str = tmp.get_first_name() + " " +
                            tmp.get_last_name() + ", HP:" +
                            std::to_string(tmp.get_hit_points()) + "/" +
                            std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                            std::to_string(tmp.get_strength()) + ", Agi:" +
                            std::to_string(tmp.get_agility()) + ", Dmg:" +
                            std::to_string(tmp.get_damage()) + ", Value:" +
                            std::to_string(tmp.get_value());

                        texts[3].setString("Your: " + gladiator_str);
                    }
                    else {
                        texts[3].setColor(sf::Color::Red);
                        texts[3].setString("No combatant selected.");
                    }
                }
            }
            // Bribe button?
            else if(n.get_cnt() == 7) {
                // Check if you can afford the bribe.
                if(mecha.get_money() >= mecha.get_arena_opponent().get_value()/2) {

                    // Play coin sound. Index 0
                    sound.resetBuffer();
                    sound.setBuffer(sound_buffers[0]);
                    sound.play();

                    // Update money.
                    mecha.set_money(mecha.get_money() - (mecha.get_arena_opponent().get_value() / 2));
                    std::string money_str = "Gold: ";
                    money_str += std::to_string(mecha.get_money());
                    // Adjust the money values on the screens.
                    screen_vec[1]->texts[2].setString(money_str);
                    screen_vec[2]->texts[2].setString(money_str);

                    // New opponent. Has to be nullptr to generate new combatant. Otherwise: segmentation fault.
                    mecha.set_arena_fighter_to_nullptr();
                    mecha.generate_arena_opponent();

                    // Update bribe button text.
                    n.set_text("Bribe with " + std::to_string(mecha.get_arena_opponent().get_value()/2) + " gold");

                    // Display opponent gladiator on roster screen.
                    Combatant opp = mecha.get_arena_opponent();
                    std::string opponent_str{};
                    opponent_str = opp.get_first_name() + " " +
                        opp.get_last_name() + ", HP:" +
                        std::to_string(opp.get_hit_points()) + "/" +
                        std::to_string(opp.get_max_hit_points()) + ", Str:" +
                        std::to_string(opp.get_strength()) + ", Agi:" +
                        std::to_string(opp.get_agility()) + ", Dmg:" +
                        std::to_string(opp.get_damage()) + ", Value:" +
                        std::to_string(opp.get_value());
                    screen_vec[1]->texts[4].setString("Opponent's: " + opponent_str);
                }
            }
        }
    });
}

// ************************** Create market window. **************************
void Screen::create_market(Mechanics &mecha, const int id) {

    // ********************** Buttons **********************
    // Print the market.
    int y = 100;
    for(unsigned int i{0}; i < mecha.get_market_max_combatants(); ++i) {
        // Get combatants for market.
        Combatant tmp = mecha.get_market_combatant(i);
        std::string gladiator_str{};
        gladiator_str = tmp.get_first_name() + " " +
            tmp.get_last_name() + ", HP:" +
            std::to_string(tmp.get_hit_points()) + "/" +
            std::to_string(tmp.get_max_hit_points()) + ", Str:" +
            std::to_string(tmp.get_strength()) + ", Agi:" +
            std::to_string(tmp.get_agility()) + ", Dmg:" +
            std::to_string(tmp.get_damage()) + ", Value:" +
            std::to_string(tmp.get_value());

        // Iterate through team vector.
        sf::Vector2f button_pos(windowSize.x/20, 0 + y);
        y += 50;
        // Here is the name of the combatant inserted. Afterwards also insert the values for the combatant.
        Button button(button_textures[2], button_textures[3], gladiator_str, font, button_pos, 20, 1, 1, i);
        buttons.push_back(button);
    }

    // Team button.
    sf::Vector2f team_b_pos(windowSize.x/10, windowSize.y/1.2);

    Button team_b(button_textures[0], button_textures[1], "Roster", font, team_b_pos, 30, 1, 1, 4);

    buttons.push_back(team_b);

    // Buy button.
    sf::Vector2f buy_b_pos(windowSize.x/2, windowSize.y/1.2);

    Button buy_b(button_textures[0], button_textures[1], "Buy", font, buy_b_pos, 30, 1, 1, 5);

    buttons.push_back(buy_b);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[0]);

    sprites.push_back(main_sprite);

    // ********************** Text **********************
    // Add title. Index: 0
    sf::Text title;
    title.setFont(font);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Black);
    title.setCharacterSize(30);
    title.setString("Market");
    title.setPosition(sf::Vector2f(windowSize.x/12, 50));
    texts.push_back(title);

    // Intro. Index: 1
    sf::Text intro;
    intro.setFont(font);
    intro.setStyle(sf::Text::Bold);
    intro.setColor(sf::Color::Black);
    intro.setCharacterSize(25);
    intro.setString("Fine goods for sale!");
    intro.setPosition(sf::Vector2f(windowSize.x/4, 50));
    texts.push_back(intro);

    // Displaying how much money you have. Index: 2
    sf::Text denarii;
    denarii.setFont(font);
    denarii.setStyle(sf::Text::Bold);
    denarii.setColor(sf::Color::Black);
    denarii.setCharacterSize(25);
    std::string money_str = "Gold: ";
    // Get money from mechanics.
    money_str += std::to_string(mecha.get_money());
    denarii.setString(money_str);
    denarii.setPosition(sf::Vector2f(windowSize.x/1.5, 50));
    texts.push_back(denarii);

    // Display the current selected combatant. Index: 3
    sf::Text gladiator;
    gladiator.setFont(font);
    gladiator.setStyle(sf::Text::Bold);
    gladiator.setColor(sf::Color::Black);
    gladiator.setCharacterSize(20);
    Combatant tmp = mecha.get_market_combatant(0);
    std::string gladiator_str{};
    gladiator_str = tmp.get_first_name() + " " +
        tmp.get_last_name() + ", HP:" +
        std::to_string(tmp.get_hit_points()) + "/" +
        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
        std::to_string(tmp.get_strength()) + ", Agi:" +
        std::to_string(tmp.get_agility()) + ", Dmg:" +
        std::to_string(tmp.get_damage()) + ", Value:" +
        std::to_string(tmp.get_value());

    gladiator.setString(gladiator_str);
    gladiator.setPosition(sf::Vector2f(windowSize.x/8, windowSize.y/1.6));
    texts.push_back(gladiator);

    // Print message if you could buy or not. Index: 4
    sf::Text message;
    message.setFont(font);
    message.setStyle(sf::Text::Bold);
    message.setColor(sf::Color::Black);
    message.setCharacterSize(25);
    message.setString("Select your ware to purchase.");
    message.setPosition(sf::Vector2f(windowSize.x/6, windowSize.y/1.4));
    texts.push_back(message);

    // Set cnt.
    this->id = id;
}

void Screen::update_market(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                           std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_market, unsigned int &sel_comb_team) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen,
                  &sel_comb_market, &sel_comb_team, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();

            // Check which button that was clicked.
            // If some of the gladiators to buy?
            if(n.get_cnt() >= 0 && n.get_cnt() < 4) {
                // Select and print selected combatant from market.
                Combatant tmp = mecha.get_market_combatant(n.get_cnt());
                std::string gladiator_str{};
                gladiator_str = tmp.get_first_name() + " " +
                    tmp.get_last_name() + ", HP:" +
                    std::to_string(tmp.get_hit_points()) + "/" +
                    std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                    std::to_string(tmp.get_strength()) + ", Agi:" +
                    std::to_string(tmp.get_agility()) + ", Dmg:" +
                    std::to_string(tmp.get_damage()) + ", Value:" +
                    std::to_string(tmp.get_value());

                texts[3].setString(gladiator_str);

                sel_comb_market = n.get_cnt();
            }
            // Team button?
            else if(n.get_cnt() == 4) {

                // Reset message text.
                texts[4].setString("Press buy to purchase.");
                texts[4].setColor(sf::Color::Black);

                // Change screen.
                curr_screen = screen_vec[1];

                // Team from market sound. Index 1
                sound.resetBuffer();
                sound.setBuffer(sound_buffers[1]);
                sound.play();

                // Update roster.
                for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                    Combatant tmp = mecha.get_team_combatant(x);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());

                    screen_vec[1]->buttons[x].set_text(gladiator_str);
                }

                // Reset selected gladiator in roster.
                if(screen_vec[1]->buttons[sel_comb_team].get_text_str() != "No combatant.") {
                    Combatant tmp = mecha.get_team_combatant(sel_comb_team);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());

                    screen_vec[1]->texts[3].setColor(sf::Color::Blue);
                    screen_vec[1]->texts[3].setString("Your: " + gladiator_str);
                }
                else {
                    screen_vec[1]->texts[3].setColor(sf::Color::Red);
                    screen_vec[1]->texts[3].setString("No combatant selected.");
                }

            }
            // Buy button?
            else if(n.get_cnt() == 5) {
                bool purchase{false};
                if (mecha.can_buy_combatant(sel_comb_market)) {
                    purchase = true;
                    texts[4].setColor(sf::Color::Green);
                    texts[4].setString("Nice doing business with you.");

                    // Play coin sound. Index 0
                    sound.resetBuffer();
                    sound.setBuffer(sound_buffers[0]);
                    sound.play();
                }
                else {
                    texts[4].setColor(sf::Color::Red);
                    texts[4].setString("Away with you!");
                }
                if(purchase = true) {
                    mecha.buy_combatant(sel_comb_market);

                    // Update money.
                    std::string money_str = "Gold: ";
                    money_str += std::to_string(mecha.get_money());
                    // Adjust the money values on the screens.
                    screen_vec[2]->texts[2].setString(money_str);
                    screen_vec[1]->texts[2].setString(money_str);

                    // Change button texts.
                    for(unsigned int i{0}; i < mecha.get_market_max_combatants(); ++i) {
                        // Get combatants for market.
                        Combatant tmp = mecha.get_market_combatant(i);
                        std::string gladiator_str{};
                        gladiator_str = tmp.get_first_name() + " " +
                            tmp.get_last_name() + ", HP:" +
                            std::to_string(tmp.get_hit_points()) + "/" +
                            std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                            std::to_string(tmp.get_strength()) + ", Agi:" +
                            std::to_string(tmp.get_agility()) + ", Dmg:" +
                            std::to_string(tmp.get_damage()) + ", Value:" +
                            std::to_string(tmp.get_value());

                        buttons[i].set_text(gladiator_str);
                    }

                    // Reset the selected gladiator in market after buying.
                    Combatant tmp = mecha.get_market_combatant(sel_comb_market);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());

                    texts[3].setString(gladiator_str);

                }
            }
        }
    });
}

// ************************** Create combat window. **************************
void Screen::create_combat(Mechanics &mecha, const int id) {

    // ********************** Buttons **********************
    // Step the fighting log. Fight! When fight is over it turns to a roster button.
    sf::Vector2f fight_b_pos(windowSize.x/2, windowSize.y/1.2);

    Button fight_b(button_textures[0], button_textures[1], "Fight!", font, fight_b_pos, 30, 1, 1, 0);

    buttons.push_back(fight_b);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[1]);

    sprites.push_back(main_sprite);

    // ********************** Text **********************
    // Add title. Index 0
    sf::Text title;
    title.setFont(font);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::White);
    title.setCharacterSize(30);
    title.setString("Arena");
    title.setPosition(sf::Vector2f(windowSize.x/12, 50));
    texts.push_back(title);

    // Info about the situation. Index 1
    sf::Text info;
    info.setFont(font);
    info.setStyle(sf::Text::Bold);
    info.setColor(sf::Color::White);
    info.setCharacterSize(25);
    info.setString("The gladiators are fighting!");
    info.setPosition(sf::Vector2f(windowSize.x/6, 100));
    texts.push_back(info);

    // Your gladiator. Index 2
    sf::Text gladiator;
    gladiator.setFont(font);
    gladiator.setStyle(sf::Text::Bold);
    gladiator.setColor(sf::Color::Blue);
    gladiator.setCharacterSize(20);
    gladiator.setString("Your man: ");
    gladiator.setPosition(sf::Vector2f(windowSize.x/20, windowSize.y/1.6));
    texts.push_back(gladiator);

    // Opponent's gladiator. Index 3
    sf::Text opponent;
    opponent.setFont(font);
    opponent.setStyle(sf::Text::Bold);
    opponent.setColor(sf::Color::Red);
    opponent.setCharacterSize(20);
    opponent.setString("Opponent: ");
    opponent.setPosition(sf::Vector2f(windowSize.x/20, windowSize.y/1.4));
    texts.push_back(opponent);

    // Combat log. 10 rows. Index 4 - 13
    unsigned int y{150};
    for(unsigned int i{0}; i < 10; ++i) {
        sf::Text row;
        row.setFont(font);
        row.setStyle(sf::Text::Bold);
        row.setColor(sf::Color::Yellow);
        row.setCharacterSize(18);
        row.setString("");
        row.setPosition(sf::Vector2f(windowSize.x/13, y));
        texts.push_back(row);
        y += 20;
    }
}

void Screen::update_combat(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen>> &screen_vec,
                           std::shared_ptr<Screen> &curr_screen, unsigned int &sel_comb_team, unsigned int combat_log_index) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen, &sel_comb_team,
                  &combat_log_index, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();

            // Check if button should go to roster or not.
            bool roster_button = false;

            // Combat over? Make button lead to roster.
            if(n.get_cnt() == 0 && mecha.is_combat_over() == true) {
                roster_button = true;
            }
            // Fight button? Render log.
            else if(n.get_cnt() == 0) {

                // Execute fight and add text to log.
                mecha.next_combat_step();

                // Move all elements one step down.
                // Beware! The position of the text elements are moved in the vector! Not on the screen!
                sf::Text tmp = texts[13];
                texts.erase(texts.begin() + 13);
                texts.insert(texts.begin() + 4, tmp);

                // Print the log.
                unsigned int x{0};
                for(unsigned int i{0}; i < mecha.get_logs().size(); ++i) {
                    if(x >= 10) {
                        x = 0;
                    }
                    std::string log_row{mecha.get_logs()[combat_log_index]};
                    texts[4 + x].setString(log_row);
                    ++combat_log_index;
                    ++x;
                }

                // Update info on gladiators.
                Combatant tmp1 = mecha.get_team_combatant(sel_comb_team);
                std::string gladiator_str{};
                gladiator_str = "Your: " + tmp1.get_first_name() + " " +
                    tmp1.get_last_name() + ", HP:" +
                    std::to_string(tmp1.get_hit_points()) + "/" +
                    std::to_string(tmp1.get_max_hit_points()) + ", Str:" +
                    std::to_string(tmp1.get_strength()) + ", Agi:" +
                    std::to_string(tmp1.get_agility()) + ", Dmg:" +
                    std::to_string(tmp1.get_damage()) + ", Value:" +
                    std::to_string(tmp1.get_value());
                texts[2].setString(gladiator_str);

                Combatant tmp2 = mecha.get_arena_opponent();
                gladiator_str = "Opponent's: " + tmp2.get_first_name() + " " +
                    tmp2.get_last_name() + ", HP:" +
                    std::to_string(tmp2.get_hit_points()) + "/" +
                    std::to_string(tmp2.get_max_hit_points()) + ", Str:" +
                    std::to_string(tmp2.get_strength()) + ", Agi:" +
                    std::to_string(tmp2.get_agility()) + ", Dmg:" +
                    std::to_string(tmp2.get_damage()) + ", Value:" +
                    std::to_string(tmp2.get_value());
                texts[3].setString(gladiator_str);
            }

            // If roster button and combat is over? - Update roster and combat screens. LEAVE COMBAT SCREEN.
            if(n.get_cnt() == 0 && mecha.is_combat_over() == true && roster_button == true) {

                // Reset button.
                buttons[0].set_text("Fight!");
                sf::Vector2f fight_b_pos(windowSize.x/2, windowSize.y/1.2);
                buttons[0].set_pos(fight_b_pos);
                texts[1].setColor(sf::Color::White);
                texts[1].setString("The gladiators are fighting!");
                // Back to roster menu.
                curr_screen = screen_vec[1];
                // First gladiator will be selected.
                sel_comb_team = 0;

                // Clear combat log.
                mecha.clear_logs(); // This will remove all the text logs in the arena_logs vector.
                combat_log_index = 0;
                // Remake combat log to correct the positions of the text elements. 10 rows. Index 4 - 13.
                texts.erase(texts.begin() + 4, texts.begin() + 14);
                unsigned int y{150};
                for(unsigned int i{0}; i < 10; ++i) {
                    sf::Text row;
                    row.setFont(font);
                    row.setStyle(sf::Text::Bold);
                    row.setColor(sf::Color::Yellow);
                    row.setCharacterSize(18);
                    row.setString("");
                    row.setPosition(sf::Vector2f(windowSize.x/13, y));
                    texts.push_back(row);
                    y += 20;
                }

                if(mecha.get_arena_opponent().get_hit_points() == 0) {
                    // Generates random opponent for next fight if last one is dead.
                    mecha.generate_arena_opponent();

                    // Update bribe button text.
                    screen_vec[1]->buttons[7].set_text("Bribe with " + std::to_string(mecha.get_arena_opponent().get_value()/2) + " gold");
                }

                // Display opponent gladiator on roster screen.
                Combatant opp = mecha.get_arena_opponent();
                std::string opponent_str{};
                opponent_str = opp.get_first_name() + " " +
                    opp.get_last_name() + ", HP:" +
                    std::to_string(opp.get_hit_points()) + "/" +
                    std::to_string(opp.get_max_hit_points()) + ", Str:" +
                    std::to_string(opp.get_strength()) + ", Agi:" +
                    std::to_string(opp.get_agility()) + ", Dmg:" +
                    std::to_string(opp.get_damage()) + ", Value:" +
                    std::to_string(opp.get_value());
                screen_vec[1]->texts[4].setString("Opponent's: " + opponent_str);

                // Update the team roster.
                for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                    Combatant tmp = mecha.get_team_combatant(x);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());
                    screen_vec[1]->buttons[x].set_text(gladiator_str);
                }
                for(unsigned int i{mecha.get_roster_size()}; i < 4; ++i) {
                    screen_vec[1]->buttons[i].set_text("No combatant.");
                }

                // Reset selected gladiator.
                if(screen_vec[1]->buttons[0].get_text_str() != "No combatant.") {
                    Combatant tmp = mecha.get_team_combatant(0);
                    std::string gladiator_str{};
                    gladiator_str = tmp.get_first_name() + " " +
                        tmp.get_last_name() + ", HP:" +
                        std::to_string(tmp.get_hit_points()) + "/" +
                        std::to_string(tmp.get_max_hit_points()) + ", Str:" +
                        std::to_string(tmp.get_strength()) + ", Agi:" +
                        std::to_string(tmp.get_agility()) + ", Dmg:" +
                        std::to_string(tmp.get_damage()) + ", Value:" +
                        std::to_string(tmp.get_value());
                    screen_vec[1]->texts[3].setColor(sf::Color::Blue);
                    screen_vec[1]->texts[3].setString("Your: " + gladiator_str);
                }
                else {
                    screen_vec[1]->texts[3].setColor(sf::Color::Red);
                    screen_vec[1]->texts[3].setString("No combatant selected.");
                }
            }
            // If fight is over: check if player was victorious and if so, add exp. and money. STAY ON COMBAT SCREEN.
            else if(n.get_cnt() == 0 && mecha.is_combat_over() == true && mecha.player_lost() == false) {

                // VICTORY!
                // Info.
                texts[1].setColor(sf::Color::Green);
                texts[1].setString("You are victorious! Glory and gold! Roster gains exp.");

                // Play victory sound. Index 2
                sound.resetBuffer();
                sound.setBuffer(sound_buffers[2]);
                sound.play();

                // Add money.
                unsigned int added{0};
                added = mecha.get_arena_opponent().get_value()/2;
                // The player wins at least 1 gold at all times.
                mecha.set_money(mecha.get_money() + added + 1);
                std::string money_str = "Gold: ";
                money_str += std::to_string(mecha.get_money()); // Get money from mechanics.
                // Adjust the money values on the other screens.
                screen_vec[1]->texts[2].setString(money_str);
                screen_vec[2]->texts[2].setString(money_str);

                // Your gladiators gain experience.
                mecha.train_team();

                // Update HP for combatants in roster. All combatants except the selected will receive full health.
                for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                    // HP is set to full if it tmp isn't the one who fought.
                    if(mecha.get_team_combatant(sel_comb_team) != mecha.get_team_combatant(x)) {
                        mecha.set_hit_points(mecha.get_team_combatant(x).get_max_hit_points(), x);
                    }
                }

                // Change button. New button takes you back to the roster.
                sf::Vector2f fight_b_pos(windowSize.x/10, windowSize.y/1.2);
                buttons[0].set_pos(fight_b_pos);
                buttons[0].set_text("Roster");
            }
            // If fight is over: check if player was defeated and if so, your gladiator is killed.
            else if(n.get_cnt() == 0 && mecha.is_combat_over() == true && mecha.player_lost() == true) {

                // SHAME!
                // Info.
                texts[1].setColor(sf::Color::Red);
                texts[1].setString("A shameful display! You lost! Roster gains exp.");

                // Play defeat sound. Index 3
                sound.resetBuffer();
                sound.setBuffer(sound_buffers[3]);
                sound.play();

                // YOUR GLADIATOR IS DEAD!
                mecha.kill_combatant(sel_comb_team);

                // Your other gladiators gain experience.
                mecha.train_team();

                // Update HP for combatants in roster. All combatants except the dead one will receive full health.
                for(unsigned int x{0}; x < mecha.get_roster_size(); ++x) {
                    mecha.set_hit_points(mecha.get_team_combatant(x).get_max_hit_points(), x);
                }

                // Change button. Takes you back to team roster.
                sf::Vector2f fight_b_pos(windowSize.x/10, windowSize.y/1.2);
                buttons[0].set_pos(fight_b_pos);
                buttons[0].set_text("Roster");
            }
        }
    });
}

// ************************** Create escape menu. **************************
void Screen::create_esc_menu(const int id) {

    // ********************** Buttons **********************
    // Save game.
    sf::Vector2f save_b_pos(windowSize.x/3, windowSize.y/4 - 30);

    Button save_b(button_textures[0], button_textures[1], "Save", font, save_b_pos, 30, 1, 1, 0);

    buttons.push_back(save_b);

    // Restart game.
    sf::Vector2f restart_b_pos(windowSize.x/3, windowSize.y/2 - 30);

    Button restart_b(button_textures[0], button_textures[1], "Restart", font, restart_b_pos, 30, 1, 1, 1);

    buttons.push_back(restart_b);

    // Quit game.
    sf::Vector2f quit_b_pos(windowSize.x/3, windowSize.y - windowSize.y/4 - 30);

    Button quit_b(button_textures[0], button_textures[1], "Quit", font, quit_b_pos, 30, 1, 1, 2);

    buttons.push_back(quit_b);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[0]);

    sprites.push_back(main_sprite);
}

void Screen::update_esc_menu(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                          std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen, &quit, &restart, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();

            // Check which button that was clicked.
            if(n.get_cnt() == 0) {
                // SAVE GAME FUNCTION.
                mecha.save();
            }
            // Restart button.
            else if(n.get_cnt() == 1) {
                quit = true;
            }
            // Quit button.
            else if(n.get_cnt() == 2) {
                restart = false;
                quit = true;
            }
        }
    });
}

// ************************** Create game over window. **************************
void Screen::create_game_over(const int id) {

    // ********************** Buttons **********************
    // Quit game.
    sf::Vector2f quit_b_pos(windowSize.x/3, windowSize.y/2);

    Button quit_b(button_textures[0], button_textures[1], "Quit", font, quit_b_pos, 30, 1, 1, 0);

    buttons.push_back(quit_b);

    // ********************** Sprites **********************
    sf::Sprite main_sprite(background_textures[0]);

    sprites.push_back(main_sprite);

    // ********************** Text **********************
    // Add text. Index 0
    sf::Text title;
    title.setFont(font);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Black);
    title.setString("Congratulations!");
    title.setPosition(sf::Vector2f(windowSize.x/6, windowSize.y/6));
    texts.push_back(title);

    // Info. Index 1
    sf::Text info;
    info.setFont(font);
    info.setStyle(sf::Text::Bold);
    info.setCharacterSize(20);
    info.setColor(sf::Color::Black);
    info.setString("You've achieved massive wealth, glory and honor. Well done.");
    info.setPosition(sf::Vector2f(windowSize.x/8, windowSize.y/4));
    texts.push_back(info);
}

void Screen::update_game_over(Mechanics &mecha, sf::Vector2f &mousePos, std::vector<std::shared_ptr<Screen> > &screen_vec,
                          std::shared_ptr<Screen> &curr_screen, bool &quit, bool &restart) {

    // Iterate through all buttons.
    std::for_each(buttons.begin(), buttons.end(), [&mecha, &mousePos, &screen_vec, &curr_screen, &quit, &restart, this](Button &n){
        if(n.get_sprite().getGlobalBounds().contains(mousePos)) {

            // Change texture state of button.
            n.change_state();

            // Check if quit button was clicked.
            if(n.get_cnt() == 0) {
                // Quit.
                restart = false;
                quit = true;
            }
        }
    });
}

// ID
const unsigned int Screen::get_id() const {
    return id;
}
