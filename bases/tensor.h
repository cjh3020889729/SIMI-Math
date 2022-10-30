#ifndef __SIMI_TENSOR_BASE__
#define __SIMI_TENSOR_BASE__

#include "basetype.h"
#include "shape.h"
#include "stride.h"
#include "slice.h"
#include "debugs.h"

// Needs: +-*/--
// Needs: 类型强转支持以及自动升级转类型
// TODO: Init fucntions
// TODO: loop functions
// TODO: 赋值=的智能指针_data直接赋值，其计数是否受影响

namespace SIMI {


template<class T>
__DATA__ class Tensor {
private:
    const char* _name;

private:
    std::shared_ptr<T> _data;
    Elemment_Type _type;
    Uint8 _ndims;
    Uint64 _elem_num;
    Stride stride;
    Shape shape;

public:
    __NORMAL__ Tensor(const u32 dim1); // 1D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2); // 2D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2,
           const u32 dim3); // 3D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4); // 4D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5); // 5D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5, const u32 dim6); // 6D tensor
    __NORMAL__ Tensor(const u32 dim1, const u32 dim2,
           const u32 dim3, const u32 dim4,
           const u32 dim5, const u32 dim6,
           const u32 dim7); // 7D tensor
    __NORMAL__ Tensor();
    __NORMAL__ Tensor(const u32* _shape, const u8 ndims); // TODO
    __NORMAL__ Tensor(const Uint32* _shape, const u8 ndims); // TODO
    __NORMAL__ Tensor(const Shape& _shape); // TODO
    // 深复制
    __NORMAL__ Tensor(const Tensor& _tensor);
    __NORMAL__ Bool check_ndims() const { return _ndims > 0; }
    __NORMAL__ Bool check_elem_number() const { return _elem_num > 0; }

    __NORMAL__ Tensor clone() const; // TODO
    __NORMAL__ std::shared_ptr<T> data() const;
    __NORMAL__ const char* name() const { return _name; }
    __NORMAL__ Uint8 ndims() const { return _ndims; }
    __NORMAL__ Uint64 elem_num() const { return _elem_num; }
    __NORMAL__ Elemment_Type dtype() const { return _type; }
    __NORMAL__ Shape get_shape() const { return shape; }

    // TODO: 快速操作--全1，全0，对角填充，随机对角填充，随机填充
    __NORMAL__ void zeros();
    __NORMAL__ void ones();
    __NORMAL__ void diag_fill(T value);
    __NORMAL__ void diag_fill(T* value, const u32 n);
    __NORMAL__ void diag_rand();
    __NORMAL__ void rand();

    // TODO: 区间切分
    // __NORMAL__ Tensor& operator[](const Slice& iloc); // 取出一部分Tensor数据——智能判断shape, 保留头部dim_size=1的维度
    // __NORMAL__ Tensor& operator[](const SliceTuple& ilocs); // 取出区间的Tensor数据——智能判断shape, 保留头部dim_size=1的维度
    
    __NORMAL__ const T& at(const u32 index) const; // 1d-find
    __NORMAL__ const T& at(const u32 index1, const u32 index2) const; // 2d-find
    // TODO: 3d -> 7d find

    __NORMAL__ T& iloc(const u32 index) const; // 1d-find
    __NORMAL__ T& iloc(const u32 index1, const u32 index2) const; // 2d-find
    // TODO: 3d -> 7d find

    __NORMAL__ void operator=(const Tensor& tensor);
    // First TODO: 右运算 +,-,*,/,+=,-=,*=,/=,++,--
    __NORMAL__ Tensor& operator++(); // 前缀++
    __NORMAL__ Tensor& operator--(); // 前缀--
    __NORMAL__ Tensor operator++(int); // 后缀++
    __NORMAL__ Tensor operator--(int); // 后缀--
#define DEFINE_TYPE Float64
#define DEFINE_SUBTYPE float64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const; // float32 自动升为 float64 -- 内部控制实际运算类型即可
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Float64
#define DEFINE_SUBTYPE Float64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
// TODO:
#define DEFINE_TYPE Int64
#define DEFINE_SUBTYPE int64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const; // int8/16/32 自动升为 int64 -- 内部控制实际运算类型即可
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Int64
#define DEFINE_SUBTYPE Int64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Uint64
#define DEFINE_SUBTYPE u64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const; // uint8/16/32 自动升为 uint64 -- 内部控制实际运算类型即可
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Uint64
#define DEFINE_SUBTYPE Uint64
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Bool
#define DEFINE_SUBTYPE bool
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
#define DEFINE_TYPE Bool
#define DEFINE_SUBTYPE Bool
    __NORMAL__ Tensor operator+(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator-(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator*(const DEFINE_SUBTYPE value) const;
    __NORMAL__ Tensor operator/(const DEFINE_SUBTYPE value) const;
    __NORMAL__ void operator+=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator-=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator*=(const DEFINE_SUBTYPE value);
    __NORMAL__ void operator/=(const DEFINE_SUBTYPE value);
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPE
    __NORMAL__ Tensor operator+(const Tensor& tensor) const;
    __NORMAL__ Tensor operator-(const Tensor& tensor) const;
    __NORMAL__ Tensor operator*(const Tensor& tensor) const;
    __NORMAL__ Tensor operator/(const Tensor& tensor) const;
    __NORMAL__ void operator+=(const Tensor& tensor);
    __NORMAL__ void operator-=(const Tensor& tensor);
    __NORMAL__ void operator*=(const Tensor& tensor);
    __NORMAL__ void operator/=(const Tensor& tensor);

    // Second TODO: 右运算 &&, ||, ==, !=, ! --> 整型支持~, ^


    // Third TODO: 左运算(friend) +,-,*,/,+=,-=,*=,/=,++,--


    // Fourth TODO: 左运算(friend) &&, ||, ==, !=, ! --> 整型支持~, ^



    template<class _T>
    __NORMAL__ friend std::ostream& operator<<(std::ostream& out, const Tensor<_T>& tensor);
    template<class _T>
    __NORMAL__ friend void loop_1d(std::ostream& out, const Tensor<_T>& _tensor);
    template<class _T>
    __NORMAL__ friend void loop_2d(std::ostream& out, const Tensor<_T>& _tensor);
    // TODO:
    template<class _T>
    __NORMAL__ friend void loop_3d(std::ostream& out, const Tensor<_T>& _tensor);
    template<class _T>
    __NORMAL__ friend void loop_4d(std::ostream& out, const Tensor<_T>& _tensor);
    template<class _T>
    __NORMAL__ friend void loop_5d(std::ostream& out, const Tensor<_T>& _tensor);
    template<class _T>
    __NORMAL__ friend void loop_6d(std::ostream& out, const Tensor<_T>& _tensor);
    template<class _T>
    __NORMAL__ friend void loop_7d(std::ostream& out, const Tensor<_T>& _tensor);
};

}



#endif
