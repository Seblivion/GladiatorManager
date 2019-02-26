// Combatant.cc
#include "Combatant.h"

Combatant::Combatant(): first_name("Leeroy"),
			last_name("Jenkins"),
            hit_points(100),
            max_hit_points(110),
			strength(5),
            agility(10),
            damage(10),
			value(0) {
    value = calc_value();
}

Combatant::Combatant(std::string fname,
		     std::string lname,
		     unsigned int hp,
		     unsigned int mhp,
		     unsigned int str,
		     unsigned int agi,
		     unsigned int dmg,
		     unsigned int val):
    first_name(fname),
    last_name(lname),
    hit_points(hp),
    max_hit_points(mhp),
    strength(str),
    agility(agi),
    damage(dmg),
    value(val) {
    // Nothing to do here, all assigned!
}

Combatant::Combatant(std::vector<std::string> flist,
		     std::vector<std::string> llist):
    first_name(flist.at(rand() % flist.size())),
    last_name(llist.at(rand() % llist.size())),
    hit_points(50),
    // Max HP can never be 0!
    max_hit_points(50 + (rand() % 50 + 1)),
    // Strength and agility can't be 0. Floating point exception when randomising with rand() % strength/agility otherwise.
    strength(rand() % 5 + 1),
    agility(rand() % 5 + 1),
    damage(rand() % 5 + 1),
    value(0) {
    hit_points = max_hit_points;
    value = calc_value();
}

Combatant::Combatant(std::vector<std::string> flist,
		     std::vector<std::string> llist, int start_val):
    first_name(flist.at(rand() % flist.size())),
    last_name(llist.at(rand() % llist.size())),
    hit_points(50),
    max_hit_points(50),
    strength(0),
    agility(0),
    damage(0),
    value(0) {
    while(value == 0) {
        int tmp = start_val / 4; // Rounded down, this is because value is split between 4 stats
        int rest = start_val % 4; // The remainder
        // Max HP can never be 0!
        set_max_hit_points(tmp * 50 + rand() % 50 + 1);
        // Strength and agility can't be 0.
        set_strength(tmp * 5 + rand() % 5 + 1);
        set_agility(tmp * 5 + rand() % 5 + 1);
        set_damage(tmp * 5 + rand() % 5 + 1);

        // Correct for remainder, if needed. Prioritize Strength > Agility > Hit points
        if (rest == 1) {
        set_strength(get_strength() + 1);
        } else if (rest == 2) {
        set_strength(get_strength() + 1);
        set_agility(get_agility() + 1);
        } else if (rest == 3) {
        set_strength(get_strength() + 1);
        set_agility(get_agility() + 1);
        set_max_hit_points(get_max_hit_points() + 5);
        }
        hit_points = max_hit_points;
        value = calc_value();
    }
}


// Misc. functions
unsigned int Combatant::do_damage(Combatant &Target) {
    // "Damage" is flat dmg and "Strength" is random from 0 to Str. value.
    // Agility makes it possible to dodge an enemy.
    unsigned int dodge_change = std::rand() % Target.get_agility();
    unsigned int hit_change = std::rand() % get_agility();

    unsigned int tmp_dmg{0};
    // Check if dodged.
    if(hit_change < dodge_change) {
        return tmp_dmg;
    }
    else {
        unsigned int random_str_dmg = std::rand() % get_strength();
        tmp_dmg = get_damage() + random_str_dmg;
        unsigned int target_hp{Target.get_hit_points()};
        if (tmp_dmg < target_hp) {
            Target.set_hit_points(target_hp - tmp_dmg);
        }
        else {
            Target.set_hit_points(0); // We're dealing with unsigned ints, let's not overflow.
        }
    }
    return tmp_dmg;
}

unsigned int Combatant::calc_value() const {
    unsigned int answer = 0;
    answer += get_max_hit_points() / 50;
    answer += get_strength() / 5;
    answer += get_agility() / 5;
    answer += get_damage() / 5;
    return answer;
}

void Combatant::train() {
    unsigned int tmp = 1; // These are all because min needs a list, list can't be made with signed AND unsigned ints.
    unsigned int stat_cap = 100;
    unsigned int hp_cap = 500;
    set_max_hit_points(std::min({get_max_hit_points() + tmp*5, hp_cap}));
    // Hit points won't be set to max until player presses combat button.
    set_strength(std::min({get_strength() + tmp, stat_cap}));
    set_agility(std::min({get_agility() + tmp, stat_cap}));
    set_damage(std::min({get_damage() + tmp, stat_cap}));
    set_value(calc_value());
}


// Save functions
std::string Combatant::serialize() const
{
    return "first_name=" + first_name +
           ",last_name=" + last_name +
           ",hit_points=" + std::to_string(hit_points) +
           ",max_hit_points=" + std::to_string(max_hit_points) +
           ",strength=" + std::to_string(strength) +
           ",agility=" + std::to_string(agility) +
           ",damage=" + std::to_string(damage) +
           ",value=" + std::to_string(value);
}

void Combatant::deserialize(std::string str)
{
  std::istringstream iss(str);
  for(int i = 0; i < 8 ; i++)
    {
      iss.ignore(std::numeric_limits<std::streamsize>::max(), '=');
      switch(i)
	{
	case 0:
	  std::getline(iss,first_name, ',');
	  break;
	case 1:
	  std::getline(iss,last_name, ',');
	  break;
	case 2:
	  iss >> hit_points;
	  break;
	case 3:
	  iss >> max_hit_points;
	  break;
	case 4:
	  iss >> strength;
	  break;
	case 5:
	  iss >> agility;
	  break;
	case 6:
	  iss >> damage;
	  break;
	case 7:
	  iss >> value;
	}
    }
}

// Get
std::string Combatant::get_first_name() const {
    return first_name;
}

std::string Combatant::get_last_name() const {
    return last_name;
}

unsigned int Combatant::get_hit_points() const {
    return hit_points;
}

unsigned int Combatant::get_max_hit_points() const {
    return max_hit_points;
}

unsigned int Combatant::get_strength() const {
    return strength;
}

unsigned int Combatant::get_agility() const {
    return agility;
}

unsigned int Combatant::get_damage() const {
    return damage;
}

int Combatant::get_value() const {
    return value;
}

// Set
void Combatant::set_first_name (std::string const &fname) {
    first_name = fname;
}

void Combatant::set_last_name (std::string const &lname) {
    last_name = lname;
}

void Combatant::set_hit_points (unsigned int const & hp) {
    hit_points = hp;
}

void Combatant::set_max_hit_points (unsigned int const & mhp) {
    max_hit_points = mhp;
}

void Combatant::set_strength (unsigned int const & str) {
    strength = str;
}

void Combatant::set_agility (unsigned int const & agi) {
    agility = agi;
}

void Combatant::set_damage (unsigned int const & dmg) {
    damage = dmg;
}

void Combatant::set_value (unsigned int const & val) {
    value = val;
}

// Operators
bool Combatant::operator==(Combatant const &other) const {
    return (
	first_name == other.first_name and
	last_name == other.last_name and
	hit_points == other.hit_points and
	max_hit_points == other.max_hit_points and
	strength == other.strength and
	agility == other.agility and
	damage == other.damage and
	value == other.value);
}

bool Combatant::operator!=(Combatant const &other) const {
    return not (*this == other);
}
