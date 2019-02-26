// Mechanics.h
#ifndef MECH_H_G
#define MECH_H_G

#include "Market.h"
#include "Team.h"
#include "Combatant.h"
#include "storage.h"
#include <vector>
#include <string>
#include <memory>


// The purpose of this class is to let the Game class have something easier to work with

class Mechanics
{
public:
    Mechanics();
    Mechanics(std::vector<std::string> fname, std::vector<std::string> lname);

    // Functions for easy management!
    bool can_buy_combatant(int const &index) const;
    void buy_combatant(int const &index);
    void sell_combatant(int const &index);
    void select_arena_fighter(int const &index);
    void generate_arena_opponent();
    void clear_logs();
    void next_combat_step();
    bool is_combat_over() const;
    void train_team();
    bool player_lost() const;
    void kill_combatant(int const &index);
    void set_fastest();
    void save();
    void load();


    // Get
    const std::vector<std::string>& get_logs() const;
    const Combatant& get_arena_opponent() const;

    // Market
    const Combatant& get_market_combatant(int const &index) const;
    unsigned int get_market_max_combatants() const;

    // Team
    unsigned int get_roster_size() const;
    int get_money() const;
    const Combatant& get_team_combatant(int const &index) const;

    // Get Team object.
    const Team& get_team() const;

    // Set
    // Market
    void set_market_combatant(Combatant const &item, int const &index);

    // Team
    void set_money(int const &m);
    void set_combatant(Combatant const &item, int const &index);
    void set_hit_points(unsigned int const &hp, int const &index);

    // Arena fighter
    void set_arena_fighter_to_nullptr();

protected:
    Team player_team;
    Market bazaar;
    std::vector<std::string> first_name;
    std::vector<std::string> last_name;
    std::shared_ptr<Combatant> arena_fighter;
    Combatant arena_opponent; // Should this also be a shared ptr? Not really needed for base requirements I think
    std::vector<std::string> combat_logs;
    int turn_tracker; // 0 for player turn, 1 for opponent turn
    int arena_index; // This is for setting stuff with the arena combatant
    Storage store;
};

#endif
