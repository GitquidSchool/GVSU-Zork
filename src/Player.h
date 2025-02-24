#ifndef PLAYER_H
#define PLAYER_H

#include "Location.h"
#include <vector>
#include "Item.h"

class Player {
private:
    Location* current_location;
    std::vector<Item> inventory;
public:
    Player();
    Location* get_current_location() const;
    void set_current_location(Location* location);
    void add_item_to_inventory(Item item);
    void show_inventory() const;
};

#endif