#include "solves.h"

namespace SIMI {

namespace SOLVES {

#define DEFINE_TYPE Float64
template<>
Tensor<DEFINE_TYPE> gaussian_elimination_solve(Tensor<DEFINE_TYPE>& tensor)
{
    u32 _end_c_index = tensor.get_shape()[0].touint32();
    u32 _end_r_index = tensor.get_shape()[1].touint32();
    SOLVES_ASSERT_QUIT(!CHECK_FLOAT64_ELEM_ZERO(tensor.at(_end_c_index-2, _end_r_index-2)) && \
                       "The Ab of A Tensor's last elemment should not equal to zero.");

    Tensor<DEFINE_TYPE> _result(_end_c_index, 1); // 列向量
    for(int i = _end_c_index - 1; i >= 0; i--) {
        _result.iloc(i, 0) = tensor.at(i, _end_r_index-1);
        for(int j = _end_c_index - 1; j > i; j--) {
            _result.iloc(i, 0) = _result.at(i, 0) - tensor.at(i, j) * _result.at(j, 0);
        }
        _result.iloc(i, 0) = _result.iloc(i, 0) / tensor.at(i, i);
    }

    return _result;
}


/*
template<>
Tensor<DEFINE_TYPE> lu_solve(Tensor<DEFINE_TYPE>& l_tensor, Tensor<DEFINE_TYPE>& u_tensor, Tensor<DEFINE_TYPE>& b_tensor)
{
    Tensor<DEFINE_TYPE> _x(b_tensor), _y(b_tensor);
    _x.zeros(), _y.zeros();
    u32 _col_num = l_tensor.get_shape()[0].touint32();
    u32 _row_num = l_tensor.get_shape()[1].touint32();

    // fill y --> Ly=b : forward solve
    for(int i = 0; i < _col_num; i++) {
        DEFINE_TYPE _sum = 0;
        for(int j = 0; j <= i; j++) {
            if(j == i) { // i == j: 对应方程未知元素(每一次求解只含有一个未知数)
                _y.iloc(j, 0) = (b_tensor.at(i, 0) - _sum) / l_tensor.at(i, j);
            } else {
                _sum = _sum + _y.iloc(j, 0) * l_tensor.at(i, j);
            }
        }
    }

    // from y to x: Ux=y : backward solve
    for(int i = _col_num-1; i >= 0; i--) {
        DEFINE_TYPE _sum = 0;
        for(int j = _col_num-1; j >= i; j--) {
            if(j == i) {
                _x.iloc(j, 0) = (_y.at(i, 0) - _sum) / u_tensor.at(i, j);
            } else {
                _sum = _sum + _x.iloc(j, 0) * u_tensor.at(i, j);
            }
        }
    }

    return _x;
}
*/

#undef DEFINE_TYPE

}

}