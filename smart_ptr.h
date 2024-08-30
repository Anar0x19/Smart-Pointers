#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <stdlib.h>
#include <stdio.h>

// Структура для unique_ptr
typedef struct {
    void* ptr;
} UniquePtr;

// Функция для создания unique_ptr
UniquePtr make_unique_ptr(void* ptr) {
    UniquePtr up;
    up.ptr = ptr;
    return up;
}

// Функция для освобождения памяти unique_ptr
void free_unique_ptr(UniquePtr* up) {
    if (up->ptr) {
        free(up->ptr);
        up->ptr = NULL;
    }
}

// Функция для получения доступа к объекту
void* get_unique_ptr(UniquePtr* up) {
    return up->ptr;
}

// Функция для передачи владения (move semantics)
UniquePtr move_unique_ptr(UniquePtr* up) {
    UniquePtr new_up = *up;
    up->ptr = NULL;
    return new_up;
}

// Функция, запрещающая выделение динамической памяти
void* forbid_malloc(size_t size) {
    printf("Dynamic memory allocation is forbidden!\n");
    return NULL;
}

#endif 
