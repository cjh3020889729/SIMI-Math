#ifndef __SIMI_STRIDE_BASE__
#define __SIMI_STRIDE_BASE__

#include "./basetype.h"
#include "./shape.h"


namespace SIMI {

__NORMAL__ class Stride {
private:
    std::shared_ptr<Uint64> _data;
    Uint8 _ndims;

public:
    Stride(const u64 dim1); // 1D stride
    Stride(const u64 dim1, const u64 dim2); // 2D stride
    Stride(const u64 dim1, const u64 dim2,
           const u64 dim3); // 3D stride
    Stride(const u64 dim1, const u64 dim2,
           const u64 dim3, const u64 dim4); // 4D stride
    Stride(const u64 dim1, const u64 dim2,
           const u64 dim3, const u64 dim4,
           const u64 dim5); // 5D stride
    Stride(const u64 dim1, const u64 dim2,
           const u64 dim3, const u64 dim4,
           const u64 dim5, const u64 dim6); // 6D stride
    Stride(const u64 dim1, const u64 dim2,
           const u64 dim3, const u64 dim4,
           const u64 dim5, const u64 dim6,
           const u64 dim7); // 7D stride
    Stride(): _ndims(0) {}
    Stride(const u64* _stride, const u8 ndims);
    Stride(const Uint64* _stride, const u8 ndims);
    // 深复制
    Stride(const Stride& _stride);
    Stride(const Shape& _shape); // 从shape生成stride
    bool check_stride() const;

    Stride clone() const;
    std::shared_ptr<Uint64> data() const;
    Uint8 ndims() const { return _ndims; }

    Uint64& operator[](const u32 index) const;
    // 浅复制
    void operator=(const Stride& _stride);
    Bool operator==(const Stride& _stride) const;
    Bool operator!=(const Stride& _stride) const;


    friend std::ostream& operator<<(std::ostream& out, const Stride& _stride);
};

} // namespace SIMI


#endif
