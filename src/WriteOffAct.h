#pragma once

#include <string>
#include <iostream>

class WriteOffAct {
public:
    WriteOffAct(
        int actNumber,
        int inventoryNumber,
        const std::string& reason,
        const std::string& date,
        int quantity
    )
        : actNumber_(actNumber),
          inventoryNumber_(inventoryNumber),
          reason_(reason),
          date_(date),
          quantity_(quantity) {
    }

    int getActNumber() const {
        return actNumber_;
    }

    int getInventoryNumber() const {
        return inventoryNumber_;
    }

    const std::string& getReason() const {
        return reason_;
    }

    const std::string& getDate() const {
        return date_;
    }

    int getQuantity() const {
        return quantity_;
    }

    friend std::ostream& operator<<(
        std::ostream& out,
        const WriteOffAct& act
    ) {
        out << "Act number: " << act.actNumber_
            << ", Inventory number: " << act.inventoryNumber_
            << ", Reason: " << act.reason_
            << ", Date: " << act.date_
            << ", Quantity: " << act.quantity_;

        return out;
    }

private:
    int actNumber_;
    int inventoryNumber_;
    std::string reason_;
    std::string date_;
    int quantity_;
};