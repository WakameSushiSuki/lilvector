#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *ptr;
    size_t count;
    size_t cap;
    size_t elem_size;
} Vector;

Vector vector_new(size_t elem_size, size_t initial);
Vector vector_copy(Vector *v);
inline void *vector_at(Vector *v, size_t index);
inline void *vector_top(Vector *v);
inline void vector_read(Vector *v, void *out, size_t index);
inline void vector_write(Vector *v, size_t index, const void *data);
void vector_push(Vector *v, const void *data);
inline void vector_pop(Vector *v);
inline void vector_push_array(Vector *v, size_t count, const void* items);

#endif VECTOR_H
