#include <iostream>
#include "basetype.h"

int main()
{
    SIMI::Float32 a(1);
    SIMI::Float64 b(2);
    SIMI::Int8 c(3);
    SIMI::Int16 d(4);
    SIMI::Int32 e(5);
    SIMI::Int64 f(6);
    SIMI::Uint8 g(7);
    SIMI::Uint16 h(8);
    SIMI::Uint32 i(9);
    SIMI::Uint64 j(10);
    SIMI::Bool k(true);

    std::cout << "Init Success.\n";
    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "c: " << c << "\n";
    std::cout << "d: " << d << "\n";
    std::cout << "e: " << e << "\n";
    std::cout << "f: " << f << "\n";
    std::cout << "g: " << g << "\n";
    std::cout << "h: " << h << "\n";
    std::cout << "i: " << i << "\n";
    std::cout << "j: " << j << "\n";
    std::cout << "k: " << k << "\n";

    return 0;
}