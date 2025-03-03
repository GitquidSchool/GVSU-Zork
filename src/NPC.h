#ifndef NPC_H
#define NPC_H

#include "Item.h"
#include <string>
#include <vector>

/**
 * Ethan Umana: 3/2/2025
 * Vincent Nguyen: 3/2/2025
 */

class NPC {
private:
    std::string name;
    std::string description;
    std::vector<std::string> messages;
    int message_index;

    std::string wanted_item;
    Item reward_item;
    
public:
    // Constructor to initialize the NPC with a name, description, and messages
    NPC(std::string name, std::string description, std::vector<std::string> messages);
    std::string get_name() const;
    std::string get_description() const;
    std::string talk();

    void set_trade(const std::string& wanted, Item reward); 
    std::string get_wanted_item() const;  
    Item get_trade_reward() const;    
};

#endif