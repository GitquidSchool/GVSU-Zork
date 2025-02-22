#include "Location.h"

// Constructor for the Location class
Location::Location(std::string name, std::string description) {
    // Check if the name or description is empty and throw an exception if they are
    if (name.empty() || description.empty()) {
        throw std::invalid_argument("Location name and description cannot be empty.");
    }
    this->name = name;
    this->description = description;
}

std::string Location::get_name() const {
    return name;
}

std::string Location::get_description() const {
    return description;
}

std::vector<Item> Location::get_items() const { 
    return items;
}

std::vector<NPC> Location::get_npcs() const { 
    return npcs;
}

// add an NPC 
void Location::add_npc(NPC npc) {
    npcs.push_back(npc);
}

// add an item
void Location::add_item(Item item) {
    items.push_back(item);
}

// add a neighboring location 
void Location::add_location(std::string direction, Location* location) {
    // Check if direction is empty or already exists and throw an exception if it is
    if (direction.empty() || neighbors.count(direction)) {
        throw std::invalid_argument("Direction cannot be empty or already exists.");
    }
    // Add neighboring location
    neighbors[direction] = location;
}

std::map<std::string, Location*> Location::get_locations() const {
    return neighbors;
}
