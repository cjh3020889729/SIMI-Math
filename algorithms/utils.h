#ifndef __SIMI_UTILS_ALGORITHM_
#define __SIMI_UTILS_ALGORITHM_

#include "../bases/types.h"
#include "../bases/basetype.h"
#include "../bases/shape.h"
#include "../bases/slice.h"
#include "../bases/stride.h"
#include "../bases/tensor.h"
#include "../bases/debugs.h"

namespace SIMI {

namespace UTILS {

#define CHECK_ZERO(tensor_elemment) (fabs(tensor_elemment) < LIMIT_FLOAT64_ZERO)
#define CHECK_FLOAT32_ELEM_ZERO(tensor_elemment) (fabs(tensor_elemment.tofloat32()) < LIMIT_FLOAT32_ZERO)
#define CHECK_FLOAT64_ELEM_ZERO(tensor_elemment) (fabs(tensor_elemment.tofloat64()) < LIMIT_FLOAT64_ZERO)

typedef enum {
    NORMAL=1,
    QUICK_SORT
} SORT_MODE;

// 类型萃取: eg: TensorType_Traits<one_tensor>::type new_tensor;
template<class T>
struct TensorType_Traits {
    using type = T;
};

// 矩阵/向量求和
template<class T>
__ALGORITHM__ T matrix_sum(const Tensor<T>& tensor)
{
    MATRIX_ASSERT_QUIT(tensor.check_elem_number().tobool());

    T _sum;
    u64 _elem_num = tensor.elem_num().touint64();
    for(int i = 0; i < _elem_num; i++) {
        _sum += tensor.data().get()[i];
    }
    return _sum;
}

// 矩阵/向量元素取绝对值
template<class T>
__ALGORITHM__ Tensor<T> matrix_abs(const Tensor<T>& tensor)
{
    MATRIX_ASSERT_QUIT(tensor.check_elem_number().tobool());

    Tensor<T> _tensor(tensor);
    u64 _elem_num = _tensor.elem_num().touint64();
    for(int i = 0; i < _elem_num; i++) {
        _tensor.data().get()[i] = fabs(_tensor.data().get()[i].tofloat64());
    }
    return _tensor;
}

template<class T>
u32 argmax_1d(Tensor<T> tensor);
template<class T>
u32 argmax_1d(Tensor<T> tensor, u32 start_index);
template<class T>
u32 argmax_1d(Tensor<T> tensor, Tensor<T>& max_tensor);
template<class T>
u32 argmax_1d(Tensor<T> tensor, T& max_);
template<class T>
u32 argmax_1d(Tensor<T> tensor, T& max_, u32 start_index);

template<class T>
u32 argmin_1d(Tensor<T> tensor);
template<class T>
u32 argmin_1d(Tensor<T> tensor, u32 start_index);
template<class T>
u32 argmin_1d(Tensor<T> tensor, Tensor<T>& min_tensor);
template<class T>
u32 argmin_1d(Tensor<T> tensor, T& min_);
template<class T>
u32 argmin_1d(Tensor<T> tensor, T& max_, u32 start_index);

// TODO
template<class T>
Tensor<T> sort_1d(Tensor<T> tensor,
                  bool(*compare)(T, T)=[](T a, T b){ return a > b? true: false; },
                  SORT_MODE mode=NORMAL);

}

}


#endif
