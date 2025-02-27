#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>

class NPC {
private:
    std::string name;
    std::string description;
    std::vector<std::string> messages;
    int message_index;
    
public:
    // Constructor to initialize the NPC with a name, description, and messages
    NPC(std::string name, std::string description, std::vector<std::string> messages);
    std::string get_name() const;
    std::string get_description() const;
    std::string talk();
};

#endif