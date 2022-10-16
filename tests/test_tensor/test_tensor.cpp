#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"

int main()
{
    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    SIMI::Tensor<SIMI::Float64> tensor2(2, 2);

    std::cout << ++tensor;
    std::cout << tensor + SIMI::Float64(2.);

    tensor=tensor + SIMI::Float64(2.);
    tensor2=tensor2 + 1.;

    std::cout << tensor2;
    std::cout << tensor2 * tensor;
    std::cout << tensor2.data().get() << "\n";
    std::cout << tensor2.clone().data().get();

    SIMI::Address_debug_2parms_get_result<SIMI::u64, SIMI::u64>((SIMI::u64)(tensor2.data().get()), (SIMI::u64)(tensor2.clone().data().get()));

    // std::cout << tensor;
    // std::cout << tensor2;
    // std::cout << tensor++;
    // std::cout << ++tensor;
    // std::cout << tensor--;
    // std::cout << --tensor;

    return 0;
}