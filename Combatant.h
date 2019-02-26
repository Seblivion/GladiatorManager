// Combatant.h
#ifndef COMBAT_H_G
#define COMBAT_H_G

#include <string>
#include <vector>
#include <cstdlib> // Srand has to be called in the main function once, with some seed depending on time.
#include <sstream> //need this in serialize/deserialize
#include <limits>  //need this in serialize/deserialize
#include <algorithm>

class Combatant
{
    
public:
    // Constructors
    Combatant();
    Combatant(std::string fname,
	      std::string lname,
	      unsigned int hp,
	      unsigned int mhp,
	      unsigned int str,
	      unsigned int agi,
	      unsigned int dmg,
	      unsigned int val);
    Combatant(std::vector<std::string> flist,
	      std::vector<std::string> llist); // Random Character generator, terrible randomness
    Combatant(std::vector<std::string> flist,
	      std::vector<std::string> llist, int start_val); // Now with option to decide it's value!


    // Misc. functions
    unsigned int do_damage(Combatant &Target);
    unsigned int calc_value() const;
    void train();

    // Save functions
    std::string serialize() const;
    void deserialize(std::string str);
    
    // Get
    std::string get_first_name() const;
    std::string get_last_name() const;
    unsigned int get_hit_points() const;
    unsigned int get_max_hit_points() const;
    unsigned int get_strength() const;
    unsigned int get_agility() const;
    unsigned int get_damage() const;
    int get_value() const;
    
    // Set
    void set_first_name (std::string const &fname);
    void set_last_name (std::string const &lname);
    void set_hit_points (unsigned int const & hp);
    void set_max_hit_points (unsigned int const & mhp);
    void set_strength (unsigned int const & str);
    void set_agility (unsigned int const & agi);
    void set_damage (unsigned int const & dmg);
    void set_value (unsigned int const & val);
    
    // Operators
    bool operator==(Combatant const &other) const;
    bool operator!=(Combatant const &other) const;


    protected:
    std::string first_name;
    std::string last_name;
    unsigned int hit_points;
    unsigned int max_hit_points;
    unsigned int strength;
    unsigned int agility;
    unsigned int damage;
    unsigned int value;
    
};

#endif
