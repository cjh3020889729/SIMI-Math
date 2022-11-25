#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

SIMI::Tensor<SIMI::Float64> do_func(const SIMI::Tensor<SIMI::Float64>& input_x)
{
    SIMI::Tensor<SIMI::Float64> _temp_xy(input_x.get_shape()[0].touint32(), 2);
    for(int i = 0; i < input_x.get_shape()[0].touint32(); i++) {
        _temp_xy.iloc(i, 0) = input_x.at(i); // x
        _temp_xy.iloc(i, 1) = 1. / (1. + 12. * input_x.at(i).tofloat64() * input_x.at(i).tofloat64()); // y
    }
    return _temp_xy;
}

double do_error(
    const SIMI::Tensor<SIMI::Float64>& input_a,
    const SIMI::Tensor<SIMI::Float64>& input_b)
{
    return SIMI::MATRIX::l2_norm_for_vector(
        SIMI::MATRIX::sub(input_a, input_b)).tofloat64();
}

void solve()
{
    std::cout << "The Chevyshev Inter Solve:\n";

    SIMI::float64 start_x = -2.;
    SIMI::float64 end_x = 2.;
    SIMI::u32 test_point_num = 100;

    for(int i = 1; i <= 3; i++) {
        SIMI::u32 n = i*10+1;

        std::cout << "\nThe Chevyshev Inter Solve-" << n << " Points:\n";

        SIMI::Tensor<SIMI::Float64> m_x = \
        SIMI::MATRIX::mean_interpolate_point_generate<SIMI::Float64>(start_x, end_x, n);
        SIMI::Tensor<SIMI::Float64> c_x = \
            SIMI::MATRIX::chebyshev_interpolate_point_generate<SIMI::Float64>(start_x, end_x, n);
        SIMI::Tensor<SIMI::Float64> m_xy = do_func(m_x);
        SIMI::Tensor<SIMI::Float64> c_xy = do_func(c_x);

        SIMI::Tensor<SIMI::Float64> m_ax;
        SIMI::Tensor<SIMI::Float64> c_ax;
        if(!SIMI::MATRIX::newton_interpolation_coefficient(m_xy, m_ax)) {
            std::cout << "The Newton Inter Coefficient Function Failed." << std::endl;
        }
        if(!SIMI::MATRIX::newton_interpolation_coefficient(c_xy, c_ax)) {
            std::cout << "The Newton Inter Coefficient Function Failed." << std::endl;
        }

        SIMI::Tensor<SIMI::Float64> input_x = \
        SIMI::MATRIX::mean_interpolate_point_generate<SIMI::Float64>(start_x, end_x, test_point_num);
        SIMI::Tensor<SIMI::Float64> m_output;
        if(!SIMI::SOLVES::newton_interpolation_caculate(m_ax, input_x, m_output)) {
            std::cout << "The Newton Inter Caculate Function Failed." << std::endl;
        }
        SIMI::Tensor<SIMI::Float64> c_output;
        if(!SIMI::SOLVES::newton_interpolation_caculate(c_ax, input_x, c_output)) {
            std::cout << "The Newton Inter Caculate Function Failed." << std::endl;
        }
        SIMI::Tensor<SIMI::Float64> normal_output = SIMI::MATRIX::get_col_vector(do_func(input_x), 1);

        double m_error = do_error(m_output, normal_output);
        double c_error = do_error(c_output, normal_output);

        std::cout << "The " << n << " inter M-Error(Test Points:" << test_point_num << "): " << m_error << "." << std::endl;
        std::cout << "The " << n << " inter C-Error(Test Points:" << test_point_num << "): " << c_error << "." << std::endl;
    }
}


int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("logs.txt");
    solve();

    SIMI::mark_compare_datetime();

    return 0;
}
