#include "./stride.h"

namespace SIMI
{

Stride::Stride(const u64 dim1)
    :_ndims(1)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64));
    _data.get()[0] = dim1;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2)
    :_ndims(2)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[2]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2,
               const u64 dim3)
    :_ndims(3)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[3]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2,
               const u64 dim3, const u64 dim4)
    :_ndims(4)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[4]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2,
               const u64 dim3, const u64 dim4,
               const u64 dim5)
    :_ndims(5)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[5]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2,
               const u64 dim3, const u64 dim4,
               const u64 dim5, const u64 dim6)
    :_ndims(6)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[6]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    _data.get()[5] = dim6;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64 dim1, const u64 dim2,
               const u64 dim3, const u64 dim4,
               const u64 dim5, const u64 dim6,
               const u64 dim7)
    :_ndims(7)
{
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[7]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    _data.get()[4] = dim5;
    _data.get()[5] = dim6;
    _data.get()[6] = dim7;
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const u64* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Shape's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const Uint64* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Stride's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const Stride& _stride)
    : _ndims(_stride.ndims())
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Stride's ndim should be more than 0(limit: 1-7).\n");

    u8 n = _stride.ndims().data();
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[n]));
    while(n--) { _data.get()[n]=_stride[n]; }
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
Stride::Stride(const Shape& _shape)
    : _ndims(_shape.ndims())
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Stride's ndim should be more than 0(limit: 1-7).\n");

    u8 n = _shape.ndims().data();
    _data = std::move(std::shared_ptr<Uint64>(new Uint64[n]));
    for(int i = n-1; i >= 0; i--) {
        if(i == n-1) _data.get()[i] = 1;
        else _data.get()[i] = _shape[i+1] * _data.get()[i+1];
    }
    assert(check_stride() && \
           "The Stride's value should all be more than 0(1-Max_Uint64).\n");
}
bool Stride::check_stride() const
{
    u8 n = _ndims.data();
    if(n == 0) {
        return false;
    } else {
        while(n--) if(_data.get()[n] <= 0) return false;
    }
    return true;
}

Stride Stride::clone() const
{
    return Stride(*this);
}
std::shared_ptr<Uint64> Stride::data() const
{
    return _data;
}

Uint64& Stride::operator[](const u32 index) const
{
    return _data.get()[index];
}

void Stride::operator=(const Stride& _stride)
{
    _ndims = _stride.ndims();
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Stride's ndim should be more than 0(limit: 1-7).\n");

    _data = _stride.data();
}

Bool Stride::operator==(const Stride& _stride) const
{
    if(_stride.ndims() != _ndims) return false;
    else {
        for(int i = 0; _stride.ndims() > i; i++) {
            if(!(_stride.data().get()[i] == _data.get()[i])) return false;
        }
    }
    return true;
}
Bool Stride::operator!=(const Stride& _stride) const
{
    int count = 0;
    if(_stride.ndims() != _ndims) return true;
    else {
        for(int i = 0; _stride.ndims() > i; i++) {
            if(!(_stride.data().get()[i] == _data.get()[i])) count++;
        }
    }
    if(count == 0) return false;
    return true;
}


std::ostream& operator<<(std::ostream& out, const Stride& stride)
{
    out << "Stride: [";
    if(stride.ndims() == 0) {
        out << "], ndims: " << 0 << ".)\n";
    }
    else {
        for(int i = 0; stride.ndims() > i; i++) {
            if(i == 0 && !((stride.ndims()-1) == i)) {
                out << stride[i] << ", ";
            } else if((stride.ndims()-1) == i) {
                out << stride[i] << "], ndims: " << stride.ndims() << ".";
            } else {
                out << stride[i] << ", ";
            }
        }
    }

    return out;
}

} // namespace SIMI
