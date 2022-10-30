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

void generate_sparse_matrix_for_gauss_elimination(
                            SIMI::u32 N,
                            SIMI::Tensor<SIMI::Float64> &a,
                            SIMI::Tensor<SIMI::Float64> &b)
{
    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    a.zeros();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) a.iloc(i, j) = 3.;
            else if(j == (i-1) || j == (i+1)) a.iloc(i, j) = -1.;
            else if(j == (N-i-1)) a.iloc(i, j) = 1./2.;
        }
    }
    b = SIMI::MATRIX::multiply(a, certain_x);
    for(int i = 0; i < N; i++) a.iloc(i, N) = b.at(i, 0);
}

void gausi_solve(SIMI::u32 N)
{
    //std::cout << "gaussian_elimination work(A_" << N << "x" << N << ", " "b_" << N << "x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    SIMI::Tensor<SIMI::Float64> a(N, N+1);
    SIMI::Tensor<SIMI::Float64> b(N, 1);
    generate_sparse_matrix_for_gauss_elimination(N, a, b);
    //std::cout << "Shape: " << a.get_shape() << std::endl;

    //std::cout << "gausi matrix:" << std::endl;
    SIMI::Tensor<SIMI::Float64> gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(a);
    //std::cout << gausi_tensor << std::endl;
    //std::cout << "gausi solve:" << std::endl;
    SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor);
    //std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;
    //std::cout << "certain solve:\n" << certain_x << std::endl;
    
}

void generate_sparse_matrix_for_jacobi_iterator(
                            SIMI::u32 N,
                            SIMI::Tensor<SIMI::Float64> &a,
                            SIMI::Tensor<SIMI::Float64> &b)
{
    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    a.zeros();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) a.iloc(i, j) = 3.;
            else if(j == (i-1) || j == (i+1)) a.iloc(i, j) = -1.;
            else if(j == (N-i-1)) a.iloc(i, j) = 1./2.;
        }
    }
    b = SIMI::MATRIX::multiply(a, certain_x);
}


void jacobi_iterator_solve(SIMI::u32 N)
{
    //std::cout << "jacobi_iterator_solve work(A_" << N << "x" << N << ", " "b_" << N << "x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    SIMI::Tensor<SIMI::Float64> x(N, 1);
    SIMI::Tensor<SIMI::Float64> a(N, N);
    SIMI::Tensor<SIMI::Float64> b(N, 1);
    generate_sparse_matrix_for_jacobi_iterator(N, a, b);
    //std::cout << "Shape: " << a.get_shape() << std::endl;
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(N, N);
    strict_diagonal_dominance_tensor.zeros();
    //std::cout << "Input Tensor:\n" << a << std::endl;
    //std::cout << "Input x:\n" << x << std::endl;
    //std::cout << "Input b:\n" << b << std::endl;

    //std::cout << "To Strict Diagonal Dominance Matrix(" << N << ", " << N << "):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        a,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    //std::cout << strict_diagonal_dominance_tensor;
    //std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> l_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> u_tensor(N, N);
    //std::cout << "Jacobi_Matrix_Split(" << N << ", " << N << "):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    //std::cout << "D Tensor:\n" << d_tensor << std::endl;
    //std::cout << "L Tensor:\n" << l_tensor << std::endl;
    //std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 error_limit = 1e-7;
    SIMI::u32 max_iters = 50;
    SIMI::SOLVES::jacobi_iterator_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        error_limit,
        max_iters,
        false
    );
    //std::cout << "Iterator Solve Result:\n" << x;
    //std::cout << "certain solve:\n" << certain_x << std::endl;
}

void gauss_seidel_iterator_solve(SIMI::u32 N)
{
    //std::cout << "gauss_seidel_iterator_solve work(A_" << N << "x" << N << ", " "b_" << N << "x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    SIMI::Tensor<SIMI::Float64> x(N, 1);
    SIMI::Tensor<SIMI::Float64> a(N, N);
    SIMI::Tensor<SIMI::Float64> b(N, 1);
    generate_sparse_matrix_for_jacobi_iterator(N, a, b);
    //std::cout << "Shape: " << a.get_shape() << std::endl;
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(N, N);
    strict_diagonal_dominance_tensor.zeros();
    //std::cout << "Input Tensor:\n" << a << std::endl;
    //std::cout << "Input x:\n" << x << std::endl;
    //std::cout << "Input b:\n" << b << std::endl;

    //std::cout << "To Strict Diagonal Dominance Matrix(" << N << ", " << N << "):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        a,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    //std::cout << strict_diagonal_dominance_tensor;
    //std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> l_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> u_tensor(N, N);
    //std::cout << "Jacobi_Matrix_Split(" << N << ", " << N << "):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    //std::cout << "D Tensor:\n" << d_tensor << std::endl;
    //std::cout << "L Tensor:\n" << l_tensor << std::endl;
    //std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 error_limit = 1e-7;
    SIMI::u32 max_iters = 60;
    SIMI::SOLVES::gauss_seidel_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        error_limit,
        max_iters,
        false
    );
    //std::cout << "Iterator Solve Result:\n" << x;
    //std::cout << "certain solve:\n" << certain_x << std::endl;
}

void sor_iterator_solve(SIMI::u32 N, SIMI::float64 w_value)
{
    //std::cout << "sor_iterator_solve work(A_" << N << "x" << N << ", " "b_" << N << "x1):" << std::endl;

    SIMI::Tensor<SIMI::Float64> certain_x(N, 1);
    for(int i = 0; i < N; i++) certain_x.iloc(i) = i; // init certain x
    SIMI::Tensor<SIMI::Float64> x(N, 1);
    SIMI::Tensor<SIMI::Float64> a(N, N);
    SIMI::Tensor<SIMI::Float64> b(N, 1);
    generate_sparse_matrix_for_jacobi_iterator(N, a, b);
    //std::cout << "Shape: " << a.get_shape() << std::endl;
    SIMI::Tensor<SIMI::Float64> strict_diagonal_dominance_tensor(N, N);
    strict_diagonal_dominance_tensor.zeros();
    //std::cout << "Input Tensor:\n" << a << std::endl;
    //std::cout << "Input x:\n" << x << std::endl;
    //std::cout << "Input b:\n" << b << std::endl;

    //std::cout << "To Strict Diagonal Dominance Matrix(" << N << ", " << N << "):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        a,
        b,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }
    //std::cout << strict_diagonal_dominance_tensor;
    //std::cout << "b:\n" << b << std::endl;

    SIMI::Tensor<SIMI::Float64> d_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> l_tensor(N, N);
    SIMI::Tensor<SIMI::Float64> u_tensor(N, N);
    //std::cout << "Jacobi_Matrix_Split(" << N << ", " << N << "):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        strict_diagonal_dominance_tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    //std::cout << "D Tensor:\n" << d_tensor << std::endl;
    //std::cout << "L Tensor:\n" << l_tensor << std::endl;
    //std::cout << "U Tensor:\n" << u_tensor << std::endl;

    SIMI::float64 w = w_value;
    SIMI::float64 error_limit = 1e-7;
    SIMI::u32 max_iters = 60;
    SIMI::SOLVES::sor_iterate_solve(
        d_tensor,
        l_tensor,
        u_tensor,
        x,
        b,
        w,
        error_limit,
        max_iters,
        false
    );
    //std::cout << "Iterator Solve Result:\n" << x;
    //std::cout << "certain solve:\n" << certain_x << std::endl;
}


int main()
{
    // 验证重定向
    SIMI::restdout2file("logs.txt");
    SIMI::reset_float_show_precision(15);

    clock_t start,end;
    SIMI::u32 base_size = 10;
    SIMI::u32 exp_max = 3;

    // 受制于矩阵运算效率，100以后的大小，高斯消元运算开销过大
    for(int i = 1; i <= exp_max; i++) {
        SIMI::float64 iter_cost_time = 0.;
        SIMI::u32 matrix_size = (int)pow(base_size, i);
        std::cout << "Start solve matrix: " << matrix_size << "x" << matrix_size << std::endl;
        
        start = clock();

        if(i <= 2)
        gausi_solve(matrix_size);

        end = clock();
        std::cout << "1.Gausi solve(" << matrix_size << "x" << matrix_size << ") cost time=" << (SIMI::float64)(end-start) / CLK_TCK << "s.\n" << std::endl;
        iter_cost_time += (SIMI::float64)(end-start) / CLK_TCK;


        start = clock();

        if(i <= 3)
        jacobi_iterator_solve(matrix_size);

        end = clock();
        std::cout << "2.Jacobi iterator solve(" << matrix_size << "x" << matrix_size << ")cost time=" << (SIMI::float64)(end-start) / CLK_TCK << "s.\n" << std::endl;
        iter_cost_time += (SIMI::float64)(end-start) / CLK_TCK;
    

        start = clock();

        if(i <= 3)
        gauss_seidel_iterator_solve(matrix_size);

        end = clock();
        std::cout << "3.Gauss seidel iterator solve(" << matrix_size << "x" << matrix_size << ")cost time=" << (SIMI::float64)(end-start) / CLK_TCK << "s.\n" << std::endl;
        iter_cost_time += (SIMI::float64)(end-start) / CLK_TCK;


        start = clock();

        if(i <= 3)
        sor_iterator_solve(matrix_size, 1.0);

        end = clock();
        std::cout << "4.SOR iterator solve(" << matrix_size << "x" << matrix_size << ")cost time=" << (SIMI::float64)(end-start) / CLK_TCK << "s.\n" << std::endl;
        iter_cost_time += (SIMI::float64)(end-start) / CLK_TCK;

        std::cout << "End solve matrix: " << matrix_size << "x" << matrix_size << std::endl;
        std::cout << "The Iter Cost Total Time: " << iter_cost_time << "s.\n";

        Sleep(100);
        std::cout << "\n\n";
    }

    SIMI::mark_compare_datetime();

    return 0;
}
