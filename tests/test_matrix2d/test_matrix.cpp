#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

void test_tensor_create_and_print();
void test_get_row_and_col();
void test_exchange_cols_and_rows();
void test_transpose();
void test_multiply();
void test_to_upper_triangular();
void test_gausi_solve();
void test_lu_split();
void test_jacobi_matrix_split();
void test_to_strict_diagonal_dominance_matrix();
void test_matrix_inverse();
void test_jacobi_iterator_solve();
void test_gauss_seidel_iterator_solve();
void test_sor_iterator_solve();
void test_hilbert_generate();


int main()
{
    // 验证重定向
    SIMI::restdout2file("logs.txt");

    // Tensor创建与输出验证
    // test_tensor_create_and_print();
    // Tensor行与列获取验证
    // test_get_row_and_col();
    // Tensor行列交换验证
    // test_exchange_cols_and_rows();
    // Tensor转置验证
    // test_transpose();
    // Tensor矩阵乘法验证
    // test_multiply();
    // Tensor上三角变换验证
    // test_to_upper_triangular();

    // 下三角验证
    // std::cout << SIMI::MATRIX::to_lower_triangular_matrix(tensor);
    // 最简行列式验证
    // std::cout << SIMI::MATRIX::to_simplest_determinant(tensor);
    // 高斯消元验证
    // test_gausi_solve();
    // LU分解验证
    // test_lu_split();
    // jacobi矩阵分解
    // test_jacobi_matrix_split();
    // 严格对角占优矩阵转换
    // test_to_strict_diagonal_dominance_matrix();
    // 矩阵的逆
    // test_matrix_inverse();
    // jacobi迭代求解
    // test_jacobi_iterator_solve();
    // gauss seidel迭代求解
    test_gauss_seidel_iterator_solve();
    // sor迭代求解
    test_sor_iterator_solve();




    // hilbert生成
    //test_hilbert_generate();

    return 0;
}

void test_tensor_create_and_print()
{
    std::cout << "create tensor test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    SIMI::Tensor<SIMI::Float64> tensor2(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;
    for(int i = 2; i < 6; i++) tensor2.iloc(i-2) = i;

    std::cout << tensor << std::endl;
    std::cout << tensor2 << std::endl;
}

void test_get_row_and_col()
{
    std::cout << "get_row_and_col test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;

    std::cout << "origin input:" << std::endl;
    std::cout << tensor << std::endl;

    std::cout << "get_col test:" << std::endl;
    std::cout << SIMI::MATRIX::get_col(tensor, 1) << std::endl;
    std::cout << "get_row test:" << std::endl;
    std::cout << SIMI::MATRIX::get_row(tensor, 1) << std::endl;
}

void test_exchange_cols_and_rows()
{
    std::cout << "exchange_cols_and_rows test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;

    std::cout << "origin input:" << std::endl;
    std::cout << tensor << std::endl;

    std::cout << "exchange_col test:" << std::endl;
    SIMI::MATRIX::exchange_col(tensor, 0, 1);
    std::cout << tensor<< std::endl;
    SIMI::MATRIX::exchange_row(tensor, 0, 1);
    std::cout << tensor << std::endl;
}

void test_transpose()
{
    std::cout << "transpose test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;

    std::cout << "origin input:" << std::endl;
    std::cout << tensor << std::endl;

    std::cout << SIMI::MATRIX::transpose(tensor) << std::endl;
}

void test_multiply()
{
    std::cout << "multiply test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    SIMI::Tensor<SIMI::Float64> tensor2(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;
    for(int i = 2; i < 6; i++) tensor2.iloc(i-2) = i;

    std::cout << "origin input:" << std::endl;
    std::cout << tensor << std::endl;
    std::cout << tensor2 << std::endl;

    std::cout << SIMI::MATRIX::multiply(tensor, tensor2) << std::endl;;
}

void test_to_upper_triangular()
{
    std::cout << "to_upper_triangular test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(2, 2);
    for(int i = 0; i < 4; i++) tensor.iloc(i) = i;

    std::cout << "origin input:" << std::endl;
    std::cout << tensor << std::endl;

    std::cout << SIMI::MATRIX::to_upper_triangular_matrix(tensor) << std::endl;;
}

void test_gausi_solve()
{
    std::cout << "gaussian_elimination test1:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 4);
    std::cout << "Shape: " << tensor.get_shape() << std::endl;
    tensor.iloc(0, 0) = 2;
    tensor.iloc(0, 1) = 1;
    tensor.iloc(0, 2) = -1;
    tensor.iloc(0, 3) = 8;
    tensor.iloc(1, 0) = -3;
    tensor.iloc(1, 1) = -1;
    tensor.iloc(1, 2) = 2;
    tensor.iloc(1, 3) = -11;
    tensor.iloc(2, 0) = -2;
    tensor.iloc(2, 1) = 1;
    tensor.iloc(2, 2) = 2;
    tensor.iloc(2, 3) = -3;

    std::cout << "gausi matrix:" << std::endl;
    SIMI::Tensor<SIMI::Float64> gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(tensor);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;

    std::cout << "gaussian_elimination test2:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor2(2, 3);
    std::cout << "Shape: " << tensor2.get_shape() << std::endl;
    tensor2.iloc(0, 0) = 1;
    tensor2.iloc(0, 1) = 1;
    tensor2.iloc(0, 2) = 3;
    tensor2.iloc(1, 0) = 1;
    tensor2.iloc(1, 1) = -1;
    tensor2.iloc(1, 2) = 1;

    std::cout << "gausi matrix:" << std::endl;
    gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(tensor2);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;
}

void test_lu_split()
{
    std::cout << "LU Directly Split test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> l_tensor(3, 3);
    l_tensor.zeros();
    SIMI::Tensor<SIMI::Float64> u_tensor(3, 3);
    u_tensor.zeros();
    std::cout << "Shape: " << tensor.get_shape() << std::endl;
    tensor.iloc(0, 0) = 2;
    tensor.iloc(0, 1) = 1;
    tensor.iloc(0, 2) = -1;
    tensor.iloc(1, 0) = -3;
    tensor.iloc(1, 1) = -1;
    tensor.iloc(1, 2) = 2;
    tensor.iloc(2, 0) = -2;
    tensor.iloc(2, 1) = 1;
    tensor.iloc(2, 2) = 2;

    std::cout << "origin matrix:" << std::endl;
    std::cout << tensor << std::endl;
    std::cout << "l matrix:" << std::endl;
    std::cout << l_tensor << std::endl;
    std::cout << "u matrix:" << std::endl;
    std::cout << u_tensor << std::endl;

    std::cout << "LU Split State: " << SIMI::MATRIX::lu_directly_split_transform(
        tensor, l_tensor, u_tensor) << std::endl;
    
    std::cout << "update l matrix:" << std::endl;
    std::cout << l_tensor << std::endl;
    std::cout << "update u matrix:" << std::endl;
    std::cout << u_tensor << std::endl;
}

void test_jacobi_matrix_split()
{
    std::cout << "Jacobi_Matrix_Split(3, 3) test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> d_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> l_tensor(3, 3);
    SIMI::Tensor<SIMI::Float64> u_tensor(3, 3);
    tensor.iloc(0, 0) = 3;
    tensor.iloc(0, 1) = -1;
    tensor.iloc(0, 2) = 1;
    tensor.iloc(1, 0) = 1;
    tensor.iloc(1, 1) = -8;
    tensor.iloc(1, 2) = -2;
    tensor.iloc(2, 0) = 1;
    tensor.iloc(2, 1) = 1;
    tensor.iloc(2, 2) = 5;
    d_tensor.zeros();
    l_tensor.zeros();
    u_tensor.zeros();
    std::cout << "Input Tensor:" << tensor << std::endl;
    std::cout << "D Tensor:" << d_tensor << std::endl;
    std::cout << "L Tensor:" << l_tensor << std::endl;
    std::cout << "U Tensor:" << u_tensor << std::endl;

    std::cout << "Jacobi_Matrix_Split(3, 3):" << std::endl;
    SIMI::MATRIX::jacobi_iterator_matrix_split<SIMI::Float64>(
        tensor,
        d_tensor,
        l_tensor,
        u_tensor
    );
    std::cout << "D Tensor:" << d_tensor << std::endl;
    std::cout << "L Tensor:" << l_tensor << std::endl;
    std::cout << "U Tensor:" << u_tensor << std::endl;
}

void test_to_strict_diagonal_dominance_matrix()
{
    std::cout << "To Strict Diagonal Dominance Matrix(3, 3) test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor(3, 3);
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
    strict_diagonal_dominance_tensor.zeros();
    std::cout << "Input Tensor:" << tensor << std::endl;

    std::cout << "To Strict Diagonal Dominance Matrix(3, 3):" << std::endl;
    if(!SIMI::MATRIX::to_strict_diagonal_dominance_matrix<SIMI::Float64>(
        tensor,
        strict_diagonal_dominance_tensor).tobool()) {
            return;
    }

    std::cout << "Strict Diagonal Dominance Tensor:" << strict_diagonal_dominance_tensor << std::endl;
}

void test_matrix_inverse()
{
    std::cout << "Matrix Inverse(2x2) test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> input_tensor1(2, 2);
    SIMI::Tensor<SIMI::Float64> input_tensor1_inverse(2, 2);
    input_tensor1.iloc(0, 0) = 1;
    input_tensor1.iloc(0, 1) = 3;
    input_tensor1.iloc(1, 0) = 4;
    input_tensor1.iloc(1, 1) = 13;
    input_tensor1_inverse.zeros();
    std::cout << "Input Tensor:" << input_tensor1 << std::endl;

    std::cout << "Matrix Inverse(2x2):" << std::endl;
    if(!(SIMI::MATRIX::inverse(input_tensor1, input_tensor1_inverse).tobool())) {
            return;
    }
    std::cout << input_tensor1_inverse;
}

void test_jacobi_iterator_solve()
{
    std::cout << "Jacobi Iterator Solve(3, 3) test:" << std::endl;

    SIMI::reset_float_show_precision(10);

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
    SIMI::SOLVES::jacobi_iterator_solve(
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

void test_gauss_seidel_iterator_solve()
{
    std::cout << "Gauss Seidel Iterator Solve(3, 3) test:" << std::endl;

    SIMI::reset_float_show_precision(10);

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
    SIMI::SOLVES::gauss_seidel_solve(
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


void test_sor_iterator_solve()
{
    std::cout << "SOR Iterator Solve(3, 3) test:" << std::endl;

    SIMI::reset_float_show_precision(10);

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

    SIMI::float64 w = 1.;
    SIMI::float64 error_limit = 1e-8;
    SIMI::u32 max_iters = 30;
    std::cout << "SOR Iterator Solve(3, 3):" << std::endl;
    SIMI::SOLVES::sor_solve(
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


void test_hilbert_generate()
{
    std::cout << "Hilbert_generate[5] test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(5);
    std::cout << tensor << std::endl;

    std::cout << "Hilbert_generate[12] test:" << std::endl;

    tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(12);
    std::cout << tensor << std::endl;
}


