
#include "Catalog.h"
#include "SportsEquipment.h"
#include "WriteOffAct.h"
#include "Algorithms.h"

#include <iostream>
#include <string>

int main() {
    // Контейнер цілих чисел
    Catalog<int> numbers;

    numbers.add(10);
    numbers.add(20);
    numbers.add(30);
    numbers.add(40);
    numbers.add(50);

    // Контейнер рядків
    Catalog<std::string> names;

    names.add("Basketball");
    names.add("Football");
    names.add("Volleyball");

    // Контейнер логічних значень
    Catalog<bool> statuses;

    statuses.add(true);
    statuses.add(false);
    statuses.add(true);

    // Контейнер спортивного інвентарю
    Catalog<SportsEquipment> equipment;

    equipment.add(SportsEquipment(101, "Basketball", "Good", 5));
    equipment.add(SportsEquipment(102, "Football", "Excellent", 3));
    equipment.add(SportsEquipment(103, "Volleyball", "Good", 8));

    // Контейнер актів списання
    Catalog<WriteOffAct> writeOffActs;

    writeOffActs.add(
        WriteOffAct(1, 101, "Physical damage", "2026-10-15", 2)
    );

    writeOffActs.add(
        WriteOffAct(2, 103, "Wear and tear", "2026-10-20", 1)
    );

    // 1. printAll – виведення контейнерів
    std::cout << "=== PRINT ALL ===\n";

    std::cout << "\nNumbers:\n";
    printAll(numbers);

    std::cout << "\nNames:\n";
    printAll(names);

    std::cout << "\nStatuses:\n";
    printAll(statuses);

    std::cout << "\nSports equipment:\n";
    printAll(equipment);

    std::cout << "\nWrite-off acts:\n";
    printAll(writeOffActs);

    // 2. findIf – пошук за умовою
    std::cout << "\n=== FIND IF ===\n";

    auto number = findIf(numbers, [](int value) {
        return value > 25;
    });

    if (number != numbers.end()) {
        std::cout << "First number greater than 25: "
                  << *number << '\n';
    }

    auto item = findIf(equipment, [](const SportsEquipment& value) {
        return value.getInventoryNumber() == 102;
    });

    if (item != equipment.end()) {
        std::cout << "Found equipment: " << *item << '\n';
    }

    // 3. countIf – підрахунок за умовою
    std::cout << "\n=== COUNT IF ===\n";

    std::size_t evenNumbers = countIf(numbers, [](int value) {
        return value % 2 == 0;
    });

    std::cout << "Even numbers: " << evenNumbers << '\n';

    std::size_t goodEquipment = countIf(
        equipment,
        [](const SportsEquipment& value) {
            return value.getCondition() == "Good";
        }
    );

    std::cout << "Equipment in good condition: "
              << goodEquipment << '\n';

    // 4. transformTo – перетворення елементів
    std::cout << "\n=== TRANSFORM TO ===\n";

    auto numberStrings = transformTo(
        numbers,
        [](int value) {
            return std::to_string(value);
        }
    );

    std::cout << "Numbers converted to strings:\n";
    printAll(numberStrings);

    auto equipmentNames = transformTo(
        equipment,
        [](const SportsEquipment& value) {
            return value.getName();
        }
    );

    std::cout << "Equipment names:\n";
    printAll(equipmentNames);

    // 5. reduce – зведення до одного значення
    std::cout << "\n=== REDUCE ===\n";

    int sum = reduce(
        numbers,
        0,
        [](int result, int value) {
            return result + value;
        }
    );

    std::cout << "Sum of numbers: " << sum << '\n';

    int totalQuantity = reduce(
        equipment,
        0,
        [](int result, const SportsEquipment& value) {
            return result + value.getQuantity();
        }
    );

    std::cout << "Total equipment quantity: "
              << totalQuantity << '\n';

    return 0;
}
