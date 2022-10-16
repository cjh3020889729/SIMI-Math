#include <iostream>
#include "basetype.h"
#include "slice.h"

int main()
{
    SIMI::Uint32 a[3] = {1,2,3};
    SIMI::u32 b[5] = {5, 4, 3, 2, 1};
    SIMI::Slice data(5, 5, 4, 3);
    SIMI::Slice data2(a, 3);
    SIMI::Slice data3(b, 5);
    SIMI::Slice data4;

    std::cout << data2;

    data2 = data;

    std::cout << data;
    std::cout << data2;
    std::cout << data3;
    std::cout << data4;

    return 0;
}