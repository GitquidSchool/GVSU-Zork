#include "Location.h"
#include "Item.h"
#include "NPC.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>

void test_location_constructor() {
    Location location("Kirkhof Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    assert(location.get_name() == "Kirkhof Center");
    assert(location.get_description() == "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    assert(location.get_visited() == false); // Ensure newly created location is not visited
    std::cout << "test_location_constructor passed" << std::endl;
}

void test_add_npc() {
    Location location("Kirkhof Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    NPC npc1("Matt the Walking Calendar", "test.", {"test!"});
    NPC npc2("Lily the Loud Study Group Leader", "test.", {"test!"});
    location.add_npc(npc1);
    location.add_npc(npc2);
    std::vector<NPC> npcs = location.get_npcs();
    assert(npcs.size() == 2);
    assert(npcs[0].get_name() == "Matt the Walking Calendar");
    assert(npcs[1].get_name() == "Lily the Loud Study Group Leader");
    std::cout << "test_add_npc passed" << std::endl;
}

void test_add_item() {
    Location location("Kirkhof Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    Item item1("Sticky Note Pad", "Mostly empty, with a few motivational quotes from a stressed-out student.", 0, 0.5);
    Item item2("Half-Eaten Panda Express Entree", "Someone left this on a table, but it's a mystery how much of it is still edible.", 35, 1.0);
    Item item3("Outdated College Brochure", "Old and crumpled from being stuffed in a backpack.", 0, 0.5);
    Item item4("Forgotten Study Guide", "It was supposed to be a lifesaver for your final exam.", 0, 1.5);
    location.add_item(item1);
    location.add_item(item2);
    location.add_item(item3);
    location.add_item(item4);
    std::vector<Item> items = location.get_items();
    assert(items.size() == 4);
    assert(items[0].get_name() == "Sticky Note Pad");
    assert(items[1].get_name() == "Half-Eaten Panda Express Entree");
    assert(items[2].get_name() == "Outdated College Brochure");
    assert(items[3].get_name() == "Forgotten Study Guide");
    std::cout << "test_add_item passed" << std::endl;
}

void test_add_location() {
    Location kirkhofCenter("Kirkhof Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    Location padnos("Padnos", "A place for science and engineering students.");
    kirkhofCenter.add_location("north", &padnos);
    std::map<std::string, Location*> neighbors = kirkhofCenter.get_locations();
    assert(neighbors.size() == 1);
    assert(neighbors["north"]->get_name() == "Padnos");
    std::cout << "test_add_location passed" << std::endl;
}

void test_invalid_location() {
    try {
        Location location("", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Location name cannot be empty.");
        std::cout << "test_invalid_location passed" << std::endl;
        return;
    }
    assert(false); // Should not reach here
}

// Test that the stream operator correctly formats the output for a visited location
void test_location_stream_operator() {
    Location kirkhofCenter("Kirkhof Center", "A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.");
    Location padnos("Padnos", "A place for science and engineering students.");
    
    // Add NPCs
    NPC npc1("Matt the Walking Calendar", "test.", {"test!"});
    NPC npc2("Lily the Loud Study Group Leader", "test.", {"test!"});
    kirkhofCenter.add_npc(npc1);
    kirkhofCenter.add_npc(npc2);

    // Add Items
    Item item1("Sticky Note Pad", "Mostly empty, with a few motivational quotes from a stressed-out student.", 0, 0.5);
    Item item2("Half-Eaten Panda Express Entree", "Someone left this on a table, but it's a mystery how much of it is still edible.", 35, 1.0);
    kirkhofCenter.add_item(item1);
    kirkhofCenter.add_item(item2);

    // Connect locations
    kirkhofCenter.add_location("north", &padnos);
    
    // Set padnos as visited
    padnos.set_visited();

    // Capture the output
    std::ostringstream output;
    output << kirkhofCenter;
    
    std::string expected_output =
        "Kirkhof Center - A lively student hub with dining, meeting rooms, lounges, and a theater for all things campus life.\n"
        "You see the following NPCs:\n"
        "- Matt the Walking Calendar\n"
        "- Lily the Loud Study Group Leader\n"
        "You see the following Items:\n"
        "- Sticky Note Pad (0 calories) - 0.5 lb - Mostly empty, with a few motivational quotes from a stressed-out student.\n"
        "- Half-Eaten Panda Express Entree (35 calories) - 1 lb - Someone left this on a table, but it's a mystery how much of it is still edible.\n"
        "You can go in the following Directions:\n"
        "- north - Padnos (Visited)\n";

    assert(output.str() == expected_output);
    std::cout << "test_location_stream_operator passed" << std::endl;
}

int main() {
    test_location_constructor();
    test_add_npc();
    test_add_item();
    test_add_location();
    test_invalid_location();
    test_location_stream_operator();
    return 0;
}
