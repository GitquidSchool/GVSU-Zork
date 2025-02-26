#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <string>
#include <functional>
#include "Location.h"
#include "Player.h"

class Game {
private:
    Player player;
    std::vector<Location> locations;
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
    int required_calories;
    bool in_progress;

    void setup_commands();
    void create_world();
    Location* random_location();
    void game_loop();

    // Command functions
    void show_help(std::vector<std::string> args);
    void talk(std::vector<std::string> args);
    void meet(std::vector<std::string> args);
    void take(std::vector<std::string> args);
    void give(std::vector<std::string> args);
    void go(std::vector<std::string> args);
    void show_items(std::vector<std::string> args);
    void look(std::vector<std::string> args);
    void quit(std::vector<std::string> args);
    void custom_command_1(std::vector<std::string> args); // Placeholder
    void custom_command_2(std::vector<std::string> args); // Placeholder

public:
    Game();
    void start();
};

#endif