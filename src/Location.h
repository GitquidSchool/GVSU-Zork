#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "NPC.h"
#include <iostream>

class Location {
    //  variables stored in the Location class:
private:
    std::string name;
    std::string description;
    std::multimap<std::string, Location*> neighbors;
    std::vector<Item> items;
    std::vector<NPC> npcs;
    bool visited;

    //  access to the variables 
public:
    Location(std::string name, std::string description);
    std::string get_name() const;
    std::string get_description() const;
    std::vector<Item> get_items() const;
    std::vector<NPC> get_npcs() const;

    void add_npc(NPC npc);
    void add_item(Item item);
    void add_location(std::string direction, Location* location);
    std::map<std::string, Location*> get_locations() const;

    void set_visited();
    bool get_visited() const;

    // Overloaded stream operator to print location details (ASSISTED BY CHATGPT)
    friend std::ostream& operator<<(std::ostream& os, const Location& location);

    NPC* find_npc(const std::string& name);
};

#endif