#include "Item.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

void test_valid_item() {
    Item item("Banana", "A ripe banana, slightly bruised but still good to eat.", 35, 0.5);
    assert(item.get_name() == "Banana");
    assert(item.get_description() == "A ripe banana, slightly bruised but still good to eat.");
    assert(item.get_calories() == 35);
    assert(item.get_weight() == 0.5f);
    std::cout << "test_valid_item passed" << std::endl;
}

void test_invalid_name() {
    try {
        Item item("", "A ripe banana, slightly bruised but still good to eat.", 35, 0.5);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Name cannot be empty");
        std::cout << "test_invalid_name passed" << std::endl;
        return;
    }
    assert(false); // Should not reach here
}

void test_invalid_description() {
    try {
        Item item("Banana", "", 35, 0.5);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Description cannot be empty");
        std::cout << "test_invalid_description passed" << std::endl;
        return;
    }
    assert(false); // Should not reach here
}

void test_invalid_calories() {
    try {
        Item item("Banana", "A ripe banana, slightly bruised but still good to eat.", -1, 0.5);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Calories must be between 0 and 1000");
        std::cout << "test_invalid_calories passed" << std::endl;
        return;
    }
    assert(false); // Should not reach here
}

void test_invalid_weight() {
    try {
        Item item("Banana", "A ripe banana, slightly bruised but still good to eat.", 35, -1);
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Weight must be between 0 and 500 lbs");
        std::cout << "test_invalid_weight passed" << std::endl;
        return;
    }
    assert(false); // Should not reach here
}

int main() {
    test_valid_item();
    test_invalid_name();
    test_invalid_description();
    test_invalid_calories();
    test_invalid_weight();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
