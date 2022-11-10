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
template<class T>
__ALGORITHM__ Tensor<T> get_col_vector(const Tensor<T>& tensor, u32 col)
{
    Tensor<T> _temp(tensor.get_shape()[0].touint32(), 1);

    for(int i = 0; i < tensor.get_shape()[0].toint32(); i++) {
        _temp.iloc(i, 0) = tensor.at(i, col);
    }
    return _temp;
}
// 矩阵取行
template<class T>
__ALGORITHM__ Tensor<T> get_row(const Tensor<T>& tensor, u32 row);
template<class T>
__ALGORITHM__ Tensor<T> get_row_vector(const Tensor<T>& tensor, u32 row)
{
    Tensor<T> _temp(tensor.get_shape()[1].touint32(), 1);

    for(int i = 0; i < tensor.get_shape()[1].toint32(); i++) {
        _temp.iloc(i, 0) = tensor.at(row, i);
    }
    return _temp;
}

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

// L2范数: TODO
template<class T>
T l2_norm_for_vector(const Tensor<T>& input_tensor, bool use_sqrt=true)
{
    T _sum = 0.;
    u32 _rows = input_tensor.get_shape()[0].touint32();
    u32 _cols = input_tensor.get_shape()[1].touint32();
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            _sum = _sum + input_tensor.at(i, j) * input_tensor.at(i, j);
        }
    }
    if(use_sqrt) _sum = sqrt(_sum.tofloat64());
    return _sum;
}

template<class T>
Tensor<T> vector_normalize(const Tensor<T>& input_tensor)
{
    MATRIX_ASSERT_QUIT(input_tensor.check_elem_number().tobool());

    Tensor<T> _temp(input_tensor);
    _temp = _temp / infinite_norm_for_vector(_temp);
    return _temp;
}


// (直接法)幂法迭代求解特征值与向量: 支持情况1
template<class T>
u32 power_iterator_find_eigenvalue_direct(
    const Tensor<T>& a_tensor,
    Tensor<T>& x,
    Tensor<T>& out_tensor,
    u32 iter_max=10)
{
    MATRIX_ASSERT_QUIT(a_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((a_tensor.get_shape()[0] == a_tensor.get_shape()[1]));

    bool is_inverse_eigenvalue=false; // 存在相反数的特征值
    T eigenvalue = 0.;
    Tensor<T> init_x(x); // x vector
    Tensor<T> y(a_tensor.get_shape()[1].touint32(), 1); // y vector
    Tensor<T> z(a_tensor.get_shape()[1].touint32(), 1); // z vector

    for(int i = 0; i < iter_max; i++) {
        init_x = vector_normalize(init_x);
        y = multiply(a_tensor, init_x);
        eigenvalue = infinite_norm_for_vector(y) / infinite_norm_for_vector(init_x);
        T e1 = infinite_norm_for_vector(y / eigenvalue - init_x);
        y = vector_normalize(y);
        if( i == iter_max-1 ) {
            Tensor<T> result(1+a_tensor.get_shape()[1].touint32(), 1); // 特征值+特征向量元素
            result.iloc(0, 0) = eigenvalue;
            for(int i = 1; i < (1+a_tensor.get_shape()[1].touint32()); i++) {
                result.iloc(i, 0) = y.at(i-1, 0);
            }
            out_tensor = result;
            return 1;
        } // case 1

        init_x = y;
        std::cout << "iter:" << i+1 << ", engen value:"
                      << eigenvalue << std::endl;
    }

    return 0;
}

// (Aitken加速法)幂法迭代求解特征值与向量: 支持情况1
template<class T>
u32 power_iterator_find_eigenvalue_aitken(
    const Tensor<T>& a_tensor,
    Tensor<T>& x,
    Tensor<T>& out_tensor,
    u32 iter_max=10)
{
    MATRIX_ASSERT_QUIT(a_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((a_tensor.get_shape()[0] == a_tensor.get_shape()[1]));

    bool is_inverse_eigenvalue=false; // 存在相反数的特征值
    T eigenvalue = 0.;
    Tensor<T> init_x(x); // x0 vector
    Tensor<T> x1(a_tensor.get_shape()[1].touint32(), 1); // x1 vector
    Tensor<T> x2(a_tensor.get_shape()[1].touint32(), 1); // x2 vector
    Tensor<T> y(a_tensor.get_shape()[1].touint32(), 1); // y vector
    // aitken加速预热
    for(int i = 0; i < 2; i++) {
        if(i == 0) {
            y = vector_normalize(init_x);
            x1 = multiply(a_tensor, y);
            eigenvalue = infinite_norm_for_vector(y) / infinite_norm_for_vector(x1);
        } else {
            y = vector_normalize(x1);
            x2 = multiply(a_tensor, y);
            eigenvalue = infinite_norm_for_vector(y) / infinite_norm_for_vector(x2);
        }
        std::cout << "iter:" << i+1 << ", engen value:"
                      << eigenvalue << std::endl;  // 预热有一次完整运算
    }
    for(int i = 0; i < iter_max-2; i++) {
        T _temp_eigenvalue = eigenvalue;

        y = vector_normalize(x2);
        eigenvalue = infinite_norm_for_vector(x2) - \
                     ((infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1)) * \
                     (infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1))) / \
                     (infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1)*2. + \
                     infinite_norm_for_vector(init_x));
        init_x = x1;
        x1 = x2;
        x2 = multiply(a_tensor, y);

        T e1 = eigenvalue - _temp_eigenvalue;
        if(i == (iter_max-2)-1 ) {
            Tensor<T> result(1+a_tensor.get_shape()[1].touint32(), 1); // 特征值+特征向量元素
            result.iloc(0, 0) = eigenvalue;
            for(int i = 1; i < (1+a_tensor.get_shape()[1].touint32()); i++) {
                result.iloc(i, 0) = y.at(i-1, 0);
            }
            out_tensor = result;
            return 1;
        } // case 1

        std::cout << "iter:" << i+3 << ", engen value:"
                      << eigenvalue << std::endl;  // 预热有一次完整运算
    }

    return 0;
}

template<class T>
static Tensor<T> _lu_solve(Tensor<T>& l_tensor, Tensor<T>& u_tensor, Tensor<T>& b_tensor)
{
    Tensor<T> _x(b_tensor), _y(b_tensor);
    _x.zeros(), _y.zeros();
    u32 _col_num = l_tensor.get_shape()[0].touint32();
    u32 _row_num = l_tensor.get_shape()[1].touint32();

    // fill y --> Ly=b : forward solve
    for(int i = 0; i < _col_num; i++) {
        T _sum = 0;
        for(int j = 0; j <= i; j++) {
            if(j == i) { // i == j: 对应方程未知元素(每一次求解只含有一个未知数)
                _y.iloc(j, 0) = (b_tensor.at(i, 0) - _sum) / l_tensor.at(i, j);
            } else {
                _sum = _sum + _y.iloc(j, 0) * l_tensor.at(i, j);
            }
        }
    }

    //from y to x: Ux=y : backward solve
    for(int i = _col_num-1; i >= 0; i--) {
        T _sum = 0;
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

// (直接法)反幂法迭代求解特征值与向量: 支持情况1
template<class T>
u32 inverse_power_iterator_find_eigenvalue_direct(
    const Tensor<T>& a_tensor,
    Tensor<T>& init_x,
    Tensor<T>& out_tensor,
    u32 iter_max=10)
{
    MATRIX_ASSERT_QUIT(a_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((a_tensor.get_shape()[0] == a_tensor.get_shape()[1]));

    bool is_inverse_eigenvalue=false; // 存在相反数的特征值
    // T eigenvalue = 0.;
    Tensor<T> x(a_tensor.get_shape()[1].touint32(), 1); // x vector
    Tensor<T> y(init_x); // y vector
    Tensor<T> _temp_y(y);
    Tensor<T> z(a_tensor.get_shape()[1].touint32(), 1); // z vector
    Tensor<T> l(a_tensor), u(a_tensor);
    if(!lu_directly_split_transform(a_tensor, l, u).tobool()) {
        std::cout << "LU Split Error.\n";
        return 0;
    }
    

    for(int i = 0; i < iter_max; i++) {
        _temp_y = y;
        x = _lu_solve(l, u, y);
        y = vector_normalize(x);
        
        if(i == iter_max-1) {
            Tensor<T> result(1+a_tensor.get_shape()[1].touint32(), 1); // 特征值+特征向量元素
            result.iloc(0, 0) = 1. / infinite_norm_for_vector(x).tofloat64();
            for(int i = 1; i < (1+a_tensor.get_shape()[1].touint32()); i++) {
                result.iloc(i, 0) = y.at(i-1, 0);
            }
            out_tensor = result;
            return 1;
        }

        std::cout << "iter:" << i+1 << ", engen value:"
                      << 1. / infinite_norm_for_vector(x).tofloat64() << std::endl;  // 预热有一次完整运算
    }

    return 0;
}

// (aitken加速)反幂法迭代求解特征值与向量: 支持情况1
template<class T>
u32 inverse_power_iterator_find_eigenvalue_aitken(
    const Tensor<T>& a_tensor,
    Tensor<T>& init_x,
    Tensor<T>& out_tensor,
    u32 iter_max=10)
{
    MATRIX_ASSERT_QUIT(a_tensor.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a_tensor.ndims() == 2));
    MATRIX_ASSERT_QUIT((a_tensor.get_shape()[0] == a_tensor.get_shape()[1]));

    bool is_inverse_eigenvalue=false; // 存在相反数的特征值
    T eigenvalue = 0.;
    Tensor<T> x(a_tensor.get_shape()[1].touint32(), 1); // x vector
    Tensor<T> x1(x);
    Tensor<T> x2(x);
    Tensor<T> y(init_x); // y vector
    Tensor<T> _temp_y(y);
    Tensor<T> z(a_tensor.get_shape()[1].touint32(), 1); // z vector
    Tensor<T> l(a_tensor), u(a_tensor);
    if(!lu_directly_split_transform(a_tensor, l, u).tobool()) {
        std::cout << "LU Split Error.\n";
        return 0;
    }
    

    for(int i = 0; i < iter_max; i++) {
        _temp_y = y;

        x = x1;
        x1 = x2;
        x2 = _lu_solve(l, u, y);
        y = vector_normalize(x2);
        
        if(i >= 2) { // aitken 加速
            T _temp_eigenvalue = 1. / eigenvalue.tofloat64();
            eigenvalue = infinite_norm_for_vector(x2) - \
                        ((infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1)) * \
                        (infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1))) / \
                        (infinite_norm_for_vector(x2) - infinite_norm_for_vector(x1)*2. + \
                        infinite_norm_for_vector(init_x));
            eigenvalue = 1. / eigenvalue.tofloat64();
            
            if(i == iter_max-1) {
                Tensor<T> result(1+a_tensor.get_shape()[1].touint32(), 1); // 特征值+特征向量元素
                result.iloc(0, 0) = eigenvalue;
                for(int i = 1; i < (1+a_tensor.get_shape()[1].touint32()); i++) {
                    result.iloc(i, 0) = y.at(i-1, 0);
                }
                out_tensor = result;
                return 1;
            }

            std::cout << "iter:" << i+1 << ", engen value:"
                      << eigenvalue << std::endl;
        } else {
            if(i == iter_max-1) {
                Tensor<T> result(1+a_tensor.get_shape()[1].touint32(), 1); // 特征值+特征向量元素
                result.iloc(0, 0) = 1. / infinite_norm_for_vector(x2).tofloat64();
                for(int i = 1; i < (1+a_tensor.get_shape()[1].touint32()); i++) {
                    result.iloc(i, 0) = y.at(i-1, 0);
                }
                out_tensor = result;
                return 1;
            }

            std::cout << "iter:" << i+1 << ", engen value:"
                      << 1. / infinite_norm_for_vector(x2).tofloat64() << std::endl;
        }
    }

    return 0;
}


// 生成单位阵
template<class T>
Tensor<T> create_E_matrix(u32 size)
{
    Tensor<T> _temp(size, size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if( i == j) _temp.iloc(i, j) = 1.;
        }
    }
    return _temp;
}


// 符号函数
template<class T>
int32 sign(const T& input)
{
    if(fabs(input.tofloat64()) < 1e-15) return 0;
    else if(input.tofloat64() > 1e-15) return 1;
    return -1;
}

// Householder变换
template<class T>
Tensor<T> householder_transform(
          const Tensor<T>& input_tensor,
          Tensor<T>& r_tensor)
{
    Tensor<T> _temp(input_tensor);
    Tensor<T> q = create_E_matrix<T>(input_tensor.get_shape()[0].touint32());
    Tensor<T> w, v, h, _h_right;
    u32 _rows = input_tensor.get_shape()[0].touint32();
    u32 _cols = input_tensor.get_shape()[1].touint32();

    for(int i = 0; i < _cols; i++) {
        Tensor<T> e1(_rows-i, 1);
        e1.iloc(0, 0) = 1.;
        T _norm = 0.;
        for(int j = i; j < _rows; j++) {
            // l2 norm
            _norm = _norm + _temp.at(j, i)*_temp.at(j, i);
        }
        _norm = sqrt(_norm.tofloat64());
        if(fabs(_norm.tofloat64()) < 1e-15) continue;

        _norm = _norm * sign(_temp.at(i, i)) * -1.; // r
        w = e1 * _norm;
        v = w;
        for(int j = i; j < _rows; j++) {
            // v = w - A1
            v.iloc(j-i, 0) = v.at(j-i, 0) - _temp.at(j, i);
        }

        _h_right = multiply(v, transpose(v)) / l2_norm_for_vector(v, false) * -2.0;
        h = create_E_matrix<T>(input_tensor.get_shape()[0].touint32());
        for(int k = i; k < _rows; k++) {
            for(int z = i; z < _rows; z++) {
                h.iloc(k, z) = h.at(k, z) + _h_right.at(k-i, z-i); 
            }
        }

        _temp = multiply(h, _temp);
        q = multiply(q, h);
    }

    r_tensor = _temp;
    return q;
}




// generate data about matrix
template<class T>
__DATA__ Tensor<T> hilbert_generate(const u32 level);


} // namespace MATRIX

} // namespace SIMI


#endif
