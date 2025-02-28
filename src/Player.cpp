#include "Player.h"
#include <iostream>

Player::Player() : current_location(nullptr), carried_weight(0.0f) {} 

Location* Player::get_current_location() const {
    return current_location;
}

Item* Player::find_item(const std::string& name) {
    for (auto& item : inventory) {
        if (item.get_name() == name) {
            return &item;
        }
    }
    return nullptr;
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

void Player::add_weight(float weight) {
    carried_weight += weight;
}

void Player::remove_item(const std::string& name) {
    for (auto item = inventory.begin(); item != inventory.end();) { // iterate through player inventory
        if (item->get_name() == name ) {
            item = inventory.erase(item);
        } else {
            ++item;
        }
    }
}