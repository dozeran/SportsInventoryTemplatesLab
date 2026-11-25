
#pragma once

#include <cstddef>
#include <stdexcept>
#include <new>
#include <utility>
#include <type_traits>

template <typename T>
class Catalog {
    static_assert(
        std::is_copy_constructible_v<T> ||
        std::is_move_constructible_v<T>,
        "Catalog<T>: T must be copyable or movable"
    );

public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    // Конструктор за замовчуванням
    Catalog()
        : data_(nullptr), size_(0), capacity_(4) {
        data_ = static_cast<T*>(
            ::operator new(sizeof(T) * capacity_)
        );
    }

    // Конструктор копіювання
    Catalog(const Catalog& other)
        : data_(static_cast<T*>(
              ::operator new(sizeof(T) * other.capacity_)
          )),
          size_(0),
          capacity_(other.capacity_) {

        try {
            for (std::size_t i = 0; i < other.size_; ++i) {
                new (&data_[i]) T(other.data_[i]);
                ++size_;
            }
        }
        catch (...) {
            clear();
            ::operator delete(data_);
            throw;
        }
    }

    // Оператор копіювального присвоєння
    Catalog& operator=(const Catalog& other) {
        if (this == &other) {
            return *this;
        }

        Catalog temp(other);
        swap(temp);

        return *this;
    }

    // Конструктор переміщення
    Catalog(Catalog&& other) noexcept
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_) {

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Оператор переміщувального присвоєння
    Catalog& operator=(Catalog&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        clear();
        ::operator delete(data_);

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    // Деструктор
    ~Catalog() {
        clear();
        ::operator delete(data_);
    }

    // Додавання копіюванням
    void add(const T& item) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 4 : capacity_ * 2);
        }

        new (&data_[size_]) T(item);
        ++size_;
    }

    // Додавання переміщенням
    void add(T&& item) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 4 : capacity_ * 2);
        }

        new (&data_[size_]) T(std::move(item));
        ++size_;
    }

    // Кількість елементів
    std::size_t size() const {
        return size_;
    }

    // Місткість контейнера
    std::size_t capacity() const {
        return capacity_;
    }

    // Перевірка на порожнечу
    bool empty() const {
        return size_ == 0;
    }

    // Доступ до елемента
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Catalog index out of range");
        }

        return data_[index];
    }

    // Ітератори
    iterator begin() {
        return data_;
    }

    iterator end() {
        return data_ ? data_ + size_ : data_;
    }

    const_iterator begin() const {
        return data_;
    }

    const_iterator end() const {
        return data_ ? data_ + size_ : data_;
    }

    const_iterator cbegin() const {
        return data_;
    }

    const_iterator cend() const {
        return data_ ? data_ + size_ : data_;
    }

private:
    // Знищення елементів
    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        size_ = 0;
    }

    // Зміна місткості
    void resize(std::size_t newCapacity) {
        T* newData = static_cast<T*>(
            ::operator new(sizeof(T) * newCapacity)
        );

        std::size_t newSize = 0;

        try {
            for (; newSize < size_; ++newSize) {
                new (&newData[newSize])
                    T(std::move_if_noexcept(data_[newSize]));
            }
        }
        catch (...) {
            for (std::size_t i = 0; i < newSize; ++i) {
                newData[i].~T();
            }

            ::operator delete(newData);
            throw;
        }

        clear();
        ::operator delete(data_);

        data_ = newData;
        size_ = newSize;
        capacity_ = newCapacity;
    }

    // Обмін даними
    void swap(Catalog& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};
