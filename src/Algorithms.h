
#pragma once

#include "Catalog.h"

#include <iostream>
#include <type_traits>
#include <utility>

// Допоміжна функція для виведення одного елемента
template <typename T>
void printValue(const T& value) {
    std::cout << value;
}

// Повна спеціалізація для типу bool
template <>
inline void printValue<bool>(const bool& value) {
    std::cout << (value ? "так" : "ні");
}

// 1. Пошук елемента за умовою
template <typename Container, typename Predicate>
auto findIf(const Container& container, Predicate predicate)
    -> typename Container::const_iterator {

    for (auto it = container.begin(); it != container.end(); ++it) {
        if (predicate(*it)) {
            return it;
        }
    }

    return container.end();
}

// 2. Підрахунок елементів за умовою
template <typename Container, typename Predicate>
std::size_t countIf(const Container& container, Predicate predicate) {
    std::size_t count = 0;

    for (const auto& item : container) {
        if (predicate(item)) {
            ++count;
        }
    }

    return count;
}

// 3. Виведення всіх елементів
template <typename Container>
void printAll(const Container& container) {
    using T = typename Container::value_type;

    if constexpr (std::is_arithmetic_v<T>) {
        bool first = true;

        for (const auto& item : container) {
            if (!first) {
                std::cout << ", ";
            }

            printValue(item);
            first = false;
        }

        std::cout << '\n';
    }
    else {
        for (const auto& item : container) {
            printValue(item);
            std::cout << '\n';
        }
    }
}

// 4. Перетворення елементів в інший тип
template <typename Container, typename Transform>
auto transformTo(const Container& container, Transform transform)
    -> Catalog<std::decay_t<
        decltype(transform(std::declval<typename Container::value_type>()))
    >> {

    using ResultType = std::decay_t<
        decltype(transform(std::declval<typename Container::value_type>()))
    >;

    Catalog<ResultType> result;

    for (const auto& item : container) {
        result.add(transform(item));
    }

    return result;
}

// 5. Зведення елементів до одного значення
template <typename Container, typename T, typename BinaryOperation>
T reduce(
    const Container& container,
    T initialValue,
    BinaryOperation operation
) {
    T result = initialValue;

    for (const auto& item : container) {
        result = operation(result, item);
    }

    return result;
}
