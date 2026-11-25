
#include <gtest/gtest.h>

#include "Catalog.h"
#include "SportsEquipment.h"
#include "WriteOffAct.h"
#include "Algorithms.h"

#include <string>

// Перевірка додавання цілих чисел
TEST(CatalogTests, AddIntegers) {
    Catalog<int> catalog;

    catalog.add(10);
    catalog.add(20);
    catalog.add(30);

    EXPECT_EQ(catalog.size(), 3);
    EXPECT_EQ(catalog.at(0), 10);
    EXPECT_EQ(catalog.at(1), 20);
    EXPECT_EQ(catalog.at(2), 30);
}

// Перевірка додавання рядків
TEST(CatalogTests, AddStrings) {
    Catalog<std::string> catalog;

    catalog.add("Basketball");
    catalog.add("Football");

    EXPECT_EQ(catalog.size(), 2);
    EXPECT_EQ(catalog.at(0), "Basketball");
    EXPECT_EQ(catalog.at(1), "Football");
}

// Перевірка додавання спортивного інвентарю
TEST(CatalogTests, AddSportsEquipment) {
    Catalog<SportsEquipment> catalog;

    catalog.add(SportsEquipment(101, "Basketball", "Good", 5));

    EXPECT_EQ(catalog.size(), 1);
    EXPECT_EQ(catalog.at(0).getInventoryNumber(), 101);
    EXPECT_EQ(catalog.at(0).getName(), "Basketball");
    EXPECT_EQ(catalog.at(0).getQuantity(), 5);
}

// Перевірка додавання актів списання
TEST(CatalogTests, AddWriteOffActs) {
    Catalog<WriteOffAct> catalog;

    catalog.add(
        WriteOffAct(1, 101, "Physical damage", "2026-10-15", 2)
    );

    EXPECT_EQ(catalog.size(), 1);
    EXPECT_EQ(catalog.at(0).getActNumber(), 1);
    EXPECT_EQ(catalog.at(0).getInventoryNumber(), 101);
    EXPECT_EQ(catalog.at(0).getQuantity(), 2);
}

// Перевірка збільшення місткості контейнера
TEST(CatalogTests, CapacityDoubles) {
    Catalog<int> catalog;

    EXPECT_EQ(catalog.capacity(), 4);

    for (int i = 0; i < 5; ++i) {
        catalog.add(i);
    }

    EXPECT_EQ(catalog.size(), 5);
    EXPECT_EQ(catalog.capacity(), 8);
}

// Перевірка незалежності копії контейнера
TEST(CatalogTests, CopyCreatesIndependentContainer) {
    Catalog<int> original;

    original.add(10);
    original.add(20);

    Catalog<int> copy = original;

    copy.add(30);

    EXPECT_EQ(original.size(), 2);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(original.at(0), 10);
    EXPECT_EQ(copy.at(2), 30);
}

// Перевірка переміщення контейнера
TEST(CatalogTests, MoveTransfersData) {
    Catalog<int> original;

    original.add(10);
    original.add(20);

    Catalog<int> moved = std::move(original);

    EXPECT_TRUE(original.empty());
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved.at(0), 10);
    EXPECT_EQ(moved.at(1), 20);
}

// Перевірка роботи range-based for
TEST(CatalogTests, RangeBasedForWorks) {
    Catalog<int> catalog;

    catalog.add(1);
    catalog.add(2);
    catalog.add(3);

    int sum = 0;

    for (const auto& value : catalog) {
        sum += value;
    }

    EXPECT_EQ(sum, 6);
}

// Перевірка пошуку, якщо елемент відсутній
TEST(AlgorithmTests, FindIfReturnsEndWhenNotFound) {
    Catalog<int> catalog;

    catalog.add(1);
    catalog.add(2);
    catalog.add(3);

    auto result = findIf(catalog, [](int value) {
        return value > 10;
    });

    EXPECT_EQ(result, catalog.end());
}

// Перевірка reduce для порожнього контейнера
TEST(AlgorithmTests, ReduceWorksWithEmptyContainer) {
    Catalog<int> catalog;

    int result = reduce(
        catalog,
        100,
        [](int total, int value) {
            return total + value;
        }
    );

    EXPECT_EQ(result, 100);
}

// Перевірка спеціалізації для bool
TEST(AlgorithmTests, BoolSpecializationWorks) {
    Catalog<bool> catalog;

    catalog.add(true);
    catalog.add(false);

    EXPECT_EQ(catalog.size(), 2);
    EXPECT_TRUE(catalog.at(0));
    EXPECT_FALSE(catalog.at(1));
}

// Перевірка підрахунку елементів
TEST(AlgorithmTests, CountIfWorks) {
    Catalog<int> catalog;

    catalog.add(1);
    catalog.add(2);
    catalog.add(3);
    catalog.add(4);

    auto count = countIf(catalog, [](int value) {
        return value % 2 == 0;
    });

    EXPECT_EQ(count, 2);
}

// Перевірка перетворення типів
TEST(AlgorithmTests, TransformToWorks) {
    Catalog<int> catalog;

    catalog.add(10);
    catalog.add(20);

    auto result = transformTo(catalog, [](int value) {
        return std::to_string(value);
    });

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0), "10");
    EXPECT_EQ(result.at(1), "20");
}
