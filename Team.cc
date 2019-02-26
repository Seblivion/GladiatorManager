// Team.cc
#include "Team.h"

Team::Team():
    money(0),
    max_roster(4),
    combatant_roster() {
    // Empty team
}

Team::Team(int m, std::vector<Combatant> roster):
    money(m),
    max_roster(4), // Hardcoded, because graphics interface
    combatant_roster(roster) {
    // Loading existing team
    }

// Misc. functions
void Team::add_combatant(Combatant const &item) {
    combatant_roster.push_back(item);
}

void Team::remove_combatant(int const &index) {
    combatant_roster.erase(combatant_roster.begin() + index);
}

void Team::remove_combatant(Combatant const &item) {
    for (auto it = combatant_roster.begin(); it != combatant_roster.end(); ++it)
    {
	if (*it == item) { // Found the target
	    combatant_roster.erase(it);
	}
    } // Either it is gone now, or it was never there to begin with, so guaranteed it cannot be found now.
}

int Team::find_combatant_index(Combatant const &item) const {
    return (std::find(combatant_roster.begin(), combatant_roster.end(), item) - combatant_roster.begin());
}


void Team::train_team() {
    for (auto i = combatant_roster.begin(); i != combatant_roster.end(); ++i) {
        i->train();
    }
}

// Save Functions
std::string Team::serialize() const
{
  std::string str{"\n{\nmoney=" + std::to_string(money) + "\n"};
  for(Combatant comb : combatant_roster)
    str +="COMBATANT:" + comb.serialize() + "\n";
  str += "}";
  return str;
}

void Team::deserialize(std::string str)
{
  std::istringstream iss(str);
  iss.ignore(std::numeric_limits<std::streamsize>::max(), '=');
  iss >> money;
  
  std::string tmp;
  iss >> tmp;
  for(int i{0}; tmp != "}"; i++)
    {
      tmp = tmp.substr(10);
      combatant_roster.emplace_back();
      combatant_roster[i].deserialize(tmp);
      iss >> tmp;
    }
}

// Get
unsigned int Team::get_roster_size() const {
    return combatant_roster.size();
}

int Team::get_money() const {
    return money;
}

const Combatant &Team::get_combatant(const int &index) const {
    return combatant_roster.at(index);
}

int Team::get_max_roster() const {
    return max_roster;
}

// Set
void Team::set_money(int const &m) {
    money = m;
}

void Team::set_combatant(Combatant const &item, int const &index) {
    combatant_roster.at(index) = item;
}

void Team::set_max_roster(int size) {
    max_roster = size;
}

void Team::set_hit_points(const unsigned int &hp, int const &index) {
    combatant_roster[index].set_hit_points(hp);
}
