#include "slice.h"

namespace SIMI {

// Class Slice
Slice::Slice(const u32 dim1)
    : _ndims(1)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[1]));
    _data.get()[0] = dim1;
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2)
    : _ndims(2)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[2]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2,
             const u32 dim3)
    : _ndims(3)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[3]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2,
             const u32 dim3, const u32 dim4)
    : _ndims(4)
{
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[4]));
    _data.get()[0] = dim1;
    _data.get()[1] = dim2;
    _data.get()[2] = dim3;
    _data.get()[3] = dim4;
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2,
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
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2,
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
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32 dim1, const u32 dim2,
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
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const u32* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Slice's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const Uint32* _shape, const u8 ndims)
    : _ndims(ndims)
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Slice's ndim should be more than 0(limit: 1-7).\n");

    int n = ndims;
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_shape[n]; }
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
Slice::Slice(const Slice& _slice)
    : _ndims(_slice.ndims())
{
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Slice's ndim should be more than 0(limit: 1-7).\n");

    u8 n = _slice.ndims().data();
    _data = std::move(std::shared_ptr<Uint32>(new Uint32[n]));
    while(n--) { _data.get()[n]=_slice[n]; }
    assert(check_slice() && \
           "The Slice's value should all be more than 0(1-Max_Uint32).\n");
}
bool Slice::check_slice() const
{
    u8 n = _ndims.data();
    if(n == 0) {
        return false;
    } else {
        while(n--) if(_data.get()[n] < 0) return false;
    }
    return true;
}

Uint64 Slice::get_location(const Shape& shape, const Stride& stride) const
{
    assert((_ndims.toint32() != 0) && \
               "The Slice's ndim size should more than 0(limit: 1-7).\n");

    u64 _temp = 0;
    for(int32 i = 0; i < _ndims.toint32(); i++) {
        int32 _dim_shape_size = shape.data().get()[i].toint32();
        int32 _dim_slice_size = _data.get()[i].toint32();
        assert((_dim_slice_size < _dim_shape_size) && \
               "The Slice's dim size should less than Shape's dim size.\n");
        int64 _dim_stride_size = stride.data().get()[i].toint64();
        _temp += (_dim_slice_size * _dim_stride_size); // 每一个dim_slice乘上对应的步长
    }
    return _temp;
}

Slice Slice::clone() const
{
    return Slice(*this);
}
std::shared_ptr<Uint32> Slice::data() const
{
    return _data;
}

Uint32& Slice::operator[](const u32 index) const
{
    return _data.get()[index];
}

void Slice::operator=(const Slice& _slice)
{
    _ndims = _slice.ndims();
    assert(CHECK_MIN_MAX(_ndims,MIN_NDIMS,MAX_NDIMS) && \
    "The Slice's ndim should be more than 0(limit: 1-7).\n");

    _data = _slice.data();
}

Bool Slice::operator==(const Slice& _slice) const
{
    if(_slice.ndims() != _ndims) return false;
    else {
        for(int i = 0; _slice.ndims() > i; i++) {
            if(!(_slice.data().get()[i] == _data.get()[i])) return false;
        }
    }
    return true;
}
Bool Slice::operator!=(const Slice& _slice) const
{
    int count = 0;
    if(_slice.ndims() != _ndims) return true;
    else {
        for(int i = 0; _slice.ndims() > i; i++) {
            if(!(_slice.data().get()[i] == _data.get()[i])) count++;
        }
    }
    if(count == 0) return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Slice& slice)
{
    out << "Slice: [";
    if(slice.ndims() == 0) {
        out << "], ndims: " << 0 << ".)\n";
    }
    else {
        for(int i = 0; slice.ndims() > i; i++) {
            if(i == 0 && !((slice.ndims()-1) == i)) {
                out << slice[i] << ", ";
            } else if((slice.ndims()-1) == i) {
                out << slice[i] << "], ndims: " << slice.ndims() << ".";
            } else {
                out << slice[i] << ", ";
            }
        }
    }

    return out;
}


// Class SliceTuple
SliceTuple::SliceTuple(const Slice& start_s, const Slice& end_s)
{
    start_location = start_s;
    end_location = end_s;
}
SliceTuple::SliceTuple(const SliceTuple& s_tuple)
{
    start_location = Slice(s_tuple.start());
    end_location = Slice(s_tuple.end());
}
const Slice& SliceTuple::start() const
{
    return start_location;
}
const Slice& SliceTuple::end() const
{
    return end_location;
}
void SliceTuple::set_start(const Slice& start_s)
{
    start_location = Slice(start_s);
}
void SliceTuple::set_end(const Slice& end_s)
{
    end_location = Slice(end_s);
}
void SliceTuple::operator=(const SliceTuple& s_tuple)
{
    start_location = s_tuple.start();
    end_location = s_tuple.end();
}
Bool SliceTuple::operator==(const SliceTuple& s_tuple) const
{
    if((s_tuple.start() == start_location).tobool()) {
        if((s_tuple.end() == end_location).tobool()) return true;
    }
    return false;
}
Bool SliceTuple::operator!=(const SliceTuple& s_tuple) const
{
    if((s_tuple.start() != start_location).tobool()) {
        if((s_tuple.end() != end_location).tobool()) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const SliceTuple& s_tuple)
{
    out << "(SliceTuple:\n";
    out << "\tStart_Slice: [";
    Slice slice = s_tuple.start();
    if(slice.ndims() == 0) {
        out << "], ndims: " << 0 << ".)\n";
    }
    else {
        for(int i = 0; slice.ndims() > i; i++) {
            if(i == 0 && !((slice.ndims()-1) == i)) {
                out << slice[i] << ", ";
            } else if((slice.ndims()-1) == i) {
                out << slice[i] << "], ndims: " << slice.ndims() << ".\n";
            } else {
                out << slice[i] << ", ";
            }
        }
    }
    out << "\tEnd_Slice: [";
    slice = s_tuple.end();
    if(slice.ndims() == 0) {
        out << "], ndims: " << 0 << ".)\n";
    }
    else {
        for(int i = 0; slice.ndims() > i; i++) {
            if(i == 0 && !((slice.ndims()-1) == i)) {
                out << slice[i] << ", ";
            } else if((slice.ndims()-1) == i) {
                out << slice[i] << "], ndims: " << slice.ndims() << ".\n)\n";
            } else {
                out << slice[i] << ", ";
            }
        }
    }

    return out;
}

}