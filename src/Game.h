#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Location.h"
#include "Player.h"

class Game {
private:
    Player player;
    std::vector<Location> locations;
    void setup_locations();
    void game_loop();
public:
    Game();
    void start();
};

#endif