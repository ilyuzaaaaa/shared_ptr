// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include "SharedPtr.hpp"

TEST(SharedPtr, Constructor) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto ptr_int = new int(buff_int);
    auto ptr_string = new std::string(buff_string);

    // Конструктор
    SharedPtr<int> shared_ptr_int(ptr_int);
    SharedPtr<std::string> shared_ptr_string(ptr_string);
    SharedPtr<int> shared_ptr_null;

    // Оператор копирования
    auto shared_ptr_int_Copy = shared_ptr_int;

    // Проверка
    EXPECT_EQ(shared_ptr_int_Copy.get(), ptr_int);
    EXPECT_EQ(shared_ptr_int_Copy.use_count(), 2);
}
TEST(SharedPtr, Move) {
    // Конструктор
    SharedPtr<int> shared_ptr_int(new int(100));
    SharedPtr<std::string> shared_ptr_string(new std::string("tests"));
    SharedPtr<int> shared_ptr_null;
    SharedPtr<int> shared_ptr_int_Copy(shared_ptr_int);
    // Конструктор (оператор) перемещения
    SharedPtr<int> shared_ptr_int_Move(std::move(shared_ptr_int_Copy));
    // Проверка
    EXPECT_EQ(*shared_ptr_int_Move.get(), 100);
    EXPECT_EQ(shared_ptr_int_Move.use_count(), 2);
}
TEST(SharedPtr, PointerToObj) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto ptr_int = new int(buff_int);
    auto ptr_string = new std::string(buff_string);

    // Конструктор
    SharedPtr<int> shared_ptr_int(ptr_int);
    SharedPtr<std::string> shared_ptr_string(ptr_string);
    SharedPtr<int> shared_ptr_null;
    // Указывает ли указатель на объект
    EXPECT_EQ(static_cast<bool>(shared_ptr_int), true);
    EXPECT_EQ(static_cast<bool>(shared_ptr_string), true);
    EXPECT_EQ(static_cast<bool>(shared_ptr_null), false);
}
TEST(SharedPtr, CounterValue) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto ptr_int = new int(buff_int);
    auto ptr_string = new std::string(buff_string);

    // Конструктор
    SharedPtr<int> shared_ptr_int(ptr_int);
    SharedPtr<std::string> shared_ptr_string(ptr_string);
    SharedPtr<int> shared_ptr_null;
    // Значение счётчика ссылок
    EXPECT_EQ(shared_ptr_int.use_count(), 1);
    EXPECT_EQ(shared_ptr_string.use_count(), 1);
    EXPECT_EQ(shared_ptr_null.use_count(), 0);
}
TEST(SharedPtr, ObjValue) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto ptr_int = new int(buff_int);
    auto ptr_string = new std::string(buff_string);

    // Конструктор
    SharedPtr<int> shared_ptr_int(ptr_int);
    SharedPtr<std::string> shared_ptr_string(ptr_string);
    SharedPtr<int> shared_ptr_null;
    // Значение объекта (ссылка)
    EXPECT_EQ(*shared_ptr_int, buff_int);
    EXPECT_EQ(*shared_ptr_string, buff_string);
}
TEST(SharedPtr, ObjPointer) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto ptr_int = new int(buff_int);
    auto ptr_string = new std::string(buff_string);

    // Конструктор
    SharedPtr<int> shared_ptr_int(ptr_int);
    SharedPtr<std::string> shared_ptr_string(ptr_string);
    SharedPtr<int> shared_ptr_null;
    // Указатель на объект
    EXPECT_EQ(shared_ptr_int.get(), ptr_int);
    EXPECT_EQ(*shared_ptr_string.get(), "tests");
    EXPECT_EQ(shared_ptr_null.get(), nullptr);

    // Указатель на объект
    EXPECT_EQ(shared_ptr_int.operator->(), ptr_int);
    EXPECT_EQ(shared_ptr_string->empty(), ptr_string->empty());
    EXPECT_EQ(shared_ptr_null.operator->(), nullptr);
}
TEST(SharedPtr, Methods) {
    // Конструктор
    SharedPtr<int> shared_ptr_int(new int(100));
    SharedPtr<std::string> shared_ptr_string(new std::string("tests"));
    SharedPtr<int> shared_ptr_null;
    // Свап
    shared_ptr_int.swap(shared_ptr_null);

    // Проверка
    EXPECT_EQ(shared_ptr_int.get(), nullptr);
    EXPECT_EQ(*shared_ptr_null.get(), 100);

    // Ресет
    shared_ptr_int.reset(new int(100));
    shared_ptr_null.reset();

    // Проверка
    EXPECT_EQ(*shared_ptr_int.get(), 100);
    EXPECT_EQ(shared_ptr_null.get(), nullptr);
}
