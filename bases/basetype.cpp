#include "./basetype.h"
/*bases/basetypes.cpp
* define: 重载类型实现
* 
* 
*/
namespace SIMI {

/* Class Float32
* 
*/
Float32::Float32(const Float64& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Int8& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Int16& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Int32& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Int64& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Uint8& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Uint16& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Uint32& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Uint64& value)
    : Type(FLOAT32)
{
    _data = value.data();
}
Float32::Float32(const Bool& value)
    : Type(FLOAT32)
{
    _data = value.data();
}



/* Class Float64
* 
*/
Float64::Float64(const Float32& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Int8& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Int16& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Int32& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Int64& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Uint8& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Uint16& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Uint32& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Uint64& value)
    : Type(FLOAT64)
{
    _data = value.data();
}
Float64::Float64(const Bool& value)
    : Type(FLOAT64)
{
    _data = value.data();
}

/* Class Int8
* 
*/
Int8::Int8(const Float32& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Float64& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Int16& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Int32& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Int64& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Uint8& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Uint16& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Uint32& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Uint64& value)
    : Type(INT8)
{
    _data = value.data();
}
Int8::Int8(const Bool& value)
    : Type(INT8)
{
    _data = value.data();
}

/* Class Int16
* 
*/
Int16::Int16(const Float32& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Float64& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Int8& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Int32& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Int64& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Uint8& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Uint16& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Uint32& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Uint64& value)
    : Type(INT16)
{
    _data = value.data();
}
Int16::Int16(const Bool& value)
    : Type(INT16)
{
    _data = value.data();
}

/* Class Int32
* 
*/
Int32::Int32(const Float32& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Float64& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Int8& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Int16& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Int64& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Uint8& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Uint16& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Uint32& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Uint64& value)
    : Type(INT32)
{
    _data = value.data();
}
Int32::Int32(const Bool& value)
    : Type(INT32)
{
    _data = value.data();
}


/* Class Int64
* 
*/
#define DEFINE_TYPE Int64
#define DEFINE_TYPEID INT64
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Bool& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID


/* Class Uint8
* 
*/
#define DEFINE_TYPE Uint8
#define DEFINE_TYPEID U8
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Bool& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID

/* Class Uint16
* 
*/
#define DEFINE_TYPE Uint16
#define DEFINE_TYPEID U16
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Bool& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID

/* Class Uint32
* 
*/
#define DEFINE_TYPE Uint32
#define DEFINE_TYPEID U32
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Bool& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID

/* Class Uint64
* 
*/
#define DEFINE_TYPE Uint64
#define DEFINE_TYPEID U64
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Bool& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID


/* Class Bool
* 
*/
#define DEFINE_TYPE Bool
#define DEFINE_TYPEID BOOL
DEFINE_TYPE::DEFINE_TYPE(const Float32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Float64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Int64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint8& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint16& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint32& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
DEFINE_TYPE::DEFINE_TYPE(const Uint64& value)
    : Type(DEFINE_TYPEID)
{
    _data = value.data();
}
#undef DEFINE_TYPE
#undef DEFINE_TYPEID



// 输出重载符
std::ostream& operator<<(std::ostream& out, const Float32& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Float64& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Int8& value)
{
    out << (int16)value.data(); // show number, not char
    return out;
}
std::ostream& operator<<(std::ostream& out, const Int16& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Int32& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Int64& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Uint8& value)
{
    out << (u16)value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Uint16& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Uint32& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Uint64& value)
{
    out << value.data();
    return out;
}
std::ostream& operator<<(std::ostream& out, const Bool& value)
{
    out << (value.data() ? "true" : "false"); // show string
    return out;
}
} // namespace SIMI
