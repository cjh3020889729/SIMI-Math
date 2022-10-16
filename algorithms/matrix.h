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




// generate data about matrix
template<class T>
__DATA__ Tensor<T> hilbert_generate(const u32 level);


} // namespace MATRIX

} // namespace SIMI


#endif
