
///////////////////
// sidney_sort.h //
///////////////////

#ifndef SIDNEY_SORT_H
#define SIDNEY_SORT_H

#include <cstdint>

// Perform an in-place sort.
void sidney_sort(uint8_t * data, unsigned number_of_elements, unsigned element_size);

// Verify that an array is sorted.
bool sidney_verify(uint8_t * data, unsigned number_of_elements, unsigned element_size);

#endif // SIDNEY_SORT_H
