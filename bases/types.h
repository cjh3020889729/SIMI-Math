#ifndef __SIMI_TYPES_BASE__
#define __SIMI_TYPES_BASE__
/*bases/types.h
* define: 类型预定义
* 
* 
*/
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <memory>

namespace SIMI {

// 基本实现接口/类
#define __NORMAL__
// 数据接口/数据定义
#define __DATA__
// 算法接口
#define __ALGORITHM__
// 未实现接口
#define __UMIMPLEMENT__
// 内部(不对外开放)静态接口/函数(模板显示实现无法限定，模板可限定)
#define __STATIC_API__                  static
// 内部(不对外开放)静态数据
#define __STATIC_DATA__                 static
// 模板类/模板方式的显示实现
#define __TEMPLATE_IMPL__
// 友元函数的实现
#define __FRIEND_IMPL__

#define TOSTR(x) #x

// 基本数据类型定义
__DATA__ typedef unsigned char           u8;
__DATA__ typedef unsigned short          u16;
__DATA__ typedef unsigned int            u32;
__DATA__ typedef unsigned long           u64;
__DATA__ typedef char                    int8;
__DATA__ typedef short                   int16;
__DATA__ typedef int                     int32;
__DATA__ typedef long                    int64;
__DATA__ typedef float                   float32;
__DATA__ typedef double                  float64;

#define LIMIT_FLOAT32_ZERO 2e-8
#define LIMIT_FLOAT64_ZERO 2e-16

// 类型ID枚举
__DATA__ typedef enum {
    U8 = 1,
    U16,
    U32,
    U64,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT32,
    FLOAT64,
    BOOL
} Elemment_Type;

__DATA__ class Type {
protected:
    Elemment_Type _type_id;

public:
    Type(Elemment_Type _id): _type_id(_id) {}
    Elemment_Type type_id() { return _type_id; }
};

// 类型申明
__DATA__ class Float32;
__DATA__ class Float64;
__DATA__ class Int8;
__DATA__ class Int16;
__DATA__ class Int32;
__DATA__ class Int64;
__DATA__ class Uint8;
__DATA__ class Uint16;
__DATA__ class Uint32;
__DATA__ class Uint64;
__DATA__ class Bool;


// 数据最高维度为7维(有效)
#define MAX_NDIMS 7
// 数据最低维度为1维(有效)
#define MIN_NDIMS 1
// 检查数据大小
#define CHECK_MIN(data,limit) ((data) >= (limit))
#define CHECK_MAX(data,limit) ((data) <= (limit))
#define CHECK_MIN_MAX(data,limit_min,limit_max) (((data) >= (limit_min)) && ((data) <= (limit_max)))
// Shape申明
__NORMAL__ class Shape;
// Stride申明
__NORMAL__ class Stride;
// Slice申明
__NORMAL__ class Slice;
// SliceTuple申明
__NORMAL__ class SliceTuple;
// Tensor申明
template<class T>
__DATA__ class Tensor;

// 定义模板类的类型名称
#define CONNECT_TEMPLATE_LEFT_EXPR(x) #x"<"
#define CONNECT_TEMPLATE_RIGHT_EXPR(x) #x">"
#define DEFINE_TYPE_NAME(base_type, template_type) CONNECT_TEMPLATE_LEFT_EXPR(base_type)CONNECT_TEMPLATE_RIGHT_EXPR(template_type)

} // namespace SIMI


#endif
