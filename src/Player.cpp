#include "Player.h"
#include <iostream>

/**
 * Ethan Umana: 3/2/2025
 * Vincent Nguyen: 3/2/2025
 */

Player::Player() : current_location(nullptr), carried_weight(0.0f) {} 

Location* Player::get_current_location() const {
    return current_location;
}

// finds items in player inventory
Item* Player::find_item(const std::string& name) {
    Item* best_match = nullptr;

    for (auto& item : inventory) {  // Iterate through iventory
        std::string item_name_lower = item.get_name();
        for (char& c : item_name_lower) c = std::tolower(c);

        std::string search_lower = name;
        for (char& c : search_lower) c = std::tolower(c);

        if (item_name_lower.rfind(search_lower, 0) == 0) {
            return &item;  // return prefix match
        }

        // Store first partial but keep looking for exact
        if (item_name_lower.find(search_lower) != std::string::npos && !best_match) {
            best_match = &item;
        }
    }
    return best_match;  //  Return best match (exact first, partial if no exact match)
}

void Player::set_current_location(Location* location) {
    current_location = location;
}

float Player::get_weight() const {
    return carried_weight; 
}

void Player::add_item_to_inventory(Item item) {
    inventory.push_back(item);
}

void Player::show_inventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
        return;
    }
    std::cout << "You are carrying the following items:" << std::endl;
    for (const auto& item : inventory) {
         std::cout << "- " << item << std::endl;
    }
}

std::vector<Item>& Player::get_inventory() {
    return inventory;
}

void Player::add_weight(float weight) {
    carried_weight += weight;
}

// removes item from player inventory
void Player::remove_item_from_inventory(const std::string& name) {
    for (auto iterate = inventory.begin(); iterate != inventory.end();) {  // Iterate through inventory
        std::string item_name_lower = iterate->get_name();
        for (char& c : item_name_lower) c = std::tolower(c);
        
        std::string search_lower = name;
        for (char& c : search_lower) c = std::tolower(c);

        if (item_name_lower == search_lower) {  // Ensure match before removing
            iterate = inventory.erase(iterate);
            return;  // Stop after removing match
        } else {
            ++iterate;
        }
    }
}