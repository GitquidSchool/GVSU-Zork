#include "Game.h"
#include <iostream>

Game::Game() {
    setup_locations();
}

void Game::setup_locations() {
    // =============================
    // 1. Define Locations
    // =============================
    locations.push_back(Location("The Commons", "A busy dining hall where students grab questionable buffet food and leave behind messy trays.")); 
    locations.push_back(Location("The Field House", "A sports complex with courts, a climbing wall, and athletic facilities.")); 
    locations.push_back(Location("The Recreation Center", "A spacious fitness center with equipment, courts, and locker rooms for all your recreational needs."));
    locations.push_back(Location("Mackinac Hall", "A building with classrooms for math, science, and history, along with computer labs, study rooms, and a snack shop."));
    locations.push_back(Location("Lake Michigan Hall", "A humanities building with classrooms, faculty offices, a store, a food spot, and quiet study areas."));
    locations.push_back(Location("Kindschi Hall", "A sleek science building with labs, classrooms, and lecture halls for STEM students."));
    locations.push_back(Location("Manitou Hall", "A multi-purpose building with classrooms, offices, and student services in a central campus location."));
    locations.push_back(Location("Padnos Hall", "A science-focused building with labs, classrooms, and research spaces for biology, chemistry, and environmental science."));  
    locations.push_back(Location("Kirkoff Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life."));
    locations.push_back(Location("The Forest", "A dark mysterious forest where the magical elf resides."));


    // Store pointers to locations for easy reference
    Location* theCommons = &locations[0]; 
    Location* theFieldHouse = &locations[1];
    Location* theRecreationCenter = &locations[2];
    Location* mackinacHall = &locations[3];
    Location* lakeMichiganHall = &locations[4];
    Location* kindschiHall = &locations[5];
    Location* manitouHall = &locations[6];
    Location* padnosHall = &locations[7];
    Location* kirkoffCenter = &locations[8];
    Location* theForest = &locations[9];

    // =============================
    // 2. Define NPCs
    // =============================
    NPC cashier("Stanley, the Overworked Cashier","A tired student worker who barely acknowledges customers.",
            {"Next.",
             "Swipe your ID.",
             "Enjoy your meal... or don't. I don't care."});
    NPC chef("Chef Marla","A strict cook who takes pride in her mass-produced food.",
            {"If you don't like it, cook for yourself next time.",
            "That lasagna took hours. You better appreciate it.",
            "Take all you want, but don't waste it."});




    NPC npc3("", "", {"", ""});

    // =============================
    // 3. Define Items
    // =============================
    Item clearCup("Clear Plastic Cup", "A sturdy plastic cup with some residue left inside.", 0, 1.5); 
    Item energyBar("Energy Bar", "A small partially unwrapped protein bar left on a bleacher.", 25, 1.0); 
    Item pearSlice("Half-Eaten Pear Slice", "A single Pear slice with a bite taken out. It's starting to brown.", 10, 0.5);
    Item breadRoll("Unfinished Bread Roll", "A soft dinner roll with one bite taken out. Slightly stale but edible.", 45, 2.0);

    // =============================
    // 4. Assign Items & NPCs to Locations
    // =============================
    theCommons->add_item(clearCup);
    theCommons->add_item(energyBar);
    theCommons->add_item(pearSlice);
    theCommons->add_item(breadRoll);
    theCommons->add_npc(cashier);
    theCommons->add_npc(chef);



    // =============================
    // 5. Define Location Connections
    // =============================
    theCommons->add_location("east", theForest);
    theCommons->add_location("west", manitouHall);
    theCommons->add_location("west", padnosHall);


    // =============================
    // 6. Set Player's Starting Location
    // =============================
    player.set_current_location(theForest);
}

void Game::start() {
    std::cout << "Welcome to the game!" << std::endl;
    game_loop();
}

void Game::game_loop() {
    std::cout << "Game loop is running..." << std::endl;
}
