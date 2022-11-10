#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

void inverse_power_iterator_direct_solve()
{
    std::cout << "1.The Direct Inverse Power Iterator:\n";
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
    SIMI::Tensor<SIMI::Float64> output;
    SIMI::Tensor<SIMI::Float64> engine_values;
    SIMI::Tensor<SIMI::Float64> engine_vectors;

    SIMI::u32 enginevalue_count = 0;
    SIMI::u32 iter_max = 12;
    enginevalue_count = SIMI::MATRIX::inverse_power_iterator_find_eigenvalue_direct(
                                      a, init_x, output, iter_max);
    if(!SIMI::SOLVES::inverse_power_iterator_result_solve(
        output, enginevalue_count, engine_values, engine_vectors)) {
        std::cout << "The enginevalue count is error(>=1 && <=2).\n";
    }
    std::cout << "The solve engine value count is " << enginevalue_count << std::endl;
    std::cout << "The solve engine values:\n" << engine_values << std::endl;
    std::cout << "The solve engine vectors:\n" << engine_vectors << std::endl;

}

void inverse_power_iterator_aitken_solve()
{
    std::cout << "2.The Aitken Inverse Power Iterator:\n";
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
    SIMI::Tensor<SIMI::Float64> output;
    SIMI::Tensor<SIMI::Float64> engine_values;
    SIMI::Tensor<SIMI::Float64> engine_vectors;

    SIMI::u32 enginevalue_count = 0;
    SIMI::u32 iter_max = 12;
    enginevalue_count = SIMI::MATRIX::inverse_power_iterator_find_eigenvalue_aitken(
                                      a, init_x, output, iter_max);
    if(!SIMI::SOLVES::inverse_power_iterator_result_solve(
        output, enginevalue_count, engine_values, engine_vectors)) {
        std::cout << "The enginevalue count is error(>=1 && <=2).\n";
    }
    std::cout << "The solve engine value count is " << enginevalue_count << std::endl;
    std::cout << "The solve engine values:\n" << engine_values << std::endl;
    std::cout << "The solve engine vectors:\n" << engine_vectors << std::endl;
}

int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("logs.txt");
    inverse_power_iterator_direct_solve();

    inverse_power_iterator_aitken_solve();

    SIMI::mark_compare_datetime();

    return 0;
}
