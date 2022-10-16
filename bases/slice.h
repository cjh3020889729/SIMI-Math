#ifndef __SIMI_SLICE_BASE__
#define __SIMI_SLICE_BASE__

#include "basetype.h"
#include "shape.h"
#include "stride.h"

namespace SIMI {

__NORMAL__ class Slice {
private:
    std::shared_ptr<Uint32> _data;
    Uint8 _ndims;

public:
    Slice(const u32 dim1); // 1D slice
    Slice(const u32 dim1, const u32 dim2); // 2D slice
    Slice(const u32 dim1, const u32 dim2,
           const u32 dim3); // 3D slice
    Slice(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4); // 4D slice
    Slice(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5); // 5D slice
    Slice(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5, const u32 dim6); // 6D slice
    Slice(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5, const u32 dim6,
           const u32 dim7); // 7D slice
    Slice(): _ndims(0) {}
    Slice(const u32* _stride, const u8 ndims);
    Slice(const Uint32* _stride, const u8 ndims);
    // 深复制
    Slice(const Slice& _slice);
    bool check_slice() const;

    Uint64 get_location(const Shape& shape, const Stride& stride) const;
    
    Slice clone() const;
    std::shared_ptr<Uint32> data() const;
    Uint8 ndims() const { return _ndims; }

    Uint32& operator[](const u32 index) const;
    // 浅复制
    void operator=(const Slice& _slice);
    Bool operator==(const Slice& _slice) const;
    Bool operator!=(const Slice& _slice) const;


    friend std::ostream& operator<<(std::ostream& out, const Slice& _slice);
};


class SliceTuple {
private:
    Slice start_location; // 起始位置
    Slice end_location; // 结束位置

public:
    SliceTuple(const Slice& start_s, const Slice& end_s);
    SliceTuple(const SliceTuple& s_tuple);

    const Slice& start() const;
    const Slice& end() const;

    void set_start(const Slice& start_s);
    void set_end(const Slice& end_s);

    void operator=(const SliceTuple& s_tuple);
    Bool operator==(const SliceTuple& s_tuple) const;
    Bool operator!=(const SliceTuple& s_tuple) const;


    friend std::ostream& operator<<(std::ostream& out, const SliceTuple& s_tuple);
};

} // namespace SIMI


#endif
