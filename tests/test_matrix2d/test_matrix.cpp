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
    // hilbert生成
    test_hilbert_generate();

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

void test_hilbert_generate()
{
    std::cout << "Hilbert_generate[5] test:" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(5);
    std::cout << tensor << std::endl;

    std::cout << "Hilbert_generate[12] test:" << std::endl;

    tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(12);
    std::cout << tensor << std::endl;
}