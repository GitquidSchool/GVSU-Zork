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

std::vector<NPC*> Location::get_npcs() const {
    return npcs;
}

// Add an NPC to the location
void Location::add_npc(NPC* npc) {
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

// Overloaded stream operator to format location details (ASSISTED BY CHATGPT)
std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << " - " << location.description << std::endl << std::endl;
    
    // Display NPCs at location
    if (location.npcs.empty()) {
        os << "You are alone.\n";
    } else {
        os << "You see the following NPCs:\n";
        for (const auto& npc : location.npcs) {
            os << "- " << npc->get_name() << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Display Items at location
    if (location.items.empty()) {
        os << "There are no items here.\n\n";
    } else {
        os << "You see the following Items:\n";
        for (const auto& item : location.items) {
            os << "- " << item << std::endl; 
        }
        std::cout << std::endl;
    }
    
    // Display available directions
    os << "You can go in the following Directions:\n";
    for (const auto& pair : location.neighbors) {
        // - Direction - Location(Visited)/Unknown
        os << "- " << pair.first << " - ";  
        if (pair.second->get_visited()) {
            os << pair.second->get_name() << " (Visited)\n";
        } else {
            os << "Unknown\n";
        }
    }
    return os;
}

// finds Npcs in current location
NPC* Location::find_npc(const std::string& name) {
    for (auto* npc : npcs) {
        if (npc->get_name().find(name) != std::string::npos) { 
            return npc; // Returns NPC if input name found within full name
        }
    }
    return nullptr; // no npc found
}

// finds items in current location
Item* Location::find_item(const std::string& name) {
    for (auto& item : items) { // iterate through location inventory by refrences
        if (item.get_name() == name) {
            return &item;
        }
    }
    return nullptr; // no item found
}

// removes item from current location
void Location::remove_item(const std::string& name) {
    for (auto item = items.begin(); item != items.end();) { // iterate through location inventory
        if (item->get_name() == name ) {
            item = items.erase(item);
        } else {
            ++item;
        }
    }
}