#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"


void hilbert_solve_by_gausi()
{
    std::cout << "\n**********************Start Sovel By Gausi func**********************\n";
    std::cout << "\n**********************Start Sovel By Gausi func**********************\n";
    SIMI::u32 level = 10;
    std::cout << "(check with matlab)hilbert generate(" << level << "):" << std::endl;

    SIMI::Tensor<SIMI::Float64> tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b(level, 1);
    b.ones();
    b = SIMI::MATRIX::multiply(tensor, b);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b << std::endl;

    SIMI::Tensor<SIMI::Float64> input_tensor(level, level+1);
    for(int i = 0; i < level; i++) {
        for(int j = 0; j < level+1; j++) {
            if(j==level) {
                input_tensor.iloc(i, j) = b.at(i, 0);
            } else {
                input_tensor.iloc(i, j) = tensor.at(i, j);
            }
        }
    }
    std::cout << "origin h|b matrix:" << std::endl;
    std::cout << input_tensor << std::endl;

    std::cout << "gausi matrix:" << std::endl;
    SIMI::Tensor<SIMI::Float64> gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(input_tensor);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;

    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    level = 12;
    std::cout << "hilbert generate(" << level << "):" << std::endl;

    tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b1(level, 1);
    b1.ones();
    b1 = SIMI::MATRIX::multiply(tensor, b1);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b1 << std::endl;

    SIMI::Tensor<SIMI::Float64> input_tensor1(level, level+1);
    for(int i = 0; i < level; i++) {
        for(int j = 0; j < level+1; j++) {
            if(j==level) {
                input_tensor1.iloc(i, j) = b1.at(i, 0);
            } else {
                input_tensor1.iloc(i, j) = tensor.at(i, j);
            }
        }
    }
    std::cout << "origin h|b matrix:" << std::endl;
    std::cout << input_tensor1 << std::endl;

    std::cout << "gausi matrix:" << std::endl;
    gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(input_tensor1);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;

    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    level = 20;
    std::cout << "hilbert generate(" << level << "):" << std::endl;

    tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b2(level, 1);
    b2.ones();
    b2 = SIMI::MATRIX::multiply(tensor, b2);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b2 << std::endl;

    SIMI::Tensor<SIMI::Float64> input_tensor2(level, level+1);
    for(int i = 0; i < level; i++) {
        for(int j = 0; j < level+1; j++) {
            if(j==level) {
                input_tensor2.iloc(i, j) = b2.at(i, 0);
            } else {
                input_tensor2.iloc(i, j) = tensor.at(i, j);
            }
        }
    }
    std::cout << "origin h|b matrix:" << std::endl;
    std::cout << input_tensor2 << std::endl;

    std::cout << "gausi matrix:" << std::endl;
    gausi_tensor = SIMI::MATRIX::gaussian_elimination_transform(input_tensor2);
    std::cout << gausi_tensor << std::endl;
    std::cout << "gausi solve:" << std::endl;
    std::cout << SIMI::SOLVES::gaussian_elimination_solve(gausi_tensor) << std::endl;
    std::cout << "\n**********************End Sovel By Gausi func**********************\n";
    std::cout << "\n**********************End Sovel By Gausi func**********************\n";
}

void hilbert_solve_by_lu()
{
    std::cout << "\n**********************Start Sovel By LU Split func**********************\n";
    std::cout << "\n**********************Start Sovel By LU Split func**********************\n";
    SIMI::u32 level = 10;
    std::cout << "(check with matlab)hilbert generate(" << level << "):" << std::endl;

    SIMI::Tensor<SIMI::Float64> a_tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << a_tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b_tensor(level, 1);
    b_tensor.ones();
    b_tensor = SIMI::MATRIX::multiply(a_tensor, b_tensor);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b_tensor << std::endl;

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

    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    level = 12;
    std::cout << "hilbert generate(" << level << "):" << std::endl;

    a_tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << a_tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b_tensor1(level, 1);
    b_tensor1.ones();
    b_tensor1 = SIMI::MATRIX::multiply(a_tensor, b_tensor1);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b_tensor1 << std::endl;

    SIMI::Tensor<SIMI::Float64> l_tensor1(a_tensor), u_tensor1(a_tensor);
    if(!(SIMI::MATRIX::lu_directly_split_transform(a_tensor, l_tensor1, u_tensor1).tobool())) {
        std::cout << "Info: The LU split is failed.\n";
    }

    std::cout << "L Matrix:\n";
    std::cout << l_tensor1 << std::endl;
    std::cout << "U Matrix:\n";
    std::cout << u_tensor1 << std::endl;

    std::cout << "LU Solve Result:\n";
    std::cout << SIMI::SOLVES::lu_solve(l_tensor1, u_tensor1, b_tensor1) << std::endl;

    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    level = 20;
    std::cout << "hilbert generate(" << level << "):" << std::endl;

    a_tensor = SIMI::MATRIX::hilbert_generate<SIMI::Float64>(level);
    std::cout << "origin h matrix:" << std::endl;
    std::cout << a_tensor << std::endl;
    SIMI::Tensor<SIMI::Float64> b_tensor2(level, 1);
    b_tensor2.ones();
    b_tensor2 = SIMI::MATRIX::multiply(a_tensor, b_tensor2);
    std::cout << "origin b matrix:" << std::endl;
    std::cout << b_tensor2 << std::endl;

    SIMI::Tensor<SIMI::Float64> l_tensor2(a_tensor), u_tensor2(a_tensor);
    if(!(SIMI::MATRIX::lu_directly_split_transform(a_tensor, l_tensor2, u_tensor2).tobool())) {
        std::cout << "Info: The LU split is failed.\n";
    }

    std::cout << "L Matrix:\n";
    std::cout << l_tensor2 << std::endl;
    std::cout << "U Matrix:\n";
    std::cout << u_tensor2 << std::endl;

    std::cout << "LU Solve Result:\n";
    std::cout << SIMI::SOLVES::lu_solve(l_tensor2, u_tensor2, b_tensor2) << std::endl;

    std::cout << "\n**********************End Sovel By LU Split func**********************\n";
    std::cout << "\n**********************End Sovel By LU Split func**********************\n";
}

int main()
{
    // 验证重定向
    SIMI::restdout2file("gausi_logs.txt");
    SIMI::reset_float_show_precision(16);

    hilbert_solve_by_gausi();

    SIMI::restdout2file("lu_logs.txt");
    hilbert_solve_by_lu();

    SIMI::mark_compare_datetime();
    return 0;
}
