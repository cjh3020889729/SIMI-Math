#ifndef __SIMI_SHAPE_BASE__
#define __SIMI_SHAPE_BASE__

#include "./types.h"
#include "./basetype.h"


namespace SIMI {

__NORMAL__ class Shape {
private:
    std::shared_ptr<Uint32> _data; // shape数据
    Uint8 _ndims; // shape维度大小

public:
    Shape(const u32 dim1); // 1D shape
    Shape(const u32 dim1, const u32 dim2); // 2D shape
    Shape(const u32 dim1, const u32 dim2,
          const u32 dim3); // 3D shape
    Shape(const u32 dim1, const u32 dim2,
          const u32 dim3, const u32 dim4); // 4D shape
    Shape(const u32 dim1, const u32 dim2,
          const u32 dim3, const u32 dim4,
          const u32 dim5); // 5D shape
    Shape(const u32 dim1, const u32 dim2,
          const u32 dim3, const u32 dim4,
          const u32 dim5, const u32 dim6); // 6D shape
    Shape(const u32 dim1, const u32 dim2,
          const u32 dim3, const u32 dim4,
          const u32 dim5, const u32 dim6,
          const u32 dim7); // 7D shape
    Shape(): _ndims(0) {}
    Shape(const u32* _shape, const u8 ndims);
    Shape(const Uint32* _shape, const u8 ndims);
    // 深复制
    Shape(const Shape& _shape);
    bool check_shape() const;
    
    Shape clone() const;
    std::shared_ptr<Uint32> data() const;
    Uint8 ndims() const { return _ndims; }

    Uint32& operator[](const u32 index) const;

    // 浅复制
    void operator=(const Shape& _shape);
    Bool operator==(const Shape& _shape) const;
    Bool operator!=(const Shape& _shape) const;


    friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
};

} // namespace SIMI

#endif
