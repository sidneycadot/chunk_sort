
/////////////////////////////
// chunk_sort_benchmark.cc //
/////////////////////////////

#include <random>
#include <iostream>
#include <chrono>

#include "sidney_sort.h"
#include "denis_sort.h"

using namespace std;
using uint8_vector_t = vector<uint8_t>;


static uint8_vector_t make_random_u8_vector(unsigned n, unsigned seed)
{
    default_random_engine eng(seed);
    uniform_int_distribution<unsigned> dist(0, 255);
    uint8_vector_t vec(n);
    for (auto & u : vec)
    {
        u = dist(eng) & 0xff;
    }
    return vec;
}


int main()
{
    unsigned number_of_elements_list[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};
    unsigned element_size_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 50};

    unsigned seed = 123456;
    unsigned number_of_repetitions = 10;

    const string method_list[] = {"sidney", "denis"};

    for (const auto & number_of_elements: number_of_elements_list)
    for (const auto & element_size: element_size_list)
    for (const auto & method : method_list)
    {
        for (unsigned rep = 0; rep < number_of_repetitions; ++rep)
        {
            uint8_vector_t vec = make_random_u8_vector(number_of_elements * element_size, seed);

            int64_t duration = -1;
            bool sort_ok = false;

            if (method == "sidney")
            {
                auto t0 = chrono::high_resolution_clock::now();
                sidney_sort(vec.data(), number_of_elements, element_size);
                auto t1 = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
                
                sort_ok = sidney_verify(vec.data(), number_of_elements, element_size); // verify result.
            }
            else if (method == "denis")
            {
                auto t0 = chrono::high_resolution_clock::now();
                denis_sort(vec.data(), number_of_elements, element_size);
                auto t1 = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
                
                sort_ok = sidney_verify(vec.data(), number_of_elements, element_size); // verify result.
            }

            cout << "number_of_elements " << number_of_elements << " element_size " << element_size << " method " << method << " sort_ok " << (sort_ok ? "YES" : "NO") << " duration " << duration << " [ns]" << endl;
        }
    }

    return 0;
}
