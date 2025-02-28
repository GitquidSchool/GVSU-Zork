#ifndef ITEM_H 
#define ITEM_H

#include <string>   
#include <iostream> 
#include <stdexcept> 

class Item {
private:
    std::string name;           // Name (cannot be empty)
    std::string description;    // Description (cannot be empty)
    int calories;               // (0-1000)
    float weight;               // (0-500lbs)

public:
    // Constructor to initialize an Item with its name, description, calories, and weight
    // Throws exceptions if any argument is invalid
    Item(const std::string &name,
         const std::string &description,
         int calories,
         float weight);
    
    std::string get_name() const;   
    std::string get_description() const; 
    int get_calories() const;      
    float get_weight() const;
    bool edible() const;      

    // Overload stream insertion operator to allows Item class to be printed (ASSISTED BY CHATGPT)
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif

