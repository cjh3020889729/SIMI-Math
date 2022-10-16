#include <iostream>
#include "basetype.h"
#include "slice.h"

int main()
{
    SIMI::Shape shape(2, 8, 6, 3);
    SIMI::Stride stride(shape);
    SIMI::Slice start_l(0, 0, 0, 0);
    SIMI::Slice end_l(0, 0, 0, 2);
    SIMI::SliceTuple slice_tuple(start_l, end_l);

    std::cout << shape;
    std::cout << stride;
    std::cout << start_l;
    std::cout << end_l;
    std::cout << slice_tuple;

    std::cout << "The start_location: " << start_l.get_location(shape, stride) << "\n";
    std::cout << "The end_location: " << end_l.get_location(shape, stride) << "\n";
    std::cout << "The [end_location, start_location) elemment: " 
              << slice_tuple.end().get_location(shape, stride) - \
              slice_tuple.start().get_location(shape, stride) + 1 \
              << "\n"; // 左闭右开

    return 0;
}