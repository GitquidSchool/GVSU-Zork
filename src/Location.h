#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "NPC.h"

class Location {
private:
    std::string name;
    std::string description;
    std::map<std::string, Location*> neighbors; // Direction -> Location
    std::vector<Item> items;
    std::vector<NPC> npcs;

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
};

#endif