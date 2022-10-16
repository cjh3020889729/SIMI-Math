#ifndef __SIMI_SOLVES_ALGORITHM_
#define __SIMI_SOLVES_ALGORITHM_

#include "../bases/types.h"
#include "../bases/basetype.h"
#include "../bases/shape.h"
#include "../bases/slice.h"
#include "../bases/stride.h"
#include "../bases/tensor.h"
#include "../bases/debugs.h"
#include "../algorithms/utils.h"

namespace SIMI {

namespace SOLVES {

template<class T>
Tensor<T> gaussian_elimination_solve(Tensor<T>& tensor);

template<class T>
Tensor<T> lu_solve(Tensor<T>& l_tensor, Tensor<T>& u_tensor, Tensor<T>& b_tensor);

}

}

#endif
