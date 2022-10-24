#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"


void lu_solve()
{
    std::cout << "LU solve work(A_3x3, b_3x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> a_tensor(3, 3);
    std::cout << "Shape: " << a_tensor.get_shape() << std::endl;
    a_tensor.iloc(0, 0) = 3;
    a_tensor.iloc(0, 1) = 1;
    a_tensor.iloc(0, 2) = 2;
    a_tensor.iloc(1, 0) = 6;
    a_tensor.iloc(1, 1) = 3;
    a_tensor.iloc(1, 2) = 4;
    a_tensor.iloc(2, 0) = 3;
    a_tensor.iloc(2, 1) = 2;
    a_tensor.iloc(2, 2) = 5;
    SIMI::Tensor<SIMI::Float64> b_tensor(3, 1);
    b_tensor.iloc(0, 0) = 11;
    b_tensor.iloc(1, 0) = 24;
    b_tensor.iloc(2, 0) = 22;

    SIMI::Tensor<SIMI::Float64> l_tensor(a_tensor), u_tensor(a_tensor);
    if(!(SIMI::MATRIX::lu_directly_split_transform(a_tensor, l_tensor, u_tensor).tobool())) {
        std::cout << "Info: The LU split is failed.\n";
    }
    std::cout << "L Matrix:\n";
    std::cout << l_tensor << std::endl;
    std::cout << "U Matrix:\n";
    std::cout << u_tensor << std::endl;

    std::cout << "LU Solve Result:\n";
    std::cout << SIMI::SOLVES::lu_solve(l_tensor, u_tensor, b_tensor) << std::endl;
}

int main()
{
    // 验证重定向
    SIMI::restdout2file("logs.txt");
    SIMI::reset_float_show_precision(15);

    lu_solve();

    SIMI::mark_compare_datetime();

    return 0;
}
