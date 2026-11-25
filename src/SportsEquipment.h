
#pragma once

#include <string>
#include <iostream>

class SportsEquipment {
public:
    SportsEquipment(
        int inventoryNumber,
        const std::string& name,
        const std::string& condition,
        int quantity
    )
        : inventoryNumber_(inventoryNumber),
          name_(name),
          condition_(condition),
          quantity_(quantity) {
    }

    int getInventoryNumber() const {
        return inventoryNumber_;
    }

    const std::string& getName() const {
        return name_;
    }

    const std::string& getCondition() const {
        return condition_;
    }

    int getQuantity() const {
        return quantity_;
    }

    void print() const {
        std::cout << *this;
    }

    // Оператор виведення об'єкта в потік
    friend std::ostream& operator<<(
        std::ostream& out,
        const SportsEquipment& equipment
    ) {
        out << "Inventory number: " << equipment.inventoryNumber_
            << ", Name: " << equipment.name_
            << ", Condition: " << equipment.condition_
            << ", Quantity: " << equipment.quantity_;

        return out;
    }

private:
    int inventoryNumber_;
    std::string name_;
    std::string condition_;
    int quantity_;
};
