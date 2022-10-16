#include "./tensor.h"


namespace SIMI {

/* Start implement Float64-Tensor
* 
*
*
*/
#define DEFINE_TYPE Float64
// Class Main
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor()
    : _ndims(0), _elem_num(0), _type(FLOAT32) 
{ 
    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1)
    : _ndims(1), _elem_num(dim1)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1]));
    memset(_data.get(), 0, dim1*sizeof(DEFINE_TYPE));
    shape = Shape(dim1);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2)
    : _ndims(2), _elem_num(dim1*dim2)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2]));
    memset(_data.get(), 0, dim1*dim2*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2,
             const u32 dim3)
    : _ndims(3), _elem_num(dim1*dim2*dim3)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2*dim3]));
    memset(_data.get(), 0, dim1*dim2*dim3*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2, dim3);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4)
    : _ndims(4), _elem_num(dim1*dim2*dim3*dim4)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2*dim3*dim4]));
    memset(_data.get(), 0, dim1*dim2*dim3*dim4*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2, dim3, dim4);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__  Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5)
    : _ndims(5), _elem_num(dim1*dim2*dim3*dim4*dim5)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2*dim3*dim4*dim5]));
    memset(_data.get(), 0, dim1*dim2*dim3*dim4*dim5*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2, dim3, dim4, dim5);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5, const u32 dim6)
    : _ndims(6), _elem_num(dim1*dim2*dim3*dim4*dim5*dim6)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2*dim3*dim4*dim5*dim6]));
    memset(_data.get(), 0, dim1*dim2*dim3*dim4*dim5*dim6*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2, dim3, dim4, dim5, dim6);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5, const u32 dim6,
             const u32 dim7)
    : _ndims(7), _elem_num(dim1*dim2*dim3*dim4*dim5*dim6*dim7)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[dim1*dim2*dim3*dim4*dim5*dim6*dim7]));
    memset(_data.get(), 0, dim1*dim2*dim3*dim4*dim5*dim6*dim7*sizeof(DEFINE_TYPE));
    shape = Shape(dim1, dim2, dim3, dim4, dim5, dim6, dim7);
    stride = Stride(shape);
    _type = _data.get()[0].type_id();

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>::Tensor(const Tensor<DEFINE_TYPE>& _tensor)
{
    _data = std::move(std::shared_ptr<DEFINE_TYPE>(new DEFINE_TYPE[_tensor.elem_num().touint64()]));

    for(int i = 0; _tensor.elem_num() > i; i++) {
        _data.get()[i] = _tensor._data.get()[i];
    }

    shape = _tensor.shape.clone();
    stride = _tensor.stride.clone();
    _type = _tensor._type;
    _ndims = _tensor._ndims;
    _elem_num = _tensor._elem_num;

    _name = DEFINE_TYPE_NAME(Tensor, DEFINE_TYPE);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::clone() const
{
    return Tensor<DEFINE_TYPE>(*this);
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ std::shared_ptr<DEFINE_TYPE> Tensor<DEFINE_TYPE>::data() const
{
    return _data;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator=(const Tensor<DEFINE_TYPE>& tensor)
{ // copy from deep copy -- keep ptr
    _data = tensor._data;
    shape = tensor.shape;
    stride = tensor.stride;
    _type = tensor._type;
    _ndims = tensor._ndims;
    _elem_num = tensor._elem_num;
}




template<>
__NORMAL__ __TEMPLATE_IMPL__ const DEFINE_TYPE& Tensor<DEFINE_TYPE>::at(const u32 index) const
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
    CLASS_ASSERT_QUIT((_elem_num > index) && \
           "The Tensor's find index should be less than _elem_num.\n", _name);

    return _data.get()[index];
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ const DEFINE_TYPE& Tensor<DEFINE_TYPE>::at(const u32 index1, const u32 index2) const
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Slice slice(index1, index2);
    return _data.get()[slice.get_location(shape, stride).touint64()];
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ DEFINE_TYPE& Tensor<DEFINE_TYPE>::iloc(const u32 index) const
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
    CLASS_ASSERT_QUIT((_elem_num > index) && \
           "The Tensor's find index should be less than _elem_num.\n", _name);

    return _data.get()[index];
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ DEFINE_TYPE& Tensor<DEFINE_TYPE>::iloc(const u32 index1, const u32 index2) const
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Slice slice(index1, index2);
    return _data.get()[slice.get_location(shape, stride).touint64()];
}


template<>
__NORMAL__ void Tensor<DEFINE_TYPE>::ones()
{
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = 1.;
    }
}
template<>
__NORMAL__ void Tensor<DEFINE_TYPE>::zeros()
{
    memset(_data.get(), 0, _elem_num.touint64()*sizeof(DEFINE_TYPE));
}
template<>
__NORMAL__ void Tensor<DEFINE_TYPE>::diag_fill(DEFINE_TYPE value)
{
    for(int i = 0; i < shape[0].toint32() && i < shape[1].touint32(); i++) {
        this->iloc(i, i) = value;
    }
}

template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>& Tensor<DEFINE_TYPE>::operator++()
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] + 1;
    }
    return *this;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE>& Tensor<DEFINE_TYPE>::operator--()
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] - 1;
    }
    return *this;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator++(int)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] + 1;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator--(int)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] - 1;
    }
    return _temp;
}

#define DEFINE_TYPE Float64
#define DEFINE_SUBTYPE float64
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator+(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] + value; // 自动转换类型
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator-(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] - value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator*(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] * value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator/(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] / value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator+=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] + value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator-=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] - value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator*=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] * value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator/=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] / value;
    }
}
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#define DEFINE_TYPE Float64
#define DEFINE_SUBTYPE Float64
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator+(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);

    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] + value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator-(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] - value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator*(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] * value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator/(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _data.get()[i] / value;
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator+=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] + value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator-=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] - value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator*=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] * value;
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator/=(const DEFINE_SUBTYPE value)
{
    CLASS_ASSERT_QUIT(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n", _name);
           
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] / value;
    }
}
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE








#define DEFINE_TYPE Float64
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator+(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _temp._data.get()[i] + tensor._data.get()[i];
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator-(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _temp._data.get()[i] - tensor._data.get()[i];
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator*(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _temp._data.get()[i] * tensor._data.get()[i];
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ Tensor<DEFINE_TYPE> Tensor<DEFINE_TYPE>::operator/(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    Tensor<DEFINE_TYPE> _temp(*this);
    for(int i = 0; _elem_num > i; i++) {
        _temp._data.get()[i] = _temp._data.get()[i] / tensor._data.get()[i];
    }
    return _temp;
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator+=(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] + tensor._data.get()[i];
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator-=(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] - tensor._data.get()[i];
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator*=(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] * tensor._data.get()[i];
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Tensor<DEFINE_TYPE>::operator/=(const Tensor<DEFINE_TYPE>& tensor)
{
    assert(check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");
    assert(tensor.elem_num() == this->elem_num() && \
           "The Tensor1's elemment number should be same as the Tensor2's elemment number.\n");
    
    for(int i = 0; _elem_num > i; i++) {
        _data.get()[i] = _data.get()[i] / tensor._data.get()[i];
    }
}



// define print loop function
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_1d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{
    out << "(Tensor:\n[";
    if(_tensor.ndims() == 0) {
        out << "], " << _tensor.shape << ")\n";
    }
    else if(_tensor.ndims() == 1) {
        for(int i = 0; _tensor.elem_num() > i; i++) {
            if(i == 0 && !((_tensor.elem_num()-1) == i)) {
                out << _tensor.at(i) << ", ";
            } else if((_tensor.elem_num()-1) == i) {
                out << _tensor.at(i) << "], " << _tensor.shape << ")\n";
            } else {
                out << _tensor.at(i) << ", ";
            }
        }
    }
    else {
        out << "Tensor print warning: it can't print by 1d-shape.\n";
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_2d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{
    out << "(Tensor:\n[";
    if(_tensor.ndims() == 0) {
        out << "], " << _tensor.shape << ")\n";
    }
    else if(_tensor.ndims() == 2) {
        for(int i = 0; _tensor.shape[0] > i; i++) {
            for(int j = 0; _tensor.shape[1] > j; j++) {
                if(j == 0 && ((_tensor.shape[1]-1) == j) && !((_tensor.shape[0]-1) == i)) { // 对于列向量的特别处理
                    out << "[" << _tensor.at(i, j) << "]," << "\n";
                } else if(j == 0 && ((_tensor.shape[1]-1) == j)) {
                    out << "[" << _tensor.at(i, j) << "]], " << _tensor.shape << ")\n";
                } else if(j == 0) {
                    out << "[" << _tensor.at(i, j) << ", ";
                } else if((_tensor.shape[1]-1) == j) {
                    if((_tensor.shape[0]-1) == i) {
                        out << _tensor.at(i, j) << "]], " << _tensor.shape << ")\n";
                    } else {
                        out << _tensor.at(i, j) << "]," << "\n";
                    }
                } else {
                    out << _tensor.at(i, j) << ", ";
                }
            }
        }
    }
    else {
        out << "Tensor print warning: it can't print by 2d-shape.\n";
    }
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_3d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{

}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_4d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{

}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_5d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{

}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_6d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{

}
template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ void loop_7d(std::ostream& out, const Tensor<DEFINE_TYPE>& _tensor)
{

}

template<>
__NORMAL__ __TEMPLATE_IMPL__ __FRIEND_IMPL__ std::ostream& operator<<(std::ostream& out, const Tensor<DEFINE_TYPE>& tensor)
{
    assert(tensor.check_elem_number().tobool() && \
           "The Tensor's elemment number should be more than 0.\n");

    switch (tensor.ndims().touint8())
    {
    case 1:
        loop_1d(out, tensor);
        break;
    case 2:
        loop_2d(out, tensor);
        break;
    case 3:
        loop_3d(out, tensor);
        break;
    case 4:
        loop_4d(out, tensor);
        break;
    case 5:
        loop_5d(out, tensor);
        break;
    case 6:
        loop_6d(out, tensor);
        break;
    case 7:
        loop_7d(out, tensor);
        break;
    default:
        CLASS_ERROR_QUIT("The Tensor print error: only support the 1-7 ndims' tensor.", tensor.name());
        break;
    }
    return out;
}
#undef DEFINE_TYPE
/* End implement Float64-Tensor */



}