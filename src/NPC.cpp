#include "NPC.h"
#include <iostream>

// Constructor for the NPC class
NPC::NPC(std::string name, std::string description, std::vector<std::string> messages)
    : name(name), description(description), messages(messages), message_index(0) {}

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
    std::cout << "DEBUG: Current message index: " << message_index << std::endl;
    std::string msg = messages[message_index]; // Get current messages
    message_index = (message_index + 1) % messages.size(); // Move next messages, loops back to start
    std::cout << "DEBUG: Next message index: " << message_index << std::endl;
    return msg; 
}