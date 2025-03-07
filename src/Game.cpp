#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <set>

/**
 * Ethan Umana: 3/2/2025
 * Vincent Nguyen: 3/2/2025
 */

Game::Game() : required_calories(500), in_progress(true) {
        setup_commands();
        create_world();
}

void Game::setup_commands() {
        commands["help"] = [this](std::vector<std::string> args) { show_help(args); };
        // commands["talk"] = [this](std::vector<std::string> args) { talk(args); };
        commands["meet"] = [this](std::vector<std::string> args) { meet(args); };
        commands["take"] = [this](std::vector<std::string> args) { take(args); };
        commands["give"] = [this](std::vector<std::string> args) { give(args); };
        commands["go"] = [this](std::vector<std::string> args) { go(args); };
        commands["inventory"] = [this](std::vector<std::string> args) { show_items(args); };
        commands["look"] = [this](std::vector<std::string> args) { look(args); };
        commands["quit"] = [this](std::vector<std::string> args) { quit(args); };
        commands["trade"] = [this](std::vector<std::string> args) { trade(args); };
        commands["dance"] = [this](std::vector<std::string> args) { dance(args); };
}

void Game::show_help(std::vector<std::string>) {
        std::time_t current_time = std::time(nullptr); // gets time
        struct tm local_time;
        #ifdef _WIN32
                localtime_s(&local_time, &current_time); // Windows-specific
        #else
                localtime_r(&current_time, &local_time); // POSIX-specific
        #endif

        // format HH:MM and print 
        char time_str[6];  // 5 chars + null terminator
        std::strftime(time_str, sizeof(time_str), "%H:%M", &local_time);
        std::cout << "Current Time: " << time_str << std::endl;
        
        std::cout << "Available commands: " << std::endl;

        // Order of commands
        std::vector<std::string> orderedCommands = 
        {"help", "meet", "take", "give", "inventory", "look", "go", "trade", "dance", "quit"};

        for (const std::string& command : orderedCommands) {
             if (commands.find(command) != commands.end()) {
                 std::cout << "- " << command << std::endl;   
             }
        }
}


void Game::meet(std::vector<std::string> target) {
        if (target.empty()) { // if npc name not provided
            std::cout << "That person isn't here." << std::endl;
            return;
        } 

        Location* current_location = player.get_current_location(); // get current location
        std::string user_input = target[0]; // get typed name

        for (char& c : user_input) c = std::tolower(c); // Convert to compare
        
        // Search for NPC
        for (NPC* npc : current_location->get_npcs()) { 
             std::istringstream iss(npc->get_name());
             std::string first_name;
             iss >> first_name; // Extract first name 

             // Store full name 
             std::string full_name = npc->get_name();

             // Convert to compare
             std::string first_name_lower = first_name;
             for (char& c : first_name_lower) c = std::tolower(c);

             if (first_name_lower == user_input) {
                 std::cout << "You meet " << full_name << ": " << npc->get_description() << std::endl;
                 return;
             }
        }

    std::cout << user_input << " isn't here." << std::endl;
}       
        
void Game::take(std::vector<std::string> target) {
        if (target.empty()){ // if item name not provided
            std::cout << "What item do you want to take?" << std::endl;
            return;
        } 
        
        std::string user_input;
        for (const auto& word : target) { // for loop that grabs all tokens in item
                if (!user_input.empty()) {
                        user_input += " ";
                }
                user_input += word; // puts tokens into one string
        }

        for (char& c : user_input) c = std::tolower(c);

        Location* current_location = player.get_current_location();  // get current location
        Item* matched_item = current_location->find_item(user_input);  // find item in current location
                
        if (matched_item) {  // if item is found
            float new_weight = player.get_weight() + matched_item->get_weight();  // calculate player weight
            if (new_weight > 30.0f) {  // if exceeding weight limit
                std::cout << "You are carrying too much weight to take " << matched_item->get_name() << "." << std::endl;
                return;
            }
        
            Item item_copy = *matched_item;  // copy of item

            current_location->remove_item(matched_item->get_name()); // Remove from location
            player.add_item_to_inventory(item_copy); // Add to inventory
            player.add_weight(item_copy.get_weight()); // Update weight
        
            std::cout << "You took the " << item_copy.get_name() << "." << std::endl;
        } else {
                std::cout << user_input << " is not in this location." << std::endl;
        }
}

void Game::give(std::vector<std::string> target) {
        if (target.empty()){ // if item name not provided
                std::cout << "That item isn't here." << std::endl;
                return;
        } else {
                std::string item_name;
                for (const auto& word : target) { // for loop that grabs all tokens in item
                        if (!item_name.empty()) {
                                item_name += " ";
                        }
                        item_name += word; // puts tokens into one string
                }
                for (char& c : item_name) c = std::tolower(c);  // Convert to Compare

                Location* current_location = player.get_current_location(); // get current location
                Item* matched_item = player.find_item(item_name); // find item in player inventory

                if (matched_item) {  // if item in inventory
                        Item item_copy = *matched_item;  // copy of item
                        player.remove_item_from_inventory(matched_item->get_name());  // remove item from inventory
                        current_location->add_item(item_copy);  // add item to location
                        player.add_weight(-item_copy.get_weight());  // subtract item weight from player weight
                        std::cout << "You put the " << item_copy.get_name() << " in " << current_location->get_name() << std::endl;
                        if (current_location->get_name() == "The Forest") {  // if in the forest
                                if (item_copy.edible()) {  // if item is edible
                                        required_calories -= item_copy.get_calories();  // subtract item cal from total cal
                                        current_location->remove_item(item_copy.get_name());  // remove item from location
                                        std::cout << "You gave the elf " << item_name << "! Calories left: " << required_calories << std::endl;
                                } else {  // item inedible
                                        Location* new_location = random_location(); // get new location
                                        player.set_current_location(new_location);  // set player location to new location
                                        std::cout << "The elf is pissed off. He sent you to " << new_location->get_name() << std::endl;
                                }
                        }
                } else {
                        std::cout << item_name << " not in your inventory." << std::endl;
                }
        }
}


void Game::go(std::vector<std::string> target) {
        if (target.empty()) { // if direction not provided
            std::cout << "Where do you want to go?" << std::endl;
            return;
        }

        Location* current_location = player.get_current_location(); // get current location
        std::string direction = target[0]; // get specified direction


        std::string directionLower = direction;
        for(char& c : directionLower) c = std::tolower(c);

        std::set<std::string> validDirections = {"north", "south", "east", "west"};
        if (validDirections.find(directionLower) == validDirections.end()) {
            std::cout << "\"" << direction << "\" is not a valid direction." << std::endl;
            return;
         }

        current_location->set_visited(); // mark current visited

        // Check if overweight
        if(player.get_weight() > 30.0f) {
           std::cout << "You are carrying too much weight." << std::endl;
           return;
        }

        std::multimap<std::string, Location*> neighbors = current_location->get_locations(); 
        std::vector<Location*> possibleLocations; // Account for locations same multiple directions
        std::string formattedDirection;

        for (const auto& pair : neighbors) {
             std::string storedDirectionLower = pair.first;
             for (char& c : storedDirectionLower) c = std::tolower(c);
        
             if (storedDirectionLower == directionLower) {
                 possibleLocations.push_back(pair.second);
                 formattedDirection = pair.first;
             }
        }

        if (possibleLocations.empty()) {
            std::cout << "You can't go " << formattedDirection << " from here." << std::endl;
            return;
        }

        if (possibleLocations.size() == 1) {
            // one location → Move directly
            player.set_current_location(possibleLocations[0]);
            std::cout << "You move " << formattedDirection << " to " << possibleLocations[0]->get_name() << "." << std::endl;
        } else {
            // Multiple locations → Ask the player
            // (CHATGPT ASSISTED)
            std::cout << "There are multiple paths " << formattedDirection << ".\n";
            int count = 1;
            for (auto option : possibleLocations) {
                 std::cout << count << ". " << (option->get_visited() ? option->get_name() + " (Visited)" : "Unknown") << std::endl;
                 count++;
            }
            //
            std::cout << "Enter the number of the location you want to go to: ";
            int choice;
            std::cin >> choice;
            // (CHATGPT ASSISTED)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            //
            if (choice > 0 && choice <= possibleLocations.size()) {
                player.set_current_location(possibleLocations[choice - 1]);
                std::cout << "You move " << formattedDirection << " to " << possibleLocations[choice - 1]->get_name() << "." << std::endl;
            } else {
                std::cout << "Invalid choice. Staying at " << current_location->get_name() << "." << std::endl;
            }
        }
}

void Game::show_items(std::vector<std::string> args) {
        std::cout << "Carried Weight: " << player.get_weight() << " lbs" << std::endl;
        player.show_inventory(); 
}

void Game::look(std::vector<std::string> target) {
        // Get curr location, also check if valid location
        Location* currentLocation = player.get_current_location();
        if (!currentLocation) {
            std::cout << "You seem to be nowhere... something went wrong!" << std::endl;
            return;
        }    
        // Uses overloaded stream operator to print location details
        std::cout << *currentLocation;
}

void Game::quit(std::vector<std::string>) {
        in_progress = false;
        std::cout << std::endl << "You have failed the elf and our school!" << std::endl;
}

void Game::trade(std::vector<std::string> target) {
        if (target.empty()) {
            std::cout << "What item do you want to trade?" << std::endl;
            return;
        }

        std::string npcInput = target[0]; 
        for (char& c : npcInput) c = std::tolower(c);

        Location* current_location = player.get_current_location();
        NPC* selected_npc = nullptr;

        // Search for NPC
        for (NPC* npc : current_location->get_npcs()) {
             std::istringstream iss(npc->get_name());
             std::string firstName;
             iss >> firstName; 

             std::string firstNameLower = firstName;
             for (char& c : firstNameLower) c = std::tolower(c);
        
             if (firstNameLower == npcInput) {
                 selected_npc = npc;
                 break;
             }
        }

        // Check if NPC is at location
        if (!selected_npc) {
            std::cout << npcInput << " is not in this location." << std::endl;
            return;
        }

        std::cout << selected_npc->get_name() << ": What would you like to trade?" << std::endl;
        std::string userItemInput;
        std::getline(std::cin, userItemInput);
        for (char& c : userItemInput) c = std::tolower(c);

        // Adjusted item search to allow partial matching
        Item* playerItem = nullptr;
        for (Item& item : player.get_inventory()) {
             std::string itemNameLower = item.get_name();
             for (char& c : itemNameLower) c = std::tolower(c);

             if (itemNameLower.find(userItemInput) != std::string::npos) {
                 playerItem = &item;
                 break; // Stop at the first valid match
             }
        }

        if (!playerItem) {
            std::cout << "You don't have that item to trade." << std::endl;
            return;
        }

        std::string wantedItem = selected_npc->get_wanted_item(); 
        std::string wantedItemLower = wantedItem;
        for (char& c : wantedItemLower) c = std::tolower(c);

        std::string playerItemLower = playerItem->get_name();
        for (char& c : playerItemLower) c = std::tolower(c);
    
    // Updated matching logic to correctly compare player input and wanted item
    if (wantedItemLower.find(playerItemLower) != std::string::npos ||
        playerItemLower.find(wantedItemLower) != std::string::npos) {
        Item reward = selected_npc->get_trade_reward();

        std::string rewardName = reward.get_name();
        std::string tradedItem = playerItem->get_name();
        player.remove_item_from_inventory(playerItem->get_name()); // Remove Item for trade
        player.add_weight(-playerItem->get_weight()); // Update player weight after remove
        player.add_item_to_inventory(reward); // Add reward to player
        player.add_weight(reward.get_weight()); // Update weight of reward
        std::cout << selected_npc->get_name() << ": Thanks for the " << tradedItem << "! Here, take this." << std::endl;   
        std::cout << "You received " << rewardName << "." << std::endl;
     } else {
        std::cout << selected_npc->get_name() << ": \"I don't want that.\"" << std::endl;
     }
}

void Game::dance(std::vector<std::string> args) {
        std::srand(std::time(0)); // randomize seed based on time
        std::vector<std::string> dances = {  // vector of dances
                "hitting the dougie",
                "doing the cha-cha slide",
                "doing the perculator",
                "doing the bachata",
                "doing the macarena",
                "doing the charlie brown",
                "hitting the griddy",
                "doing the orange justice",
                "doing the robot",
                "break dancing",
                "hitting the folks",
                "doing the floss"
        };

        int random_dance = std::rand() % dances.size();  // select random dance in dances
        std::string dance_picked = dances[random_dance];  // store random dance chosen

        std::vector<std::string> responses = {  // vector of npc responses
                "judged you",
                "joined in",
                "laughed",
                "watched you",
                "ignored you",
                "starting cheering"
        };

        int random_response = std::rand() % responses.size();  // select random npc response
        std::string response_picked = responses[random_response];  // store random response chosen

        Location* current_location = player.get_current_location();  // get current location
        const std::vector<NPC*>& npcs = current_location->get_npcs();  // get npcs in location

        int random_npc = std::rand() % npcs.size();  // select random npc in location
        const NPC& npc = *npcs[random_npc];  // get reference to npc chosen

        std::cout << "You are " << dance_picked << " in " << current_location->get_name() << ", " << npc.get_name() << " " << response_picked << std::endl;
}

void Game::create_world() {
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
        locations.push_back(Location("The Forest", "A dark mysterious forest where a powerful elf resides."));


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
        // Commons
        NPC* stanley = new NPC("Stanley the Overworked Cashier","A tired student worker who barely acknowledges customers.",
                {"Next in line please.",
                "Swipe your ID.",
                "Enjoy your meal... or don't. I don't care."});
        NPC* marla = new NPC("Marla the Chef","A strict cook who takes pride in her mass-produced food.",
                {"If you don't like it, cook for yourself next time.",
                "That lasagna took hours. You better appreciate it.",
                "Take all you want, but don't waste it."});


        // Field House
        NPC* anderson = new NPC("Anderson the Coach","A lunatic coach who spends most of his time yelling at players.",
                {"Hustle up!",
                "You're only as good as your last play!",
                "Keep your head in the game!."});
        NPC* chloe = new NPC("Chloe the Workout Enthusiast", "A high-energy student always looking for the next fitness challenge.",
                {"No pain, no gain!",
                "Hydration is key—did you drink enough water today?",
                "Just one more rep! You got this!"});
        
        // Recreation Center
        NPC* milo = new NPC("Milo the Equipment Tinkerer", "A student always fixing gym equipment, convinced the machines have hidden secrets.",
                {"The weights whisper when no one's looking.", 
                "These machines are plotting something big.", 
                "One small tweak, and your workout could change forever."});
        NPC* aurora = new NPC("Aurora the Snack Philosopher", "A laid-back student who ponders the meaning behind every snack.",
                {"A granola bar isn't just a snack!", 
                "Every stale cookie tells a story of endurance.", 
                "Remember, sometimes the best workout is a thoughtful pause for a snack."});

        // Mackinac Hall
        NPC* lana = new NPC("Lana the Lounge Lurker", "A student who's always lounging around campus, avoiding class with a new excuse.",
                {"Nap studies should be a real major.", 
                "Procrastination is an art form.", 
                "If you skip class, no homework!"});
        NPC* todd = new NPC("Todd the Tour Guide", "Overenthusiastic but easily distracted, he gives tours but often forgets where he's going.",
                {"Welcome to campus—wait, where are we again?", 
                "Here's the library... I think.", 
                "Best pizza is... somewhere around here."});

        // Lake Michigan Hall        
        NPC* james = new NPC("James the Forever Student", "James has been here for at least a decade, switching majors every couple years.",
                {"Oh, you're new? I was new... like 12 years ago.", 
                "Thinking of switching to Classics. Or Biology. Or both.", 
                "I have enough credits to graduate, but what's the rush?"});
        
        // Kindschi Hall
        NPC* lenz = new NPC("Lenz the Over-Caffeinated Professor", "Runs purely on espresso and questionable enthusiasm. Speaks at 2x speed.",
                {"Science waits for no one—except grant funding.", 
                "Ask questions! Just not during my coffee break.", 
                "That reaction won't explode... probably."});
        NPC* sam = new NPC("Sam the Perpetual Lab Student", "Has been in the lab so long, they might have tenure. Smells faintly of ethanol.",
                {"What day is it? Lab days don't count.", 
                "If I leave now, I'll ruin my no-sunlight streak.", 
                "I made soap again instead of my experiment..."});
        
        // Manitou Hall
        NPC* greg = new NPC("Greg the Over-Dramatic Student", "A business major who always has a dramatic story to tell.",
                {"One more email and I'll explode!", 
                "My coffee's cold. Today is doomed.", 
                "I tried studying, but the universe had other plans."});
        NPC* debbie = new NPC("Debbie the Bookstore Cat Lady", "A student who spends more time at the campus bookstore than in actual classes.",
                {"I've read this book ten times—it's so cozy!", 
                "The bookstore cat understands me.", 
                "You should read this… unless you prefer textbooks!"});

        // Padnos Hall
        NPC* spencer = new NPC("Spencer the Self-Proclaimed Artist", "A biology major who spends all his free time painting random objects around the building.",
                {"This beaker is my masterpiece.", 
                "It's not just a chair, it's the chair of despair.", 
                "Painting photosynthesis is harder than it looks!"});
        NPC* tina = new NPC("Tina the Tech Over-Explainer", "A computer science major who believes everyone wants to hear about her latest tech discovery.",
                {"4 lines of Python can automate your life!", 
                "I'm making an app—Uber for homework.", 
                "Still using that phone? Let me show you how to root it!"});
        
        // Kirkoff Center
        NPC* matt = new NPC("Matt the Walking Calendar", "Knows every event happening on campus.",
                {"Join the meeting—I got the day planned!", 
                "I should make a Google Calendar for my Google Calendar.", 
                "Gotta run to my 3:15! It's in 3 minutes!"});
        NPC* lily = new NPC("Lily the Loud Study Group Leader", "Always organizing study groups.",
                {"OK, let's break this down—EVERYONE GOT THEIR PENS?!", 
                "The answer is obviously C—are we all clear?!?", 
                "Can't focus, I'm too excited for finals!"});

        // The Forest
        NPC* bernard = new NPC("Bernard the Watchful", "An all-powerful elf with an enormous appetite.",
                {"Have you gathered enough food yet?",
                "The school's survival depends on your success. Keep searching!",
                "Your journey is not over until I am well-fed."});

        // =============================
        // 3. Define Items
        // =============================
        // trade items (wanted items, reward items)

        Item clearCup("Clear Plastic Cup", "A sturdy plastic cup with some residue left inside.", 0, 1.5); 
        Item sodaCan("Unbranded Soda Can", "A full can of soda with the branding rubbed away.", 20, 1.0);
        marla->set_trade("Clear Plastic Cup", sodaCan);
        Item energyBar("Energy Bar", "A small partially unwrapped protein bar left on a bleacher.", 25, 1.0); 
        Item pearSlice("Half-Eaten Pear Slice", "A single Pear slice with a bite taken out. It's starting to brown.", 10, 0.5);
        Item breadRoll("Unfinished Bread Roll", "A soft dinner roll with one bite taken out. Slightly stale but edible.", 45, 2.0);
        
        Item banana("Banana", "A ripe banana, slightly bruised but still good to eat.", 35, 0.5);
        Item trailMix("Bag of Trail Mix", "A small, resealable bag of trail mix filled with nuts and dried fruit.", 45, 1.5);
        Item proteinPowder("Box of Protein Powder", "A box of protein powder, half-open and empty.", 0, 3.0);
        Item proteinShake("Protein Shake", "A mostly finished protein shake", 20, 1.0);
        chloe->set_trade("Box of Protein Powder", proteinShake);

        Item staleCookie("Stale Protein Cookie", "An enormous stale cookie that has hardened over time.", 10, 1.0);
        Item yogurtCup("Diet Yogurt Cup", "A large cup of fat-free, low-calorie yogurt from the snack machine.", 15, 1.5);
        Item weightPlate("Rusted Weight Plate", "A heavily rusted weight plate, its surface pitted and corroded from years of neglect.", 0, 5.0);
        Item proteinBar("Large Protein Bar", "A protein bar that's been crushed in a backpack.", 30, 1.0);
        milo->set_trade("Rusted Weight Plate", proteinBar);

        Item textbook("Dusty Textbook", "An old textbook filled with scribbled notes from past classes.", 0, 3.0);
        Item smushedMuffin("Smushed Muffin", "A muffin that's been squished in a backpack for far too long.", 35, 2.0);
        Item appleSlices("Packaged Apple Slices", "A pre-packaged container of apple slices from the campus store.", 25, 2.5);

        Item pretzels("Forgotten Bag of Pretzels", "Stale but still crunchable. Found wedged under a table leg.", 25, 2.5);
        Item mysteryCandy("Mystery-Flavored Hard Candy", "A single candy with a faded wrapper. It could be anything.", 30, 1.0);

        Item labNotebook("Half-Used Lab Notebook", "The first few pages are filled with equations. The rest is doodles and coffee stains.", 0, 2.0);
        Item safetyGoggles("Crushed Safety Goggles", "Clearly failed their last experiment. Now they sit here, a tragic reminder.", 0, 1.5);
        Item bunsenTubing("Burnt-Out Bunsen Burner Tubing", "Someone turned the gas up way too high. Now it's just a melted mess.", 0, 2.5);
        Item labCoat("Abandoned Lab Coat", "Slightly singed. Smells like chemicals. Probably left behind for a reason.", 0, 2.0);
        Item rockCandy("Lab-Grown Rock Candy", "A large piece of rock candy, perfect for a sweet tooth.", 20, 1.0);
        Item gelatin("Gelatinous Blob", "A wobbly blob of gelatin, left behind from a lab.", 10, 0.5);
        lenz->set_trade("Abandoned Lab Coat", rockCandy);
        sam->set_trade("Half-Used Lab Notebook", gelatin);

        Item staleBagel("Stale Bagel", "Hard as a rock, but still has a faint bagel flavor if you squint really hard.", 15, 1.5);
        Item backpack("Scuffed Leather Backpack", "Well-worn but still functional. Looks like someone gave up and left this behind.", 0, 4.0);
        Item calculator("Misplaced Calculator", "It's probably broken, but it could be useful for someone.", 0, 2.0);
        Item candyWrapper("Candy Bar Wrapper", "The candy's gone, but the wrapper is a solid reminder of someone's poor life choices.", 15, 1.0);

        Item energyDrink("Energy Drink", "Half-empty but still a kick of energy.", 20, 2.0);
        Item peanutButter("Peanut Butter Packet", "A little sticky—probably thanks to students who didn't close it properly.", 30, 1.0);
        Item sandwich("Half-Eaten Sandwich", "A mystery sandwich wrapped in plastic.", 50, 3.0);
        Item donut("Glazed Donut with a Bite Missing", "Who takes just one bite and leaves the rest? The world may never know.", 40, 2.5);

        Item stickyNotes("Sticky Note Pad", "Mostly empty, with a few motivational quotes from a stressed-out student.", 0, 0.5);
        Item pandaEntree("Half-Eaten Panda Express Entree", "Someone left this on a table, but it's a mystery how much of it is still edible.", 35, 1.0);
        Item studyGuide("Forgotten Study Guide", "It was supposed to be a lifesaver for your final exam.", 0, 1.5);
        Item ramenPacket("Instant Ramen Packet", "A single packet of instant ramen, perfect for a quick meal.", 25, 1.0);
        lily->set_trade("Forgotten Study Guide", ramenPacket);
        
        // =============================
        // 4. Assign Items & NPCs to Locations
        // =============================
        theCommons->add_item(clearCup);
        theCommons->add_item(energyBar);
        theCommons->add_item(pearSlice);
        theCommons->add_item(breadRoll);
        theCommons->add_npc(stanley);
        theCommons->add_npc(marla);

        theFieldHouse->add_item(banana);
        theFieldHouse->add_item(trailMix);
        theFieldHouse->add_item(proteinPowder);
        theFieldHouse->add_npc(anderson);
        theFieldHouse->add_npc(chloe);

        theRecreationCenter->add_item(staleCookie);
        theRecreationCenter->add_item(yogurtCup);
        theRecreationCenter->add_item(weightPlate);
        theRecreationCenter->add_npc(milo);
        theRecreationCenter->add_npc(aurora);

        mackinacHall->add_item(textbook);
        mackinacHall->add_item(smushedMuffin);
        mackinacHall->add_item(appleSlices);
        mackinacHall->add_npc(lana);
        mackinacHall->add_npc(todd);

        lakeMichiganHall->add_item(pretzels);
        lakeMichiganHall->add_item(mysteryCandy);
        lakeMichiganHall->add_npc(james);

        kindschiHall->add_item(labNotebook);
        kindschiHall->add_item(safetyGoggles);
        kindschiHall->add_item(bunsenTubing);
        kindschiHall->add_item(labCoat);
        kindschiHall->add_npc(lenz);
        kindschiHall->add_npc(sam);

        manitouHall->add_item(staleBagel);
        manitouHall->add_item(backpack);
        manitouHall->add_item(calculator);
        manitouHall->add_item(candyWrapper);
        manitouHall->add_npc(greg);
        manitouHall->add_npc(debbie);

        padnosHall->add_item(energyDrink);
        padnosHall->add_item(peanutButter);
        padnosHall->add_item(sandwich);
        padnosHall->add_item(donut);
        padnosHall->add_npc(spencer);
        padnosHall->add_npc(tina);
        
        kirkoffCenter->add_item(stickyNotes);
        kirkoffCenter->add_item(pandaEntree);
        kirkoffCenter->add_item(studyGuide);
        kirkoffCenter->add_npc(matt);
        kirkoffCenter->add_npc(lily);

        theForest->add_npc(bernard);

        // =============================
        // 5. Define Location Connections
        // =============================
        theCommons->add_location("East", theForest);
        theCommons->add_location("West", manitouHall);
        theCommons->add_location("West", padnosHall);

        theFieldHouse->add_location("East", mackinacHall);
        theFieldHouse->add_location("South", theRecreationCenter);

        theRecreationCenter->add_location("East", kindschiHall);
        theRecreationCenter->add_location("North", theFieldHouse);

        mackinacHall->add_location("West", theFieldHouse);
        mackinacHall->add_location("South", manitouHall);

        lakeMichiganHall->add_location("East", padnosHall);
        lakeMichiganHall->add_location("North", kindschiHall);   
        
        kindschiHall->add_location("West", theRecreationCenter);
        kindschiHall->add_location("South", lakeMichiganHall);
        kindschiHall->add_location("East", padnosHall);

        manitouHall->add_location("North", mackinacHall);
        manitouHall->add_location("South", padnosHall);
        manitouHall->add_location("East", theCommons);

        padnosHall->add_location("West", kindschiHall);
        padnosHall->add_location("West", lakeMichiganHall);
        padnosHall->add_location("North", manitouHall);
        padnosHall->add_location("South", kirkoffCenter);
        padnosHall->add_location("East", theCommons);

        kirkoffCenter->add_location("North", padnosHall);  

        theForest->add_location("West", theCommons);
        
        player.set_current_location(theForest); // Set starting location 
}

void Game::start() {
        std::cout << "Welcome to GVSU-Zork!" << std::endl;
        std::cout << "You are on a mission to save GVSU with the help of the powerful elf, Bernard." << std::endl;
        std::cout << "You must gather 500 calories worth of food to feed Bernard and save the school." << std::endl;
        std::cout << "What will you do?";
        game_loop();
}

void Game::game_loop() {
    while (in_progress) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);
        
        // Tokenize input (ASSISTED BY CHATGPT)
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        for (std::string s; iss >> s; ) tokens.push_back(s);

        if (tokens.empty()) continue;

        std::string command = tokens[0];
        tokens.erase(tokens.begin());

        if (commands.find(command) != commands.end()) {
            commands[command](tokens);
        } else {
            std::cout << "Invalid command. Type 'help' for available commands." << std::endl;
        }
        if (required_calories <= 0) {
                std::cout << "\nCongratulations! You have satisfied Bernard and he saves GVSU!" << std::endl;
                in_progress = false;
                return;
        }
    }
}


Location* Game::random_location() {
        std::srand(time(0));  // randomize seed based on time
        int index = std::rand() % locations.size();  // random number in range of locations
        return &locations[index];  // return new location
}