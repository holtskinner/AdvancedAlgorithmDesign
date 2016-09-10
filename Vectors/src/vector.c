#include "vector.h"

void init_vector(struct vector* v)
{
	v->data = malloc(sizeof(int) * INIT_VECTOR_SIZE);
	v->size = 0;
	v->capacity = INIT_VECTOR_SIZE;
}

int access_element_vector(struct vector* v, size_t index)
{
	if(index >= v->size)
		exit(OUT_OF_BOUNDS);
	return v->data[index];
}

void insert_element_vector(struct vector* v, int element_to_insert)
{
	if(v->capacity == v->size)
	{
            v->capacity *= 2;
            v->data = realloc(v->data, sizeof(int) * v->capacity);
		
	}
	v->data[v->size] = element_to_insert;
	v->size += 1;
}

int* vector_get_ptr(struct vector* v)
{
	return v->data;
}

void free_vector(struct vector* v)
{
	free(v->data);
	v->size = 0;
}
