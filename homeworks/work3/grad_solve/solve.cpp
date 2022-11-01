#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

void gradient_descent_solve()
{
    SIMI::Tensor<SIMI::Float64> a(3, 3);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
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

    SIMI::u32 iter_max = 100;
    SIMI::float64 error_limit = 1e-7;
    SIMI::SOLVES::gradient_descent_solve(a, b, x, iter_max, error_limit);
    std::cout << "X:\n" << x;
}

void conjugate_gradient_descent_solve()
{
    SIMI::Tensor<SIMI::Float64> a(3, 3);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
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

    SIMI::SOLVES::conjugate_gradient_descent_solve(a, b, x);
    std::cout << "X:\n" << x;
}

int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("gradient_logs.txt");
    gradient_descent_solve();

    SIMI::restdout2file("conjugate_logs.txt");
    conjugate_gradient_descent_solve();

    SIMI::mark_compare_datetime();

    return 0;
}
