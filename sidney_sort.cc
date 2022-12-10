
////////////////////
// sidney_sort.cc //
////////////////////

#include <cstdlib>

#include "sidney_sort.h"

// Old-school way of getting a parameter to the sidney_compare() function.
// NOTE: this makes our sidney_sort and sidney_verify unsafe if multiple threads can call it with a different element_size parameter.

static unsigned sidney_compare_element_size;

// Old-school qsort() compare function for big-endian comparison.
static int sidney_compare(const void *vpa, const void *vpb)
{
    const uint8_t * const pa = static_cast<const uint8_t *>(vpa);
    const uint8_t * const pb = static_cast<const uint8_t *>(vpb);
    
    for (unsigned i = 0 ; i < sidney_compare_element_size; ++i)
    {
        uint8_t a = pa[i];
        uint8_t b = pb[i];

        if (a < b)
        {
            return -1;
        }
        if (a > b)
        {
            return +1;
        }
    }
    return 0;
}

void sidney_sort(uint8_t * data, unsigned number_of_elements, unsigned element_size)
{
    sidney_compare_element_size = element_size;
    qsort(data, number_of_elements, element_size, sidney_compare);
}

bool sidney_verify(uint8_t * data, unsigned number_of_elements, unsigned element_size)
{
    sidney_compare_element_size = element_size;
    for (unsigned i = 0; i < number_of_elements - 1; ++i)
    {
        if (sidney_compare(&data[i * element_size], &data[(i + 1) * element_size]) > 0)
        {
            return false;
        }
    }
    return true; // all ok
}
