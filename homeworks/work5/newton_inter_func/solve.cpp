#include <iostream>
#include "basetype.h"
#include "slice.h"
#include "tensor.h"
#include "debugs.h"
#include "matrix.h"
#include "solves.h"

#include <ctime>
#include <windows.h>

#define PI 3.141592653589793238462643383279502884


void do_sinx(
    const SIMI::Tensor<SIMI::Float64>& input_x,
    SIMI::Tensor<SIMI::Float64>& sin_x)
{
    for(int i = 0; i < sin_x.get_shape()[0].touint32(); i++) {
        sin_x.iloc(i) = sin(input_x.at(i).tofloat64());
    }
}

void do_2_pi_norm(SIMI::Tensor<SIMI::Float64>& input_x) {
    for(int i = 0; i < input_x.get_shape()[0].touint32(); i++) {
        input_x.iloc(i) = ((input_x.at(i).tofloat64() / (2. * PI)) - (int)(input_x.at(i).tofloat64() / (2. * PI))) * 2. * PI;
    }
}


void newton_inter_func()
{
    std::cout << "The Newton Inter Function:\n";
    SIMI::Tensor<SIMI::Float64> xy(17, 2);
    SIMI::Tensor<SIMI::Float64> ax(17, 2);
    xy.iloc(0, 0) = 0; // 0 - pi / 2
    xy.iloc(0, 1) = 0;
    xy.iloc(1, 0) = PI / 6.;
    xy.iloc(1, 1) = 1./2.;
    xy.iloc(2, 0) = PI / 3.;
    xy.iloc(2, 1) = sqrt(3.) / 2.;
    xy.iloc(3, 0) = PI / 4.;
    xy.iloc(3, 1) = sqrt(2.) / 2.;
    xy.iloc(4, 0) = PI / 2.;
    xy.iloc(4, 1) = 1.;
    // info: 这里直接生成sin的周期值，暂不额外引入针对sin插值拟合时Newton插值法对对称性的考虑
    // pi / 2 - pi
    xy.iloc(5, 0) = 2. * PI / 3.;
    xy.iloc(5, 1) = sqrt(3.) / 2.;
    xy.iloc(6, 0) = 3.* PI / 4.;
    xy.iloc(6, 1) = sqrt(2.) / 2.;
    xy.iloc(7, 0) = 5. * PI / 6.;
    xy.iloc(7, 1) = 1./2.;
    // pi - 3 pi / 2
    xy.iloc(8, 0) = PI;
    xy.iloc(8, 1) = 0;
    xy.iloc(9, 0) = 4. * PI / 3.;
    xy.iloc(9, 1) = -sqrt(3.) / 2.; // 
    xy.iloc(10, 0) = 5. * PI / 4.;
    xy.iloc(10, 1) = -sqrt(2.) / 2.; // 
    xy.iloc(11, 0) = 7. * PI / 6.;
    xy.iloc(11, 1) = -1./2.; // 
    xy.iloc(12, 0) = 3. * PI / 2.;
    xy.iloc(12, 1) = -1.;
    // 3 pi / 2 - 2 pi
    xy.iloc(13, 0) = 5. * PI / 3.;
    xy.iloc(13, 1) = -sqrt(3.) / 2.;
    xy.iloc(14, 0) = 7. * PI / 4.;
    xy.iloc(14, 1) = -sqrt(2.) / 2.;
    xy.iloc(15, 0) = 11.* PI / 6.;
    xy.iloc(15, 1) = -1./2.;
    xy.iloc(16, 0) = 2. * PI;
    xy.iloc(16, 1) = 0;
    SIMI::Tensor<SIMI::Float64> input_x(6, 1);
    SIMI::Tensor<SIMI::Float64> sin_x(6, 1);
    SIMI::Tensor<SIMI::Float64> output(6, 1);
    input_x.iloc(0) = 1;
    input_x.iloc(1) = 2;
    input_x.iloc(2) = 3;
    input_x.iloc(3) = 4;
    input_x.iloc(4) = 14;
    input_x.iloc(5) = 1000;
    do_sinx(input_x, sin_x);
    do_2_pi_norm(input_x);

    if(!SIMI::MATRIX::newton_interpolation_coefficient(xy, ax)) {
        std::cout << "The Newton Inter Coefficient Function Failed." << std::endl;
    }
    std::cout << "The Newton Inter a:" << std::endl;
    std::cout << SIMI::MATRIX::get_col_vector(ax, 0);
    std::cout << "The Newton Inter x:" << std::endl;
    std::cout << SIMI::MATRIX::get_col_vector(ax, 1);

    std::cout << std::endl;
    std::cout << std::endl;

    if(!SIMI::SOLVES::newton_interpolation_caculate(ax, input_x, output)) {
        std::cout << "The Newton Inter Caculate Function Failed." << std::endl;
    }
    std::cout << "The Newton Inter Input X:" << std::endl;
    std::cout << input_x;
    std::cout << "The Newton Inter Output:" << std::endl;
    std::cout << output;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Normal Sin(x):" << std::endl;
    std::cout << sin_x;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Error Sin(x):" << std::endl;
    std::cout << SIMI::MATRIX::sub(output, sin_x);
}


int main()
{
    // 验证重定向
    SIMI::reset_float_show_precision(15);

    SIMI::restdout2file("logs.txt");
    newton_inter_func();

    SIMI::mark_compare_datetime();

    return 0;
}
