#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"


void gausi_solve()
{
    std::cout << "gaussian_elimination work(A_3x3, b_3x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 4);
    std::cout << "Shape: " << tensor.get_shape() << std::endl;
    tensor.iloc(0, 0) = 3;
    tensor.iloc(0, 1) = 1;
    tensor.iloc(0, 2) = 2;
    tensor.iloc(0, 3) = 11;
    tensor.iloc(1, 0) = 6;
    tensor.iloc(1, 1) = 3;
    tensor.iloc(1, 2) = 4;
    tensor.iloc(1, 3) = 24;
    tensor.iloc(2, 0) = 3;
    tensor.iloc(2, 1) = 2;
    tensor.iloc(2, 2) = 5;
    tensor.iloc(2, 3) = 22;

    std::cout << "gausi matrix:" << std::endl;
    SIMI::Tensor<SIMI::Float64> gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(tensor);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;
}

int main()
{
    // 验证重定向
    SIMI::restdout2file("logs.txt");
    SIMI::reset_float_show_precision(15);

    gausi_solve();

    SIMI::mark_compare_datetime();

    return 0;
}
