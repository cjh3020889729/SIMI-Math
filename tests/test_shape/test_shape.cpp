#include <iostream>
#include "basetype.h"
#include "shape.h"

int main()
{
    SIMI::Uint32 a[3] = {1,2,3};
    SIMI::u32 b[5] = {5, 4, 3, 2, 1};
    SIMI::Shape data(5, 5, 4, 3);
    SIMI::Shape data2(a, 3);
    SIMI::Shape data3(b, 5);
    SIMI::Shape data4;

    std::cout << data2;

    data2 = data;

    std::cout << data;
    std::cout << data2;
    std::cout << data3;
    std::cout << data4;

    return 0;
}