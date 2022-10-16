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

#define CHECK_ZERO(tensor_elemment) (abs(tensor_elemment) == 0)
#define CHECK_FLOAT32_ELEM_ZERO(tensor_elemment) (fabs(tensor_elemment.tofloat32()) < LIMIT_FLOAT32_ZERO)
#define CHECK_FLOAT64_ELEM_ZERO(tensor_elemment) (fabs(tensor_elemment.tofloat64()) < LIMIT_FLOAT64_ZERO)

typedef enum {
    NORMAL=1,
    QUICK_SORT
} SORT_MODE;

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
