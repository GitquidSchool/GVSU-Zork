#include "Player.h"
#include <iostream>

Player::Player() : current_location(nullptr) {}

Location* Player::get_current_location() const {
    return current_location;
}

void Player::set_current_location(Location* location) {
    current_location = location;
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