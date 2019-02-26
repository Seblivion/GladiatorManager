// Team.h
#ifndef TEAM_H_G
#define TEAM_H_G

#include "Combatant.h"
#include <string>
#include <vector>
#include <algorithm> // For finding purposes
#include <sstream>

class Team
{
public:
    // Constructors
    Team();
    Team(int m, std::vector<Combatant> roster);

    // Misc. functions
    void add_combatant(Combatant const &item);
    void remove_combatant(int const &index);
    void remove_combatant(Combatant const &item); // Remove specific combatant
    int find_combatant_index (Combatant const &item) const;
    void train_team();

    // Save Functions
    std::string serialize() const;
    void deserialize(std::string str);
    
    // Get
    unsigned int get_roster_size() const;
    int get_money() const;
    // Remember, const ref. This does not let you change stuff.
    const Combatant& get_combatant(int const &index) const;
    int get_max_roster() const;


    // Set
    void set_money(int const &m);
    void set_combatant(Combatant const &item, int const &index);
    void set_max_roster(int size);
    void set_hit_points(unsigned int const &hp, int const &index);

protected:

    int money;
    int max_roster;
    std::vector<Combatant> combatant_roster;

};

#endif
