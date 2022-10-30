#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

// 节省时间，不打印输出
void jacobi_iterator_solve()
{
    std::cout << "Jacobi Iterator Solve(3, 3):" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(3, 3);
    tensor.iloc(0, 0) = 1;
    tensor.iloc(0, 1) = -8;
    tensor.iloc(0, 2) = -2;
    tensor.iloc(1, 0) = 1;
    tensor.iloc(1, 1) = 1;
    tensor.iloc(1, 2) = 5;
    tensor.iloc(2, 0) = 3;
    tensor.iloc(2, 1) = -1;
    tensor.iloc(2, 2) = 1;
    b.iloc(0, 0) = 1;
    b.iloc(1, 0) = 4;
    b.iloc(2, 0) = -2;
    strict_diagonal_dominance_tensor.zeros();
    std::cout << "Input Tensor:\n" << tensor << std::endl;
    std::cout << "Input x:\n" << x << std::endl;
    std::cout << "Input b:\n" << b << std::endl;

    std::cout << "To Strict Diagonal Dominance Matrix(3, 3):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        tensor,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    std::cout << strict_diagonal_dominance_tensor;
    std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> l_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> u_tensor(3, 3);
    std::cout << "Jacobi_Matrix_Split(3, 3):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    std::cout << "D Tensor:\n" << d_tensor << std::endl;
    std::cout << "L Tensor:\n" << l_tensor << std::endl;
    std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 error_limit = 1e-8;
    SIMI::u32 max_iters = 30;
    std::cout << "Jacobi Iterator Solve(3, 3):" << std::endl;
    SIMI::SOLVES::jacobi_iterator_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        error_limit,
        max_iters,
        true
    );
    std::cout << "Iterator Solve Result:\n" << x;
}

void gauss_seidel_iterator_solve()
{
    std::cout << "Gauss Seidel Iterator Solve(3, 3):" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(3, 3);
    tensor.iloc(0, 0) = 1;
    tensor.iloc(0, 1) = -8;
    tensor.iloc(0, 2) = -2;
    tensor.iloc(1, 0) = 1;
    tensor.iloc(1, 1) = 1;
    tensor.iloc(1, 2) = 5;
    tensor.iloc(2, 0) = 3;
    tensor.iloc(2, 1) = -1;
    tensor.iloc(2, 2) = 1;
    b.iloc(0, 0) = 1;
    b.iloc(1, 0) = 4;
    b.iloc(2, 0) = -2;
    strict_diagonal_dominance_tensor.zeros();
    std::cout << "Input Tensor:\n" << tensor << std::endl;
    std::cout << "Input x:\n" << x << std::endl;
    std::cout << "Input b:\n" << b << std::endl;

    std::cout << "To Strict Diagonal Dominance Matrix(3, 3):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        tensor,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    std::cout << strict_diagonal_dominance_tensor;
    std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> l_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> u_tensor(3, 3);
    std::cout << "Jacobi_Matrix_Split(3, 3):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    std::cout << "D Tensor:\n" << d_tensor << std::endl;
    std::cout << "L Tensor:\n" << l_tensor << std::endl;
    std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 error_limit = 1e-8;
    SIMI::u32 max_iters = 30;
    std::cout << "Gauss Seidel Iterator Solve(3, 3):" << std::endl;
    SIMI::SOLVES::gauss_seidel_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        error_limit,
        max_iters,
        true
    );
    std::cout << "Iterator Solve Result:\n" << x;
}


void sor_iterator_solve(SIMI::float64 w_value)
{
    std::cout << "SOR Iterator Solve(3, 3) - W(" << w_value << "):" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> x(3, 1);
    SIMI::Tensor<SIMI::Float64> b(3, 1);
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(3, 3);
    tensor.iloc(0, 0) = 1;
    tensor.iloc(0, 1) = -8;
    tensor.iloc(0, 2) = -2;
    tensor.iloc(1, 0) = 1;
    tensor.iloc(1, 1) = 1;
    tensor.iloc(1, 2) = 5;
    tensor.iloc(2, 0) = 3;
    tensor.iloc(2, 1) = -1;
    tensor.iloc(2, 2) = 1;
    b.iloc(0, 0) = 1;
    b.iloc(1, 0) = 4;
    b.iloc(2, 0) = -2;
    strict_diagonal_dominance_tensor.zeros();
    std::cout << "Input Tensor:\n" << tensor << std::endl;
    std::cout << "Input x:\n" << x << std::endl;
    std::cout << "Input b:\n" << b << std::endl;

    std::cout << "To Strict Diagonal Dominance Matrix(3, 3):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        tensor,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    std::cout << strict_diagonal_dominance_tensor;
    std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> l_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> u_tensor(3, 3);
    std::cout << "Jacobi_Matrix_Split(3, 3):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    std::cout << "D Tensor:\n" << d_tensor << std::endl;
    std::cout << "L Tensor:\n" << l_tensor << std::endl;
    std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 w = w_value;
    SIMI::float64 error_limit = 1e-8;
    SIMI::u32 max_iters = 30;
    std::cout << "SOR Iterator Solve(3, 3):" << std::endl;
    SIMI::SOLVES::sor_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        w,
        error_limit,
        max_iters,
        true
    );
    std::cout << "Iterator Solve Result:\n" << x;
}


int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("jacobi_logs.txt");
    jacobi_iterator_solve();

    SIMI::restdout2file("gauss_logs.txt");
    gauss_seidel_iterator_solve();

    SIMI::restdout2file("sor_logs.txt");
    // w: from 0.2 --> 1.6
    for(int i = 1; i <= 8; i++) sor_iterator_solve(i * 0.2), std::cout << std::endl;

    SIMI::mark_compare_datetime();

    return 0;
}
