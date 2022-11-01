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


// 矩阵对应元素相减
template<class T>
__ALGORITHM__ Tensor<T> sub(const Tensor<T>& input_tensor1, const Tensor<T>& input_tensor2)
{
    MATRIX_ASSERT_QUIT(input_tensor1.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT(input_tensor2.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor1.ndims() == input_tensor2.ndims()));
    MATRIX_ASSERT_QUIT((input_tensor1.get_shape() == input_tensor2.get_shape()).tobool());

    Tensor<T> _temp(input_tensor1);
    u64 _elem_num = input_tensor1.elem_num().touint64();
    for(int i = 0; i < _elem_num; i++) {
        _temp.data().get()[i] = input_tensor1.data().get()[i] - input_tensor2.data().get()[i];
    }
    return _temp;
}

// 矩阵对应元素相加
template<class T>
__ALGORITHM__ Tensor<T> add(const Tensor<T>& input_tensor1, const Tensor<T>& input_tensor2)
{
    MATRIX_ASSERT_QUIT(input_tensor1.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT(input_tensor2.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor1.ndims() == input_tensor2.ndims()));
    MATRIX_ASSERT_QUIT((input_tensor1.get_shape() == input_tensor2.get_shape()).tobool());

    Tensor<T> _temp(input_tensor1);
    u64 _elem_num = input_tensor1.elem_num().touint64();
    for(int i = 0; i < _elem_num; i++) {
        _temp.data().get()[i] = input_tensor1.data().get()[i] + input_tensor2.data().get()[i];
    }
    return _temp;
}

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

// 矩阵的迹
template<class T>
__ALGORITHM__ Float64 trace(const Tensor<T>& input_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));

    Float64 _trace_sum = 0.;
    u32 _rows = input_tensor.get_shape()[0].touint8();
    for(int i = 0; i < _rows; i++) {
        _trace_sum = _trace_sum + input_tensor.at(i, i);
    }
    return _trace_sum;
}

// 矩阵的非对角元素和
template<class T>
__ALGORITHM__ Float64 ndiag_sum(const Tensor<T>& input_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));

    Float64 _sum = 0.;
    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint32();
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if(i != j) _sum = _sum + input_tensor.at(i, i);
        }
    }
    return _sum;
}

// 矩阵求逆
template<class T>
__ALGORITHM__ Bool inverse(const Tensor<T>& input_tensor,
                                  Tensor<T>& output_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u32 _rows = input_tensor.get_shape()[0].touint32();
    u32 _cols = input_tensor.get_shape()[1].touint32();
    Tensor<T> _temp(_rows, _cols*2); // A|E --> E|A^-1
    _temp.zeros();
    output_tensor.zeros();
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols*2; j++) {
            if(j < _rows) _temp.iloc(i, j) = input_tensor.at(i, j);
            else {
                if((j - _rows) == i) _temp.iloc(i, j) = 1;
            }
        }
    } // init matrix

    for(int i = 0; i < _rows; i++) { // 基本行变换--换行
        u32 _max_row_index = i + UTILS::argmax_1d(UTILS::matrix_abs(get_col(input_tensor, i)), (u32)i);
        if(_max_row_index != i) exchange_row(_temp, i, _max_row_index);
        for(int j = 0; j < _rows; j++) { // 化对角阵 -- 基本行变换--加减
            if(i == j) continue;
            else { // 消元+行对角所在列非对角元归零
                Float32 _ratio = _temp.at(j, i) / _temp.at(i, i);
                for(int k = i; k < _cols*2; k++) {
                    _temp.iloc(j, k) = _temp.at(j, k) - _temp.at(i, k) * _ratio;
                }
            }
        }
    }

    for(int j = 0; j < _rows; j++) { // 对角线对应元归一化为1 -- 基本行变换--乘以常数
        T _elem_temp = _temp.at(j, j);
        for(int k = j; k < _cols*2; k++) {
            _temp.iloc(j, k) = _temp.at(j, k) / _elem_temp;
        }
    }

    if(fabs((trace(_temp) - _rows).tofloat64()) > 1e-15) {
        MATRIX_WARNING_NO_PARAMS("The matrix can't have inverse.");
        return false;
    } // check diag is E-diag

    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            output_tensor.iloc(i, j) = _temp.at(i, j+_rows);
        }
    }

    return true;
}


// 线性方程组求解: 严格行对角占优矩阵
template<class T>
__ALGORITHM__ Bool to_strict_diagonal_dominance_matrix(const Tensor<T>& input_tensor,
                                                       Tensor<T>& output_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
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

// 线性方程组求解: 严格行对角占优矩阵 -- 包含同时处理b的形式
template<class T>
__ALGORITHM__ Bool to_strict_diagonal_dominance_matrix(const Tensor<T>& input_tensor,
                                                       Tensor<T>& b_tensor,
                                                       Tensor<T>& output_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
    Tensor<T> _records_do_rows(_rows);
    Tensor<T> _temp_b(b_tensor);
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
        b_tensor.iloc(_max_index, 0) = _temp_b.at(i, 0);
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

    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
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


// check is symmetric matrix
template<class T>
bool is_symmetric_matrix(const Tensor<T>& input_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
    Tensor<T> _temp(input_tensor);
    _temp = transpose(_temp);
    for(int i = 0; i < _rows; i++) {
        for(int j =0; j < _cols; j++) {
            if(input_tensor.at(i, j) != _temp.at(i, j)) {
                return false;
            }
        }
    }
    return true;
}

// check is positive definite matrix
template<class T>
bool is_positive_definite_matrix(const Tensor<T>& input_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
    Tensor<T> _x(1, _rows);
    _x.zeros(); _x.iloc(0, 0) = 1; // [1, 0, 0, ..., 0]
    Tensor<T> _xta = multiply(_x, input_tensor);
    _x = transpose(_x); // _rows, 1
    Tensor<T> _xtax = multiply(_xta, _x);
    if(CHECK_ZERO(_xtax.at(0, 0).tofloat64())) return false;
    return true;
}


// cholesky split
template<class T>
bool cholesky_split(const Tensor<T>& input_tensor, Tensor<T>& l_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((input_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((input_tensor.get_shape()[0] == input_tensor.get_shape()[1]));

    if(!is_symmetric_matrix(input_tensor)) {
        std::cout << "cholesky_split: failed to check symmetric_matrix.\n";
        return false;
    }
    if(!is_positive_definite_matrix(input_tensor)) {
        std::cout << "cholesky_split: failed to check symmetric_matrix.\n";
        return false;
    }
    u32 _rows = input_tensor.get_shape()[0].touint8();
    u32 _cols = input_tensor.get_shape()[1].touint8();
    l_tensor.zeros();
    for(int i = 0; i < _cols; i++) {
        for(int j = i; j < _rows; j++) {
            T _temp = input_tensor.at(j, i);
            for(int k = 0; k < i; k++) {
                if( i == j ) {
                    _temp = _temp - l_tensor.at(i, k) * l_tensor.at(i, k);
                }
                else {
                    _temp = _temp - input_tensor.at(j, k) * l_tensor.at(i, k);
                }
            }
            if( i == j ) {
                l_tensor.iloc(j, i) = sqrt(_temp.tofloat64());
            }
            else {
                l_tensor.iloc(j, i) = _temp / l_tensor.at(i, i);
            }
        }
    }
    return true;
}


// 无穷范数
template<class T>
T infinite_norm_for_vector(const Tensor<T>& input_tensor)
{
    T _max_value = 1e-15;
    u32 _rows = input_tensor.get_shape()[0].touint32();
    u32 _cols = input_tensor.get_shape()[1].touint32();
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if(fabs(input_tensor.at(i, j).tofloat64()) > _max_value.tofloat64()) {
                _max_value = fabs(input_tensor.at(i, j).tofloat64());
            }
        }
    }
    return _max_value;
}

// L2范数
template<class T>
T l2_norm_for_vector(const Tensor<T>& input_tensor)
{
    T _max_value = 1e-15;
    u32 _rows = input_tensor.get_shape()[0].touint32();
    u32 _cols = input_tensor.get_shape()[1].touint32();
    // for(int i = 0; i < _rows; i++) {
    //     for(int j = 0; j < _cols; j++) {
    //         if(fabs(input_tensor.at(i, j).tofloat64()) > _max_value) {
    //             _max_value = fabs(input_tensor.at(i, j).tofloat64());
    //         }
    //     }
    // }
    return _max_value;
}



// generate data about matrix
template<class T>
__DATA__ Tensor<T> hilbert_generate(const u32 level);


} // namespace MATRIX

} // namespace SIMI


#endif
