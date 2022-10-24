#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"

int main()
{
    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    SIMI::Tensor<SIMI::Float64> tensor2(2, 2);

    tensor.ones();
    tensor2.zeros();
    tensor.iloc(0, 0) = -327.75;

    std::cout << tensor;
    std::cout << tensor2;

    std::cout << tensor.at(0, 0) << std::endl;
    std::cout << (SIMI::Uint8)tensor.at(0, 0) << std::endl;
    std::cout << (SIMI::Uint32)tensor.at(0, 0) << std::endl;
    std::cout << (SIMI::Int32)tensor.at(0, 0) << std::endl;

    return 0;
}