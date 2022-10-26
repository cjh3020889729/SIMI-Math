#include "./matrix.h"


namespace SIMI {

namespace MATRIX {

// 普通矩阵乘法实现: 优化寻址计算消耗
template<class T1, class T2>
__STATIC_API__ __ALGORITHM__ void _multiply_normal(const Tensor<T1>& tensor1,
                                    const Tensor<T2>& tensor2,
                                    Tensor<T1>& out_tensor)
{
    T1* tensor1_start_data = tensor1.data().get();
    T2* tensor2_start_data = tensor2.data().get();
    u32 m2_rows = tensor2.get_shape()[1].touint32();
    u32 m1_rows = tensor1.get_shape()[1].touint32();
    u64 m1_elem_num = tensor1.elem_num().toint64();
    T1* out_tensor_data = out_tensor.data().get();

    for(int i = 0; i < m1_elem_num; i++) {
        for(int j = 0; j < m2_rows; j++) {
            // multi: 1, add: 1, adr: 3
            (*out_tensor_data) += (*tensor1_start_data) * (*tensor2_start_data);
            tensor2_start_data++; // offset: 1
            out_tensor_data++; // offset: 1
        }
        out_tensor_data -= m2_rows; // offset: m2_rows: N
        tensor1_start_data++; // offset: 1

        if(((i+1) % m1_rows == 0) && ((i+1) != m1_elem_num)) {
            tensor2_start_data = tensor2.data().get(); // adr: 1
            out_tensor_data += m2_rows; // offset: m2_rows: N
        }
    }
}
// 分块矩阵乘法实现
template<class T1, class T2>
__STATIC_API__ __ALGORITHM__ void _multiply_split_block(const Tensor<T1>& tensor1,
                                    const Tensor<T2>& tensor2,
                                    Tensor<T1>& out_tensor)
{
    MATRIX_ASSERT_QUIT(false && \
                "The multiply mode(SPLIT_BLOCK) doesn't implement.");
}
// Strassen矩阵乘法实现
template<class T1, class T2>
__STATIC_API__ __ALGORITHM__ void _multiply_strassen(const Tensor<T1>& tensor1,
                                      const Tensor<T2>& tensor2,
                                      Tensor<T1>& out_tensor)
{
    MATRIX_ASSERT_QUIT(false && \
                "The multiply mode(STRASSEN) doesn't implement.");
}
// COPPERSMITH_WINOGRAD矩阵乘法实现
template<class T1, class T2>
__STATIC_API__ __ALGORITHM__ void _multiply_coppersmith_winograd(const Tensor<T1>& tensor1,
                                                  const Tensor<T2>& tensor2,
                                                  Tensor<T1>& out_tensor)
{
    MATRIX_ASSERT_QUIT(false && \
                "The multiply mode(COPPERSMITH_WINOGRAD) doesn't implement.");
}

#define DEFINE_TYPE1 Float64
#define DEFINE_TYPE2 Float64
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> transpose(const Tensor<DEFINE_TYPE1>& tensor)
{
    MATRIX_ASSERT_QUIT((tensor.ndims() == 2) && \
                "The Multiply only support the ndims == 2 for Tensor*Tensor.");

    Tensor<DEFINE_TYPE1> _temp(tensor.get_shape()[1].touint32(), tensor.get_shape()[0].touint32());
    for(int i = 0; tensor.get_shape()[0] > i; i++) {
        for(int j = 0; tensor.get_shape()[0] > j; j++) {
            if(i == j) continue; // 对角不动
            _temp.iloc(i, j) = tensor.at(j, i);
        }
    }
    return _temp;
}
// 矩阵乘法接口
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> multiply(const Tensor<DEFINE_TYPE1>& tensor1,
                                            const Tensor<DEFINE_TYPE2>& tensor2,
                                            Multiply_Mode mode)
{
    MATRIX_ASSERT_QUIT(((tensor1.ndims() == 2) && (tensor2.ndims() == 2)) && \
                "The Multiply only support the ndims == 2 for Tensor*Tensor.");

    Tensor<DEFINE_TYPE1> _temp(tensor1.get_shape()[0].touint32(), tensor2.get_shape()[1].touint32());
    switch(mode)
    {
        case NORMAL:
            _multiply_normal(tensor1, tensor2, _temp);
            break;
        case SPLIT_BLOCK:
            _multiply_split_block(tensor1, tensor2, _temp);
            break;
        case STRASSEN:
            _multiply_strassen(tensor1, tensor2, _temp);
            break;
        case COPPERSMITH_WINOGRAD:
            _multiply_coppersmith_winograd(tensor1, tensor2, _temp);
            break;
        default:
            MATRIX_ASSERT_QUIT(false && \
                "The multiply mode doesn't support, which only supports: NORMAL, SPLIT_BLOCK, STRASSEN, COPPERSMITH_WINOGRAD.");
            break;
    }

    return _temp;
}

template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> get_col(const Tensor<DEFINE_TYPE1>& tensor, u32 col)
{
    Tensor<DEFINE_TYPE1> _temp(tensor.get_shape()[0].touint32());

    for(int i = 0; i < tensor.get_shape()[0].toint32(); i++) {
        _temp.iloc(i) = tensor.at(i, col);
    }
    return _temp;
}
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> get_row(const Tensor<DEFINE_TYPE1>& tensor, u32 row)
{
    Tensor<DEFINE_TYPE1> _temp(tensor.get_shape()[1].touint32());

    for(int i = 0; i < tensor.get_shape()[1].toint32(); i++) {
        _temp.iloc(i) = tensor.at(row, i);
    }
    return _temp;
}

// 交换行
template<>
__ALGORITHM__ void exchange_col(Tensor<DEFINE_TYPE1>& tensor, u32 col1, u32 col2)
{
    Tensor<DEFINE_TYPE1> _temp(tensor);

    for(int i = 0; i < _temp.get_shape()[0].toint32(); i++) {
        _temp.iloc(i, col1) = tensor.at(i, col2);
        _temp.iloc(i, col2) = tensor.at(i, col1);
    }
    tensor = _temp;
}
// 交换列
template<>
__ALGORITHM__ void exchange_row(Tensor<DEFINE_TYPE1>& tensor, u32 row1, u32 row2)
{
    Tensor<DEFINE_TYPE1> _temp(tensor);

    for(int i = 0; i < _temp.get_shape()[1].toint32(); i++) {
        _temp.iloc(row1, i) = tensor.at(row2, i);
        _temp.iloc(row2, i) = tensor.at(row1, i);
    }
    tensor = _temp;
}

// 上三角变换
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> to_upper_triangular_matrix(const Tensor<DEFINE_TYPE1>& tensor)
{
    Tensor<DEFINE_TYPE1> _temp(tensor);
    u32 _rows = _temp.get_shape()[0].touint32();
    u32 _cols = _temp.get_shape()[1].touint32();
    for(int _iter_count = 0; _iter_count < (_cols-1); _iter_count++) {
        u32 _max_at_row = _iter_count + UTILS::argmax_1d(get_col(_temp, (u32)_iter_count), _iter_count); // 列最大值所在行

        if(_max_at_row != _iter_count) exchange_row(_temp, _iter_count, _max_at_row); // 交换最大列所在行
        
        for(int i = _iter_count+1; i < _rows; i++) {
            float64 _ratio = (_temp.at(i, _iter_count) / _temp.at(_iter_count, _iter_count)).tofloat64();
            for(int j = _iter_count; j < _cols; j++) {
                _temp.iloc(i, j) = _temp.at(i, j) - (_temp.at(_iter_count, j) * _ratio);
                if(CHECK_FLOAT64_ELEM_ZERO(_temp.at(i, j))) _temp.iloc(i, j) = 0;
            }
        }
    
    }
    return _temp;
}


// 下三角变换
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> to_lower_triangular_matrix(const Tensor<DEFINE_TYPE1>& tensor)
{
    MATRIX_WARNING_NO_PARAMS("The Functions doesn't implement.");
}


// 最简行列式变换
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> to_simplest_determinant(const Tensor<DEFINE_TYPE1>& tensor)
{
    MATRIX_WARNING_NO_PARAMS("The Functions doesn't implement.");
}


// 高斯消元变换
template<>
__ALGORITHM__ Tensor<DEFINE_TYPE1> gaussian_elimination_transform(const Tensor<DEFINE_TYPE1>& tensor)
{
    return to_upper_triangular_matrix(tensor);
}


// LU分解变换
template<>
__ALGORITHM__ Bool lu_directly_split_transform(const Tensor<DEFINE_TYPE1>& input_tensor,
                                               Tensor<DEFINE_TYPE1>& l_tensor,
                                               Tensor<DEFINE_TYPE1>& u_tensor)
{
    // check input_tensor.shape = n x n
    if(!(input_tensor.get_shape()[0]==input_tensor.get_shape()[1])) {
        MATRIX_WARNING_NO_PARAMS("The input_tensor's shape should n x n.");
        return false;
    }
    // check L.shape=U.shape=input_tensor.shape
    if(!(l_tensor.get_shape()==u_tensor.get_shape()).tobool()) {
        MATRIX_WARNING_NO_PARAMS("The l_tensor's shape should equal to u_tensor's shape.");
        return false;
    }
    if(!(input_tensor.get_shape()==l_tensor.get_shape()).tobool()) {
        MATRIX_WARNING_NO_PARAMS("The input_tensor's shape should equal to l_tensor/u_tensor's shape.");
        return false;
    }
    // check LU exists: 存在则列主元上三角化最后一行末尾元素不为0
    // 在本函数中采用直接法拆分LU，因此l/u矩阵未必真实有效
    // 但只要该方法返回true，则必然可以通过高斯消元法重新得到正确的LU分解
    Tensor<DEFINE_TYPE1> check_tensor = to_upper_triangular_matrix(input_tensor);
    u32 _end_c_index = check_tensor.get_shape()[0].touint32();
    u32 _end_r_index = check_tensor.get_shape()[1].touint32();
    if(CHECK_FLOAT64_ELEM_ZERO(check_tensor.at(_end_c_index-1, _end_r_index-1))) {
        MATRIX_WARNING_NO_PARAMS("The Tensor's last elemment should is zero, which means the.");
        return false;
    }

    // start LU split
    l_tensor.zeros();
    l_tensor.diag_fill(1); // init L matrix
    u_tensor.zeros();
    for(int i = 0; i < u_tensor.get_shape()[1].touint32(); i++) {
        u_tensor.iloc(0, i) = input_tensor.at(0, i);
    } // init U matrix
    u32 _col_num = l_tensor.get_shape()[0].touint32();
    u32 _row_num = l_tensor.get_shape()[0].touint32();
    for(int i = 1; i < _col_num; i++) { // l col-axis
        DEFINE_TYPE1 _sum = 0;
        for(int k = 0; k < _row_num; k++) { // u row-axis
            _sum = 0;
            if(k < i) { // find l elemmet
                for(int jk = 0; jk < k; jk++) {
                    _sum = _sum + l_tensor.at(i, jk) * u_tensor.at(jk, k);
                } // accumulate [0, k), if k == 0, break 
                l_tensor.iloc(i, k) = (input_tensor.at(i, k) - _sum) / u_tensor.at(k, k);
                if(CHECK_FLOAT64_ELEM_ZERO(l_tensor.at(i, k))) l_tensor.iloc(i, k) = 0;
            } else { // find r elemment
                for(int jk = 0; jk < i; jk++) {
                    _sum = _sum + l_tensor.at(i, jk) * u_tensor.at(jk, k);
                }
                u_tensor.iloc(i, k) = (input_tensor.at(i, k) - _sum) / l_tensor.at(k, k);
                if(CHECK_FLOAT64_ELEM_ZERO(u_tensor.at(i, k))) u_tensor.iloc(i, k) = 0;
            }
        }
    }
    return true;
}








template<>
__DATA__ Tensor<DEFINE_TYPE1> hilbert_generate(const u32 level)
{
    if(level == 0 || level > 500) {
        MATRIX_WARNING_1_PARAMS("The function of hilbert_generate needs [1, 500] level, but it is %d.", level);
        if(level == 0) return hilbert_generate<DEFINE_TYPE1>(1);
        return hilbert_generate<DEFINE_TYPE1>(500);
    }

    Tensor<DEFINE_TYPE1> _temp(level, level);
    for(int i = 0; i < level; i++) {
        for(int j = 0; j < level; j++) {
            _temp.iloc(i, j) = 1./(i+j+1);
            if(CHECK_FLOAT64_ELEM_ZERO(_temp.at(i, j))) _temp.iloc(i, j) = 0;
        }
    }
    return _temp;
}

#undef DEFINE_TYPE1
#undef DEFINE_TYPE2




}

}
