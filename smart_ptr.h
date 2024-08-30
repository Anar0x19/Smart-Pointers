#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    void* ptr;
    void (*deleter)(void*);
} UniquePtr;

// Function declarations
UniquePtr make_unique_ptr(void* ptr, void (*deleter)(void*));
void* get_unique_ptr(const UniquePtr* up);
UniquePtr move_unique_ptr(UniquePtr* up);
void free_unique_ptr(UniquePtr* up);

// Function for array support
UniquePtr make_unique_array(void* ptr, size_t size);
void* get_unique_array(const UniquePtr* up);
void free_unique_array(UniquePtr* up);

// Helper functions
void* forbid_malloc(size_t size);

#endif // SMART_PTR_H

#ifdef SMART_PTR_IMPL

#include "smart_ptr.h"

static void default_deleter(void* ptr) {
    free(ptr);
}

UniquePtr make_unique_ptr(void* ptr, void (*deleter)(void*)) {
    UniquePtr up;
    up.ptr = ptr;
    up.deleter = deleter ? deleter : default_deleter;
    return up;
}

void* get_unique_ptr(const UniquePtr* up) {
    return up->ptr;
}

UniquePtr move_unique_ptr(UniquePtr* up) {
    UniquePtr new_up = { up->ptr, up->deleter };
    up->ptr = NULL;
    up->deleter = NULL;
    return new_up;
}

void free_unique_ptr(UniquePtr* up) {
    if (up->ptr) {
        up->deleter(up->ptr);
        up->ptr = NULL;
        up->deleter = NULL;
    }
}

UniquePtr make_unique_array(void* ptr, size_t size) {
    UniquePtr up;
    up.ptr = ptr;
    up.deleter = size > 0 ? free : NULL; // Free array if size is greater than 0
    return up;
}

void* get_unique_array(const UniquePtr* up) {
    return up->ptr;
}

void free_unique_array(UniquePtr* up) {
    if (up->ptr) {
        free(up->ptr);
        up->ptr = NULL;
        up->deleter = NULL;
    }
}

void* forbid_malloc(size_t size) {
    (void)size; // For the sake of example, just return NULL
    return NULL;
}

#endif // SMART_PTR_IMPL
