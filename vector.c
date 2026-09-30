// tiiiiny and HOPEFULLY not erroneous lil vector
// relies on gcc void* arithmetic extension, im too lazy to cast

#include "vector.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *ptr;
    size_t count;
    size_t cap;
    size_t elem_size;
} Vector;

Vector vector_new(size_t elem_size, size_t initial) {
    return (Vector) {
        .count = 0,
        .cap = initial,
        .elem_size = elem_size,
        .ptr = malloc(initial * elem_size),
    };
}

void vector_free(Vector *v) {
    free(v->ptr);
    *v = { 0 };
}

Vector vector_copy(const Vector *v) {
    Vector cpy = {
        .count = v->count,
        .cap = v->cap,
        .elem_size = v->elem_size,
        .ptr = malloc(v->cap * v->elem_size),
    };

    memcpy(cpy.ptr, v->ptr, v->count * v->elem_size);
    return cpy;
}

void *vector_at(const Vector *v, size_t index) {
    return v->ptr + index * v->elem_size;
}

void *vector_top(const Vector *v) {
    return vector_at(v, v->count - 1);
}

void vector_read(const Vector *v, void *out, size_t index) {
    memmove(out, vector_at(v, index), v->elem_size);
}

void vector_write(Vector *v, size_t index, const void *data) {
    memmove(vector_at(v, index), data, v->elem_size);
}

void vector_push(Vector *v, const void *data) {
    if (v->count >= v->cap)
        v->ptr = realloc(v->ptr, (v->cap *= 2) * v->elem_size);

    vector_write(v, v->count++, data);
}

void vector_push_array(Vector *v, size_t count, const void* items) {
    for (size_t i = 0; i < count; i++)
        vector_push(v, items + i * v->elem_size);
}

void vector_pop(Vector *v) {
    v->count--;
}
