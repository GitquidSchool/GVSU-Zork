#include "Item.h"
#include <stdexcept>


Item::Item(const std::string &name, const std::string &description, int calories, float weight) {
    // Validate and assign attributes
    if (name.empty()) {
        throw std::invalid_argument("Item must have a name");
    }
    this->name = name;

    if (description.empty()) {
        throw std::invalid_argument("Description cannot be empty");
    }
    this->description = description;
    
    if (calories < 0 || calories > 1000) {
        throw std::invalid_argument("Calories must be between 0 and 1000");
    }
    this->calories = calories;

    if (weight < 0 || weight > 500) {
        throw std::invalid_argument("Weight must be between 0 and 500 lbs");
    }
    this->weight = weight;
}

// Getters to retrieve attributes
std::string Item::get_name() const {
    return name;
}

std::string Item::get_description() const {
    return description;
}

int Item::get_calories() const {
    return calories;
}

float Item::get_weight() const {
    return weight;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os  << item.get_name() << " (" << item.get_calories() << " calories) - "
        << item.get_weight() << " lb - " << item.get_description();
    return os;
}
