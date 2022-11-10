#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

void qr_solve()
{
    std::cout << "The QR Iterator:\n";
    SIMI::Tensor<SIMI::Float64> a(3, 3);
    a.iloc(0, 0) = 8;
    a.iloc(0, 1) = -8;
    a.iloc(0, 2) = -4;
    a.iloc(1, 0) = 12;
    a.iloc(1, 1) = -15;
    a.iloc(1, 2) = -7;
    a.iloc(2, 0) = -18;
    a.iloc(2, 1) = 26;
    a.iloc(2, 2) = 12;
    SIMI::Tensor<SIMI::Float64> init_x(3, 1);
    init_x.iloc(0, 0) = 1.;
    init_x.iloc(1, 0) = 1.;
    init_x.iloc(2, 0) = 1.;

    SIMI::Tensor<SIMI::Float64> r(3, 3);
    std::cout << "A Matrix:" << std::endl;
    std::cout << a;
    std::cout << "Householder Matrix:" << std::endl;
    std::cout << SIMI::MATRIX::householder_transform(a, r);
}

void test_householder()
{
    std::cout << "The QR Iterator:\n";
    SIMI::Tensor<SIMI::Float64> a(3, 3);
    a.iloc(0, 0) = 8;
    a.iloc(0, 1) = -8;
    a.iloc(0, 2) = -4;
    a.iloc(1, 0) = 12;
    a.iloc(1, 1) = -15;
    a.iloc(1, 2) = -7;
    a.iloc(2, 0) = -18;
    a.iloc(2, 1) = 26;
    a.iloc(2, 2) = 12;
    std::cout << "A Matrix:" << std::endl;
    std::cout << a;

    SIMI::u32 iter_max = 25;
    SIMI::Tensor<SIMI::Float64> r;
    std::cout << "End QR Solve:\n";
    std::cout << "Q:\n";
    std::cout << SIMI::SOLVES::QR_solve(a, iter_max, r) << std::endl;
    std::cout << "R:\n";
    std::cout << r << std::endl;
}


int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("logs.txt");
    // qr_solve();
    test_householder();

    SIMI::mark_compare_datetime();

    return 0;
}
