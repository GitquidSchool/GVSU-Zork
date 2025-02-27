#include "Location.h"
#include <stdexcept>

// Constructor for the Location class
Location::Location(std::string name, std::string description) {
    // Check if the name or description is empty and throw an exception if they are
    if (name.empty()) {
        throw std::invalid_argument("Location name cannot be empty.");
    }
    if (description.empty()) {
        throw std::invalid_argument("Location description cannot be empty.");
    }
    this->name = name;
    this->description = description;
    this->visited = false;
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

// Add an NPC to the location
void Location::add_npc(NPC npc) {
    npcs.push_back(npc);
}

// Add an item to the location
void Location::add_item(Item item) {
    items.push_back(item);
}

void Location::add_location(std::string direction, Location* location) {
    if (direction.empty()) {
        throw std::invalid_argument("Direction cannot be empty.");
    }
    // No longer checking for duplicate directions since multimap allows it
    neighbors.insert({direction, location});
}

// Mark visited
void Location::set_visited() {
    visited = true;
}

// Check if visited
bool Location::get_visited() const {
    return visited;
}

// Overloaded stream operator to format location details
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << " - " << location.description << "\n";
    
    os << "You see the following NPCs:\n";
    for (const auto& npc : location.npcs) {
        os << "- " << npc.get_name() << "\n";
    }
    
    os << "You see the following Items:\n";
    for (const auto& item : location.items) {
        os << "- " << item << "\n";
    }
    
    //CHATGPT ASSISTED
    os << "You can go in the following Directions:\n";
    for (const auto& pair : location.neighbors) {
        std::string status = pair.second->get_visited() ? pair.second->get_name() + " (Visited)" : "Unknown";
        os << "- " << pair.first << " - " << status << "\n";
    }
    return os;
}

// finds Npcs in current location
NPC* Location::find_npc(const std::string& name) {
    for (auto& npc : npcs) {
        if (npc.get_name() == name) {
            return &npc;
        }
    }
    return nullptr; // no npc found
}

// finds items in current location
Item* Location::find_item(const std::string& name) {
    for (auto& item : items) {
        if (item.get_name() == name) {
            return &item;
        }
    }
    return nullptr; // no item found
}