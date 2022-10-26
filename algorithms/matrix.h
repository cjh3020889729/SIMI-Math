#ifndef __SIMI_MATRIX_ALGORITHM_
#define __SIMI_MATRIX_ALGORITHM_

#include "../bases/types.h"
#include "../bases/basetype.h"
#include "../bases/shape.h"
#include "../bases/slice.h"
#include "../bases/stride.h"
#include "../bases/tensor.h"
#include "../bases/debugs.h"
#include "../algorithms/utils.h"

namespace SIMI {

namespace MATRIX {

__DATA__ typedef enum {
    NORMAL=1,
    SPLIT_BLOCK,
    STRASSEN,
    COPPERSMITH_WINOGRAD
} Multiply_Mode;

// 填充指定行
template<class T, class T1>
__ALGORITHM__ void fill_row(Tensor<T>& input_tensor, Tensor<T1>& row_tensor, u32 _row_n)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() >= 1));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] > _row_n));

    u32 _cols = input_tensor.get_shape()[1].touint32();
    for(int i = 0; i < _cols; i++) {
        input_tensor.iloc(_row_n, i) = row_tensor.at(i);
    }
}

// algorithms about matrix
// 矩阵转置
template<class T>
__ALGORITHM__ Tensor<T> transpose(const Tensor<T>& tensor);

// 矩阵取列
template<class T>
__ALGORITHM__ Tensor<T> get_col(const Tensor<T>& tensor, u32 col);
// 矩阵取行
template<class T>
__ALGORITHM__ Tensor<T> get_row(const Tensor<T>& tensor, u32 row);

// 矩阵换行
template<class T>
__ALGORITHM__ void exchange_col(Tensor<T>& tensor, u32 col1, u32 col2);
// 矩阵换列
template<class T>
__ALGORITHM__ void exchange_row(Tensor<T>& tensor, u32 row1, u32 row2);

// 矩阵乘法
template<class T1, class T2>
__ALGORITHM__ Tensor<T1> multiply(const Tensor<T1>& tensor1, const Tensor<T2>& tensor2, Multiply_Mode mode=NORMAL);

// 上三角变换
template<class T>
__ALGORITHM__ Tensor<T> to_upper_triangular_matrix(const Tensor<T>& tensor);

// 下三角变换: TODO
template<class T>
__ALGORITHM__ Tensor<T> to_lower_triangular_matrix(const Tensor<T>& tensor);

// 最简行列式变换
template<class T>
__ALGORITHM__ Tensor<T> to_simplest_determinant(const Tensor<T>& tensor);

// 高斯消元变换
template<class T>
__ALGORITHM__ Tensor<T> gaussian_elimination_transform(const Tensor<T>& tensor);

// LU分解变换
template<class T>
__ALGORITHM__ Bool lu_directly_split_transform(const Tensor<T>& input_tensor,
                                           Tensor<T>& l_tensor,
                                           Tensor<T>& u_tensor);

// 线性方程组求解: 严格行对角占优矩阵
template<class T>
__ALGORITHM__ Bool to_strict_diagonal_dominance_matrix(const Tensor<T>& input_tensor,
                                                       Tensor<T>& output_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u8 _rows = input_tensor.get_shape()[0].touint8();
    u8 _cols = input_tensor.get_shape()[1].touint8();
    Tensor<T> _records_do_rows(_rows);
    _records_do_rows.zeros();
    output_tensor.zeros(); // init matrix
    for(int i = 0; i < _rows; i++) {
        auto _origin_row_tensor = get_row(input_tensor, i);
        auto _row_tensor = UTILS::matrix_abs(_origin_row_tensor);
        u32 _max_index = UTILS::argmax_1d(_row_tensor);
        T _other_sum = UTILS::matrix_sum(_row_tensor) - _row_tensor.at(_max_index);
        if(_row_tensor.at(_max_index) <= _other_sum) {
            MATRIX_WARNING_NO_PARAMS("The input_tensor can't transform to strict diagonal dominance matrix.");
            return false;
        }
        fill_row(output_tensor, _origin_row_tensor, _max_index);
        _records_do_rows.iloc(_max_index) = 1;
    }
    if(UTILS::matrix_sum(_records_do_rows) < _rows) {
        MATRIX_WARNING_NO_PARAMS("The input_tensor can't transform to strict diagonal dominance matrix.");
        return false;
    }
    return true;
} 

// 线性方程组求解: Jacobi迭代矩阵分解
template<class T>
__ALGORITHM__ void jacobi_iterator_matrix_split(const Tensor<T>& input_tensor,
                                                Tensor<T>& d_tensor,
                                                Tensor<T>& l_tensor,
                                                Tensor<T>& u_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));

    u8 _rows = input_tensor.get_shape()[0].touint8();
    u8 _cols = input_tensor.get_shape()[1].touint8();
    d_tensor.zeros(); // init matrix
    l_tensor.zeros();
    u_tensor.zeros();
    for(int i = 0; i < _rows; i++) {
        for(int j =0; j < _cols; j++) {
            if(i == j) d_tensor.iloc(i, j) = input_tensor.at(i, j);
            else if(i > j) l_tensor.iloc(i, j) = input_tensor.at(i, j);
            else u_tensor.iloc(i, j) = input_tensor.at(i, j);
        }
    }
}



// generate data about matrix
template<class T>
__DATA__ Tensor<T> hilbert_generate(const u32 level);


} // namespace MATRIX

} // namespace SIMI


#endif
