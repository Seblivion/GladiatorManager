// Mechanics.cc
#include "Mechanics.h"

// Constructors
Mechanics::Mechanics(): 
    player_team(),
    bazaar(),
    first_name(),
    last_name(),
    arena_fighter(),
    arena_opponent(),
    combat_logs(),
    turn_tracker(0),
    arena_index(0) {
    // Nothing much here, just default constructor
}

Mechanics::Mechanics(std::vector<std::string> fname, std::vector<std::string> lname):
    player_team(),
    bazaar(fname, lname),
    first_name(fname),
    last_name(lname),
    arena_fighter(),
    arena_opponent(),
    combat_logs(),
    turn_tracker(0),
    arena_index(0) {
    // Constructor with name lists for random names
}


// Functions for easy management!
bool Mechanics::can_buy_combatant(int const &index) const {
    if ((index >= 0) and (index < Mechanics::get_market_max_combatants()) and (get_roster_size() < player_team.get_max_roster())) {
	return (Mechanics::get_market_combatant(index).get_value() <= Mechanics::get_money());
    }
    else {
	return false; // The combatant index is not in the market, do not buy it.
    }
}

void Mechanics::buy_combatant(int const &index) {
    if (Mechanics::can_buy_combatant(index)) { // Can we afford this combatant?
	if (get_roster_size() < player_team.get_max_roster()) {
	    Combatant tmp = Mechanics::get_market_combatant(index);
	    Mechanics::set_money(Mechanics::get_money() - tmp.get_value());
	    player_team.add_combatant(tmp);
	    bazaar.remove_combatant(index);
        // Never run out of combatants in market, never cost 0 and sometimes cost 1 too much
        bazaar.add_new_combatant(first_name, last_name, 1 + (rand() % std::max<int>({player_team.get_money(), 2})));
	}
    }
}

void Mechanics::sell_combatant(int const &index) {
    if ((index >= 0) and (index < Mechanics::get_roster_size())) {
	Combatant tmp = Mechanics::get_team_combatant(index);
	Mechanics::set_money(Mechanics::get_money() + tmp.get_value());
        player_team.remove_combatant(index);
    }
}

void Mechanics::select_arena_fighter(int const &index) {
    arena_fighter = std::make_shared<Combatant>(Mechanics::get_team_combatant(index));
    arena_index = index;
}

void Mechanics::generate_arena_opponent() {
    if (arena_fighter != nullptr) {
        // Check your highest value combatant and money. The value received will be used to generate opponent.
        int condition_val{0};
        for(unsigned int x{0}; x < get_roster_size(); ++x) {
            if(get_team_combatant(x).get_value() > condition_val) {
                condition_val = get_team_combatant(x).get_value();
            }
            else if(get_money() > condition_val) {
                condition_val = get_money();
            }
        }
        // This will make the opponent be generated around your own level of strength.
        int balance_val = std::rand() % condition_val + (condition_val / 2);
        Combatant tmp{first_name, last_name, balance_val};
        arena_opponent = tmp;
    }
    else {
        Combatant tmp{first_name, last_name};
        arena_opponent = tmp;
    }
}

void Mechanics::clear_logs() {
    combat_logs.clear();
}

void Mechanics::kill_combatant(int const &index) {
    if ((index >= 0) and (index < Mechanics::get_roster_size())) {
        player_team.remove_combatant(index);
    }
}

void Mechanics::next_combat_step() {
    if (arena_fighter != nullptr) {
        if (turn_tracker == 0) {
            // Player turn
            unsigned int dmg_done{arena_fighter->do_damage(arena_opponent)};
            turn_tracker = 1;
            // Check if dodged.
            if(dmg_done == 0) {
                combat_logs.push_back(
                    arena_fighter->get_first_name() + " " + arena_fighter->get_last_name() +
                    "'s attack was dodged by " + arena_opponent.get_first_name() + " " + arena_opponent.get_last_name() + "!"
                );
            }
            else {
                combat_logs.push_back(
                    arena_fighter->get_first_name() + " " + arena_fighter->get_last_name() +
                    " did " + std::to_string(dmg_done) +
                    " damage to " + arena_opponent.get_first_name() + " " + arena_opponent.get_last_name() +
                    " who has " + std::to_string(arena_opponent.get_hit_points()) + " hp left!"
                );
            }
        }
        else {
            // Enemy turn
            unsigned int dmg_done{arena_opponent.do_damage(*arena_fighter)};
            turn_tracker = 0;
            // Check if dodged.
            if(dmg_done == 0) {
                combat_logs.push_back(
                    arena_opponent.get_first_name() + " " + arena_opponent.get_last_name() +
                    "'s attack was dodged by " + arena_fighter->get_first_name() + " " + arena_fighter->get_last_name() + "!"
                );
            }
            else {
                combat_logs.push_back(
                    arena_opponent.get_first_name() + " " + arena_opponent.get_last_name() +
                    " did " + std::to_string(dmg_done) +
                    " damage to " + arena_fighter->get_first_name() + " " + arena_fighter->get_last_name() +
                    " who has " + std::to_string(arena_fighter->get_hit_points()) + " hp left!"
                );
            }
        }
        // Turn if statement
        player_team.set_combatant(*arena_fighter, arena_index); // Update the team with the changes
    } // nullptr if statement
}

bool Mechanics::is_combat_over() const {
    if (arena_fighter != nullptr) {
        if (arena_fighter->get_hit_points() > 0) {
            if (arena_opponent.get_hit_points() > 0) {
                return false;
            }
        }
    }
    return true; // It's only not over if BOTH have hp, otherwise it's over for someone
}

void Mechanics::train_team() {
    player_team.train_team();
}

bool Mechanics::player_lost() const {
    return (arena_fighter->get_hit_points() == 0);
}

void Mechanics::set_fastest() {
    if (arena_fighter->get_agility() >= arena_opponent.get_agility()) {
	turn_tracker = 0;
    } else {
	turn_tracker = 1;
    }
}

void Mechanics::save() {
    store.save(player_team, "PLAYER");
}

void Mechanics::load() {
    store.load(player_team, "PLAYER");
}


// Get
const std::vector<std::string>& Mechanics::get_logs() const{
    return combat_logs;
}

const Combatant& Mechanics::get_arena_opponent() const {
    return arena_opponent;
}

const Combatant& Mechanics::get_market_combatant(int const &index) const {
    return bazaar.get_combatant(index);
}

unsigned int Mechanics::get_market_max_combatants() const {
    return bazaar.get_max_combatants();
}

unsigned int Mechanics::get_roster_size() const {
    return player_team.get_roster_size();
}

int Mechanics::get_money() const {
    return player_team.get_money();
}

const Combatant &Mechanics::get_team_combatant(int const &index) const {
    return player_team.get_combatant(index);
}

const Team& Mechanics::get_team() const {
    return player_team;
}


// Set
void Mechanics::set_market_combatant(Combatant const &item, int const &index) {
    bazaar.set_combatant(item, index);
}

void Mechanics::set_money(int const &m) {
    player_team.set_money(m);
}

void Mechanics::set_combatant(Combatant const &item, int const &index) {
    player_team.set_combatant(item,index);
}

void Mechanics::set_hit_points(const unsigned int &hp, int const &index) {
    player_team.set_hit_points(hp, index);
}

void Mechanics::set_arena_fighter_to_nullptr() {
    arena_fighter = nullptr;
}

