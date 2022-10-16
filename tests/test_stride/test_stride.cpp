#include <iostream>
#include "basetype.h"
#include "stride.h"

int main()
{
    SIMI::Uint64 a[3] = {1,2,3};
    SIMI::u64 b[5] = {5, 4, 3, 2, 1};
    SIMI::Stride data(5, 5, 4, 3);
    SIMI::Stride data2(a, 3);
    SIMI::Stride data3(b, 5);
    SIMI::Stride data4;

    std::cout << data2;

    data2 = data;

    std::cout << data;
    std::cout << data2;
    std::cout << data3;
    std::cout << data4;

    return 0;
}