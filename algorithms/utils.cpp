#include "./utils.h"

namespace SIMI {

namespace UTILS {

#define DEFINE_TYPE Float64
template<>
u32 argmax_1d(Tensor<DEFINE_TYPE> tensor, DEFINE_TYPE& max_, u32 start_index)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmax_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmax_1d only support the 1d tensor, which has >= start_index+1 elemment.");                 
    
    u32 _elem_num = tensor.elem_num().touint32();
    u32 _max_index = start_index;
    DEFINE_TYPE _max = tensor.at(start_index);

    for(int i = start_index+1; i < _elem_num; i++) {
        if(_max < tensor.at(i)) {
            _max = tensor.at(i);
            _max_index = i;
        }
    }
    max_ = _max;
    return _max_index - start_index;
}
template<>
u32 argmax_1d(Tensor<DEFINE_TYPE> tensor, DEFINE_TYPE& max_)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmax_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmax_1d only support the 1d tensor, which has >= 1 elemment.");                 

    return argmax_1d(tensor, max_, 0);
}
template<>
u32 argmax_1d(Tensor<DEFINE_TYPE> tensor)
{
    DEFINE_TYPE _max = 0;
    return argmax_1d(tensor, _max);
}
template<>
u32 argmax_1d(Tensor<DEFINE_TYPE> tensor, u32 start_index)
{
    DEFINE_TYPE _max = 0;
    return argmax_1d(tensor, _max, start_index);
}
template<>
u32 argmax_1d(Tensor<DEFINE_TYPE> tensor, Tensor<DEFINE_TYPE>& max_tensor)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmax_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmax_1d only support the 1d tensor, which has >= 1 elemment.");                 

    u32 _elem_num = tensor.elem_num().touint32();
    u32 _max_index = 0;
    DEFINE_TYPE _max = tensor.at(0);

    for(int i = 1; i < _elem_num; i++) {
        if(_max < tensor.at(i)) {
            _max = tensor.at(i);
            _max_index = i;
        }
    }
    max_tensor.iloc(0) = _max;
    return _max_index;
}


template<>
u32 argmin_1d(Tensor<DEFINE_TYPE> tensor, DEFINE_TYPE& min_, u32 start_index)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmin_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmin_1d only support the 1d tensor, which has >= start_index+1 elemment.");                 
    
    u32 _elem_num = tensor.elem_num().touint32();
    u32 _min_index = start_index;
    DEFINE_TYPE _min = tensor.at(start_index);

    for(int i = start_index+1; i < _elem_num; i++) {
        if(_min > tensor.at(i)) {
            _min = tensor.at(i);
            _min_index = i;
        }
    }
    min_ = _min;
    return _min_index - start_index;
}
template<>
u32 argmin_1d(Tensor<DEFINE_TYPE> tensor, DEFINE_TYPE& min_)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmin_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmin_1d only support the 1d tensor, which has >= 1 elemment.");                 

    return argmin_1d(tensor, min_, 0);
}
template<>
u32 argmin_1d(Tensor<DEFINE_TYPE> tensor)
{
    DEFINE_TYPE _min = 0;
    return argmin_1d(tensor, _min);
}
template<>
u32 argmin_1d(Tensor<DEFINE_TYPE> tensor, u32 start_index)
{
    DEFINE_TYPE _min = 0;
    return argmin_1d(tensor, _min, start_index);
}
template<>
u32 argmin_1d(Tensor<DEFINE_TYPE> tensor, Tensor<DEFINE_TYPE>& min_tensor)
{
    UTILS_ASSERT_QUIT(tensor.ndims()==1 && \
                      "The argmin_1d only support the 1d tensor.");
    UTILS_ASSERT_QUIT(tensor.elem_num()>=1 && \
                      "The argmin_1d only support the 1d tensor, which has >= 1 elemment.");                 

    u32 _elem_num = tensor.elem_num().touint32();
    u32 _min_index = 0;
    DEFINE_TYPE _min = tensor.at(0);

    for(int i = 1; i < _elem_num; i++) {
        if(_min > tensor.at(i)) {
            _min = tensor.at(i);
            _min_index = i;
        }
    }
    min_tensor.iloc(0) = _min;
    return _min_index;
}

#undef DEFINE_TYPE

}

}
