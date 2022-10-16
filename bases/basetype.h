#ifndef __SIMI_BASETYPE_BASE__
#define __SIMI_BASETYPE_BASE__
/*bases/basetypes.h
* define: 重载类型定义
* 
* TODO: 重载友元运算符号，支持左运算
* TODO: 重载Bool类对应的逻辑运算符: &&, ||
* TODO: 重载整型类的位移符号
* TODO: 重载类型转换符号
*/
#include "./types.h"


namespace SIMI {

__NORMAL__ class Float32 : public Type {
private:
    float _data;

public:
    Float32(): _data(0), Type(FLOAT32) {}
    Float32(const float value) : _data(value), Type(FLOAT32) { _data=value; }
    Float32(const Float32& value): Type(FLOAT32) { _data=value.data(); }
    Float32(const Float64& value);
    Float32(const Int8& value);
    Float32(const Int16& value);
    Float32(const Int32& value);
    Float32(const Int64& value);
    Float32(const Uint8& value);
    Float32(const Uint16& value);
    Float32(const Uint32& value);
    Float32(const Uint64& value);
    Float32(const Bool& value);

    float data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    Float32 operator!() const { return Float32(!_data); }

    void set_data(const float value) { _data=value; }
    void operator=(const float right_value) { _data=right_value; }
    Float32 operator+(const float right_value) const { return Float32(_data+right_value); }
    Float32 operator-(const float right_value) const { return Float32(_data-right_value); }
    Float32 operator*(const float right_value) const { return Float32(_data*right_value); }
    Float32 operator/(const float right_value) const { return Float32(_data/right_value); }
    void operator+=(const float right_value) { _data+=right_value; }
    void operator-=(const float right_value) { _data-=right_value; }
    void operator*=(const float right_value) { _data*=right_value; }
    void operator/=(const float right_value) { _data/=right_value; }

    void operator=(const Float32& right_value) { _data=right_value.data(); }
    Float32 operator+(const Float32& right_value) const { return Float32(_data+right_value.data()); }
    Float32 operator-(const Float32& right_value) const { return Float32(_data-right_value.data()); }
    Float32 operator*(const Float32& right_value) const { return Float32(_data*right_value.data()); }
    Float32 operator/(const Float32& right_value) const { return Float32(_data/right_value.data()); }
    void operator+=(const Float32& right_value) { _data+=right_value.data(); }
    void operator-=(const Float32& right_value) { _data-=right_value.data(); }
    void operator*=(const Float32& right_value) { _data*=right_value.data(); }
    void operator/=(const Float32& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const float right_value) const { return _data==right_value; }
    bool operator!=(const float right_value) const { return _data!=right_value; }
    bool operator>(const float right_value) const { return _data>right_value; }
    bool operator<(const float right_value) const { return _data<right_value; }
    bool operator>=(const float right_value) const { return _data>=right_value; }
    bool operator<=(const float right_value) const { return _data<=right_value; }

    bool operator==(const Float32& right_value) const { return _data==right_value.data(); }
    bool operator!=(const Float32& right_value) const { return _data!=right_value.data(); }
    bool operator>(const Float32& right_value) const { return _data>right_value.data(); }
    bool operator<(const Float32& right_value) const { return _data<right_value.data(); }
    bool operator>=(const Float32& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const Float32& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const Float32& value);
};

class Float64 : public Type {
private:
    double _data;

public:
    Float64(): _data(0), Type(FLOAT64) {}
    Float64(const double value): _data(value), Type(FLOAT64) {}
    Float64(const Float64& value): Type(FLOAT64) { _data=value.data(); }
    Float64(const Float32& value);
    Float64(const Int8& value);
    Float64(const Int16& value);
    Float64(const Int32& value);
    Float64(const Int64& value);
    Float64(const Uint8& value);
    Float64(const Uint16& value);
    Float64(const Uint32& value);
    Float64(const Uint64& value);
    Float64(const Bool& value);

    double data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    Float32 operator!() const { return Float32(!_data); }

    void set_data(const double value) { _data=value; }
    void operator=(const double right_value) { _data=right_value; }
    Float64 operator+(const double right_value) const { return Float64(_data+right_value); }
    Float64 operator-(const double right_value) const { return Float64(_data-right_value); }
    Float64 operator*(const double right_value) const { return Float64(_data*right_value); }
    Float64 operator/(const double right_value) const { return Float64(_data/right_value); }
    void operator+=(const double right_value) { _data+=right_value; }
    void operator-=(const double right_value) { _data-=right_value; }
    void operator*=(const double right_value) { _data*=right_value; }
    void operator/=(const double right_value) { _data/=right_value; }

    void operator=(const Float64& right_value) { _data=right_value.data(); }
    Float64 operator+(const Float64& right_value) const { return Float64(_data+right_value.data()); }
    Float64 operator-(const Float64& right_value) const { return Float64(_data-right_value.data()); }
    Float64 operator*(const Float64& right_value) const { return Float64(_data*right_value.data()); }
    Float64 operator/(const Float64& right_value) const { return Float64(_data/right_value.data()); }
    void operator+=(const Float64& right_value) { _data+=right_value.data(); }
    void operator-=(const Float64& right_value) { _data-=right_value.data(); }
    void operator*=(const Float64& right_value) { _data*=right_value.data(); }
    void operator/=(const Float64& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const double right_value) const { return _data==right_value; }
    bool operator!=(const double right_value) const { return _data!=right_value; }
    bool operator>(const double right_value) const { return _data>right_value; }
    bool operator<(const double right_value) const { return _data<right_value; }
    bool operator>=(const double right_value) const { return _data>=right_value; }
    bool operator<=(const double right_value) const { return _data<=right_value; }

    bool operator==(const Float64& right_value) const { return _data==right_value.data(); }
    bool operator!=(const Float64& right_value) const { return _data!=right_value.data(); }
    bool operator>(const Float64& right_value) const { return _data>right_value.data(); }
    bool operator<(const Float64& right_value) const { return _data<right_value.data(); }
    bool operator>=(const Float64& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const Float64& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const Float64& value);
};

class Int8 : public Type {
private:
    int8 _data;

public:
    Int8(): _data(0), Type(INT8) {}
    Int8(const int8 value): _data(value), Type(INT8) {}
    Int8(const Int8& value): Type(INT8) { _data=value.data(); }
    Int8(const Float32& value);
    Int8(const Float64& value);
    Int8(const Int16& value);
    Int8(const Int32& value);
    Int8(const Int64& value);
    Int8(const Uint8& value);
    Int8(const Uint16& value);
    Int8(const Uint32& value);
    Int8(const Uint64& value);
    Int8(const Bool& value);
    
    int8 data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    Int8 operator!() const { return Int8(!_data); }
    Int8 operator~() const { return Int8(~_data); }
    Int8 operator^(const int8 value) const { return Int8(_data ^ value); }
    Int8 operator^(const Int8& right_value) const { return Int8(_data ^ right_value.data()); }

    void set_data(const int8 value) { _data=value; }
    void operator=(const int8 right_value) { _data=right_value; }
    Int8 operator+(const int8 right_value) const { return Int8(_data+right_value); }
    Int8 operator-(const int8 right_value) const { return Int8(_data-right_value); }
    Int8 operator*(const int8 right_value) const { return Int8(_data*right_value); }
    Int8 operator/(const int8 right_value) const { return Int8(_data/right_value); }
    void operator+=(const int8 right_value) { _data+=right_value; }
    void operator-=(const int8 right_value) { _data-=right_value; }
    void operator*=(const int8 right_value) { _data*=right_value; }
    void operator/=(const int8 right_value) { _data/=right_value; }

    void operator=(const Int8& right_value) { _data=right_value.data(); }
    Int8 operator+(const Int8& right_value) const { return Int8(_data+right_value.data()); }
    Int8 operator-(const Int8& right_value) const { return Int8(_data-right_value.data()); }
    Int8 operator*(const Int8& right_value) const { return Int8(_data*right_value.data()); }
    Int8 operator/(const Int8& right_value) const { return Int8(_data/right_value.data()); }
    void operator+=(const Int8& right_value) { _data+=right_value.data(); }
    void operator-=(const Int8& right_value) { _data-=right_value.data(); }
    void operator*=(const Int8& right_value) { _data*=right_value.data(); }
    void operator/=(const Int8& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const int8 right_value) const { return _data==right_value; }
    bool operator!=(const int8 right_value) const { return _data!=right_value; }
    bool operator>(const int8 right_value) const { return _data>right_value; }
    bool operator<(const int8 right_value) const { return _data<right_value; }
    bool operator>=(const int8 right_value) const { return _data>=right_value; }
    bool operator<=(const int8 right_value) const { return _data<=right_value; }

    bool operator==(const Int8& right_value) const { return _data==right_value.data(); }
    bool operator!=(const Int8& right_value) const { return _data!=right_value.data(); }
    bool operator>(const Int8& right_value) const { return _data>right_value.data(); }
    bool operator<(const Int8& right_value) const { return _data<right_value.data(); }
    bool operator>=(const Int8& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const Int8& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const Int8& value);
};

#define DEFINE_TYPE Int16
#define DEFINE_SUBTYPE int16
#define DEFINE_TYPEID INT16
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Int16& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Int32
#define DEFINE_SUBTYPE int32
#define DEFINE_TYPEID INT32
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Int32& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Int64
#define DEFINE_SUBTYPE int64
#define DEFINE_TYPEID INT64
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Int64& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Uint8
#define DEFINE_SUBTYPE u8
#define DEFINE_TYPEID U8
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Uint8& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Uint16
#define DEFINE_SUBTYPE u16
#define DEFINE_TYPEID U16
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Uint16& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Uint32
#define DEFINE_SUBTYPE u32
#define DEFINE_TYPEID U32
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Uint32& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint64& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

// TODO: implement the copy functions
#define DEFINE_TYPE Uint64
#define DEFINE_SUBTYPE u64
#define DEFINE_TYPEID U64
class DEFINE_TYPE : public Type {
private:
    DEFINE_SUBTYPE _data;

public:
    DEFINE_TYPE(): _data(0), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const DEFINE_SUBTYPE value): _data(value), Type(DEFINE_TYPEID) {}
    DEFINE_TYPE(const Uint64& value): Type(DEFINE_TYPEID) { _data=value.data(); }
    DEFINE_TYPE(const Float32& value);
    DEFINE_TYPE(const Float64& value);
    DEFINE_TYPE(const Int8& value);
    DEFINE_TYPE(const Int16& value);
    DEFINE_TYPE(const Int32& value);
    DEFINE_TYPE(const Int64& value);
    DEFINE_TYPE(const Uint8& value);
    DEFINE_TYPE(const Uint16& value);
    DEFINE_TYPE(const Uint32& value);
    DEFINE_TYPE(const Bool& value);
    
    DEFINE_SUBTYPE data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    DEFINE_TYPE operator!() const { return DEFINE_TYPE(!_data); }
    DEFINE_TYPE operator~() const { return DEFINE_TYPE(~_data); }
    DEFINE_TYPE operator^(const DEFINE_SUBTYPE value) const { return DEFINE_TYPE(_data ^ value); }
    DEFINE_TYPE operator^(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data ^ right_value.data()); }

    void set_data(const DEFINE_SUBTYPE value) { _data=value; }
    void operator=(const DEFINE_SUBTYPE right_value) { _data=right_value; }
    DEFINE_TYPE operator+(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data+right_value); }
    DEFINE_TYPE operator-(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data-right_value); }
    DEFINE_TYPE operator*(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data*right_value); }
    DEFINE_TYPE operator/(const DEFINE_SUBTYPE right_value) const { return DEFINE_TYPE(_data/right_value); }
    void operator+=(const DEFINE_SUBTYPE right_value) { _data+=right_value; }
    void operator-=(const DEFINE_SUBTYPE right_value) { _data-=right_value; }
    void operator*=(const DEFINE_SUBTYPE right_value) { _data*=right_value; }
    void operator/=(const DEFINE_SUBTYPE right_value) { _data/=right_value; }

    void operator=(const DEFINE_TYPE& right_value) { _data=right_value.data(); }
    DEFINE_TYPE operator+(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data+right_value.data()); }
    DEFINE_TYPE operator-(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data-right_value.data()); }
    DEFINE_TYPE operator*(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data*right_value.data()); }
    DEFINE_TYPE operator/(const DEFINE_TYPE& right_value) const { return DEFINE_TYPE(_data/right_value.data()); }
    void operator+=(const DEFINE_TYPE& right_value) { _data+=right_value.data(); }
    void operator-=(const DEFINE_TYPE& right_value) { _data-=right_value.data(); }
    void operator*=(const DEFINE_TYPE& right_value) { _data*=right_value.data(); }
    void operator/=(const DEFINE_TYPE& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const DEFINE_SUBTYPE right_value) const { return _data==right_value; }
    bool operator!=(const DEFINE_SUBTYPE right_value) const { return _data!=right_value; }
    bool operator>(const DEFINE_SUBTYPE right_value) const { return _data>right_value; }
    bool operator<(const DEFINE_SUBTYPE right_value) const { return _data<right_value; }
    bool operator>=(const DEFINE_SUBTYPE right_value) const { return _data>=right_value; }
    bool operator<=(const DEFINE_SUBTYPE right_value) const { return _data<=right_value; }

    bool operator==(const DEFINE_TYPE& right_value) const { return _data==right_value.data(); }
    bool operator!=(const DEFINE_TYPE& right_value) const { return _data!=right_value.data(); }
    bool operator>(const DEFINE_TYPE& right_value) const { return _data>right_value.data(); }
    bool operator<(const DEFINE_TYPE& right_value) const { return _data<right_value.data(); }
    bool operator>=(const DEFINE_TYPE& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const DEFINE_TYPE& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const DEFINE_TYPE& value);
};
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE
#undef DEFINE_TYPEID

class Bool : public Type {
private:
    bool _data;

public:
    Bool(): _data(0), Type(BOOL) {}
    Bool(const bool value): _data(value), Type(BOOL) {}
    Bool(const Bool& value): Type(BOOL) { _data=value.data(); }
    Bool(const Float32& value);
    Bool(const Float64& value);
    Bool(const Int8& value);
    Bool(const Int16& value);
    Bool(const Int32& value);
    Bool(const Int64& value);
    Bool(const Uint8& value);
    Bool(const Uint16& value);
    Bool(const Uint32& value);
    Bool(const Uint64& value);
    
    bool data() const { return _data; }
    u8 touint8() const { return _data; }
    u16 touint16() const { return _data; }
    u32 touint32() const { return _data; }
    u64 touint64() const { return _data; }
    int8 toint8() const { return _data; }
    int16 toint16() const { return _data; }
    int32 toint32() const { return _data; }
    int64 toint64() const { return _data; }
    float32 tofloat32() const { return _data; }
    float64 tofloat64() const { return _data; }
    bool tobool() const { return _data; }

    // 值运算符重载: +,-,*,/,*=.etc
    // %, ^, ~ 只对整型有效
    Bool operator!() const { return Bool(!_data); }
    Bool operator~() const { return Bool(~_data); }
    Bool operator^(const bool value) const { return Bool(_data ^ value); }
    Bool operator^(const Bool& right_value) const { return Bool(_data ^ right_value.data()); }

    void set_data(const bool value) { _data=value; }
    void operator=(const bool right_value) { _data=right_value; }
    Bool operator+(const bool right_value) const { return Bool(_data+right_value); }
    Bool operator-(const bool right_value) const { return Bool(_data-right_value); }
    Bool operator*(const bool right_value) const { return Bool(_data*right_value); }
    Bool operator/(const bool right_value) const { return Bool(_data/right_value); }
    void operator+=(const bool right_value) { _data+=right_value; }
    void operator-=(const bool right_value) { _data-=right_value; }
    void operator*=(const bool right_value) { _data*=right_value; }
    void operator/=(const bool right_value) { _data/=right_value; }

    void operator=(const Bool& right_value) { _data=right_value.data(); }
    Bool operator+(const Bool& right_value) const { return Bool(_data+right_value.data()); }
    Bool operator-(const Bool& right_value) const { return Bool(_data-right_value.data()); }
    Bool operator*(const Bool& right_value) const { return Bool(_data*right_value.data()); }
    Bool operator/(const Bool& right_value) const { return Bool(_data/right_value.data()); }
    void operator+=(const Bool& right_value) { _data+=right_value.data(); }
    void operator-=(const Bool& right_value) { _data-=right_value.data(); }
    void operator*=(const Bool& right_value) { _data*=right_value.data(); }
    void operator/=(const Bool& right_value) { _data/=right_value.data(); }

    // 逻辑比较符重载: ==, > , <
    bool operator==(const bool right_value) const { return _data==right_value; }
    bool operator!=(const bool right_value) const { return _data!=right_value; }
    bool operator>(const bool right_value) const { return _data>right_value; }
    bool operator<(const bool right_value) const { return _data<right_value; }
    bool operator>=(const bool right_value) const { return _data>=right_value; }
    bool operator<=(const bool right_value) const { return _data<=right_value; }

    bool operator==(const Bool& right_value) const { return _data==right_value.data(); }
    bool operator!=(const Bool& right_value) const { return _data!=right_value.data(); }
    bool operator>(const Bool& right_value) const { return _data>right_value.data(); }
    bool operator<(const Bool& right_value) const { return _data<right_value.data(); }
    bool operator>=(const Bool& right_value) const { return _data>=right_value.data(); }
    bool operator<=(const Bool& right_value) const { return _data<=right_value.data(); }

    // 输出重载符: <<
    friend std::ostream& operator<<(std::ostream& out, const Bool& value);
};

}

#endif
