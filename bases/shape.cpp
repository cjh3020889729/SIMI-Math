#include "./shape.h"

namespace SIMI {


Shape::Shape(const u32 dim1)
    : _ndims(1)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[1]));
    _data.get()[0] = dim1;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2)
    : _ndims(2)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[2]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2,
             const u32 dim3)
    : _ndims(3)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[3]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4)
    : _ndims(4)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[4]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5)
    : _ndims(5)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[5]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5, const u32 dim6)
    : _ndims(6)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[6]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    _data.get()[5] = dim6;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4,
             const u32 dim5, const u32 dim6,
             const u32 dim7)
    : _ndims(7)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[7]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    _data.get()[5] = dim6;
    _data.get()[6] = dim7;
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const u32* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Shape's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const Uint32* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Shape's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
Shape::Shape(const Shape& _shape)
    : _ndims(_shape.ndims())
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Shape's ndim should be more than 0(limit: 1-7).\n");

    u8 n = _shape.ndims().data();
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_shape() && \
           "The Shape's value should all be more than 0(1-Max_Uint32).\n");
}
bool Shape::check_shape() const
{
    u8 n = _ndims.data();
    if(n == 0) {
        return false;
    } else {
        while(n--) if(_data.get()[n] <= 0) return false;
    }
    return true;
}

Shape Shape::clone() const
{
    return Shape(*this);
}
std::shared_ptr<Uint32> Shape::data() const
{
    return _data;
}

Uint32& Shape::operator[](const u32 index) const
{
    return _data.get()[index];
}

void Shape::operator=(const Shape& _shape)
{
    _ndims = _shape.ndims();
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Shape's ndim should be more than 0(limit: 1-7).\n");

    _data = _shape.data(); // count+1
}

Bool Shape::operator==(const Shape& _shape) const
{
    if(_shape.ndims() != _ndims) return false;
    else {
        for(int i = 0; _shape.ndims() > i; i++) {
            if(!(_shape.data().get()[i] == _data.get()[i])) return false;
        }
    }
    return true;
}

Bool Shape::operator!=(const Shape& _shape) const
{
    int count = 0;
    if(_shape.ndims() != _ndims) return true;
    else {
        for(int i = 0; _shape.ndims() > i; i++) {
            if(!(_shape.data().get()[i] == _data.get()[i])) count++;
        }
    }
    if(count == 0) return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
    out << "Shape: [";
    if(shape.ndims() == 0) {
        out << "], ndims: " << 0 << ".)\n";
    }
    else {
        for(int i = 0; shape.ndims() > i; i++) {
            if(i == 0 && !((shape.ndims()-1) == i)) {
                out << shape[i] << ", ";
            } else if((shape.ndims()-1) == i) {
                out << shape[i] << "], ndims: " << shape.ndims() << ".";
            } else {
                out << shape[i] << ", ";
            }
        }
    }

    return out;
}

} // namespace SIMI