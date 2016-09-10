#include "../include/vector.h"

int main()
{
	// vector of floats
	struct vector v;
	init_vector(&v); 
	insert_element_vector(&v, 5);

	int ele = access_element_vector(&v, 0);
	printf("%d\n", ele);
}
