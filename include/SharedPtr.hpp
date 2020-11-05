// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_
#include <iostream>
#include <atomic>
#include <cstddef>
#include <utility>

template <typename T>
class SharedPtr {
  T *object = nullptr;
  std::atomic_size_t *counter;

 public:
  SharedPtr();

  explicit SharedPtr(T *ptr);

  // Конструктор копирования
  SharedPtr(const SharedPtr &ptr);

  // Конструктор перемещения
  SharedPtr(SharedPtr &&ptr) noexcept;

  ~SharedPtr();

  auto operator=(const SharedPtr &ptr) -> SharedPtr &;

  auto operator=(SharedPtr &&ptr) noexcept -> SharedPtr &;

  // проверяет, указывает ли указатель на объект
  explicit operator bool() const;

  auto operator*() const -> T &;

  auto operator-> () const -> T *;

  auto get() -> T *;

  void reset();

  void reset(T *ptr);

  void swap(SharedPtr &ptr);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  [[nodiscard]] auto use_count() const -> size_t;
};
template <typename T>
SharedPtr<T>::SharedPtr() {
    counter = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
    object = ptr;
    counter = new std::atomic_size_t(1);
}
// Конструктор копирования
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &ptr){
    counter = nullptr;
    *this = ptr;
}

// Конструктор перемещения
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&ptr) noexcept {
    counter = nullptr;
    *this = std::move(ptr);
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (!counter) return;

    if ((*counter)-- == 0) {
        delete object;
        delete counter;
    }
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr &ptr) -> SharedPtr & {
    if (this == &ptr) return *this;

    this->~SharedPtr();

    object = ptr.object;
    counter = ptr.counter;
    (*counter)++;

    return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr &&ptr) noexcept -> SharedPtr & {
    if (this == &ptr) return *this;

    this->~SharedPtr();

    object = ptr.object;
    counter = ptr.counter;
    ptr.object = nullptr;
    ptr.counter = nullptr;

    return *this;
}

// проверяет, указывает ли указатель на объект
template <typename T>
SharedPtr<T>::operator bool() const {
    return object != nullptr;
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T & {
    return *object;
}

template <typename T>
auto SharedPtr<T>::operator-> () const -> T * {
    return object;
}

template <typename T>
auto SharedPtr<T>::get() -> T * {
    return object;
}

template <typename T>
void SharedPtr<T>::reset() {
    *this = SharedPtr();
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
    *this = SharedPtr(ptr);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr &ptr) {
    std::swap(object, ptr.object);
    std::swap(counter, ptr.counter);
}

// возвращает количество объектов SharedPtr, которые ссылаются на тот же
// управляемый объект
template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
    if (counter)
        return *counter;
    else
        return 0;
}

#endif  // INCLUDE_SHAREDPTR_HPP_
