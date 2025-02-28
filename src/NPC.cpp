#include "NPC.h"

// Constructor for the NPC class
NPC::NPC(std::string name, std::string description, std::vector<std::string> messages)
    : name(name), description(description), messages(messages), message_index(0),
        // Initialize reward item with default values
      reward_item("None", "No trade available.", 0, 0.0)
    {}

std::string NPC::get_name() const {
    return name;
}

std::string NPC::get_description() const {
    return description;
}

// Returns next message in list of messages
// If no messages, returns default
std::string NPC::talk() {
    if (messages.empty()) return name + " remains silent."; // Check if no messages
    std::string msg = messages[message_index]; // Get current messages
    message_index = (message_index + 1) % messages.size(); // Move next messages, loops back to start
    return msg; 
}

void NPC::set_trade(const std::string& wanted, Item reward) {
    wanted_item = wanted;
    reward_item = reward;
}

std::string NPC::get_wanted_item() const {
    return wanted_item;  
}

Item NPC::get_trade_reward() const {
    return reward_item;
}