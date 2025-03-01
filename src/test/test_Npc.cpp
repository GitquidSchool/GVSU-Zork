#include "NPC.h"
#include <iostream>
#include <cassert>
#include <vector>

void test_npc_constructor() {
    std::vector<std::string> messages = {
        "If you don't like it, cook for yourself next time.",
        "That lasagna took hours. You better appreciate it.",
        "Take all you want, but don't waste it."
    };
    NPC npc("Chef Marla", "A strict cook who takes pride in her mass-produced food.", messages);
    assert(npc.get_name() == "Chef Marla");
    std::cout << "test_npc_constructor passed" << std::endl;
}

void test_npc_talk() {
    std::vector<std::string> messages = {
        "If you don't like it, cook for yourself next time.",
        "That lasagna took hours. You better appreciate it.",
        "Take all you want, but don't waste it."
    };
    NPC npc("Chef Marla", "A strict cook who takes pride in her mass-produced food.", messages);
    assert(npc.talk() == "If you don't like it, cook for yourself next time.");
    assert(npc.talk() == "That lasagna took hours. You better appreciate it.");
    assert(npc.talk() == "Take all you want, but don't waste it.");
    assert(npc.talk() == "If you don't like it, cook for yourself next time."); // Should loop back to the first message
    std::cout << "test_npc_talk passed" << std::endl;
}

void test_npc_no_messages() {
    std::vector<std::string> messages;
    NPC npc("Silent Bob", "A man of few words.", messages);
    assert(npc.talk() == "Silent Bob remains silent.");
    std::cout << "test_npc_no_messages passed" << std::endl;
}

int main() {
    test_npc_constructor();
    test_npc_talk();
    test_npc_no_messages();
    return 0;
}