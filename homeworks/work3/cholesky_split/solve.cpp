#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

void cholesky_split_solve()
{
    SIMI::Tensor<SIMI::Float64> a(3, 3);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
    SIMI::Tensor<SIMI::Float64> l(3, 3);
    a.iloc(0, 0) = 4;
    a.iloc(0, 1) = -2;
    a.iloc(0, 2) = 0;
    a.iloc(1, 0) = -2;
    a.iloc(1, 1) = 2;
    a.iloc(1, 2) = -1;
    a.iloc(2, 0) = 0;
    a.iloc(2, 1) = -1;
    a.iloc(2, 2) = 5;
    b.iloc(0, 0) = 0;
    b.iloc(1, 0) = 3;
    b.iloc(2, 0) = -7;
    if(!SIMI::MATRIX::cholesky_split(a, l)) {
        std::cout << "The cholesky split failed." << std::endl;
    }
    std::cout << "A:\n" << a;
    std::cout << "L:\n" << l;

    SIMI::SOLVES::cholesky_split_solve(l, b, x);
    std::cout << "X:\n" << x;
}

int main()
{
    // 验证重定向
    SIMI::restdout2file("logs.txt");
    SIMI::reset_float_show_precision(15);

    cholesky_split_solve();

    SIMI::mark_compare_datetime();

    return 0;
}
