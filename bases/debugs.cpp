#include "debugs.h"

namespace SIMI {

bool restdout2file(const char* file_path)
{
    if(freopen(file_path, "w", stdout)) {
        return true;
    } else {
        return false;
    }
}

// 配置输出数据显示精度
bool reset_float_show_precision(const u8 precision_size)
{
    std::cout.precision(precision_size);
    std::cout.flags(std::cout.fixed);
}

// 标明编译时间
void mark_compare_datetime()
{
    std::cout << "The compile data: " << __DATE__ << " - " << __TIME__ << std::endl;
}


#define DEFINE_TYPE u64
#define DEFINE_SUBTYPE u64
// 数值debug
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Data_debug_2parms(DEFINE_SUBTYPE param1, DEFINE_SUBTYPE param2)
{
    std::cout << "\nParams1: " << param1 << "\n";
    std::cout << "Params2: " << param2 << "\n\n";
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Data_debug_2parms_with_result(DEFINE_SUBTYPE param1, DEFINE_SUBTYPE param2, DEFINE_SUBTYPE result)
{
    std::cout << "\nParams1: " << param1 << "\n";
    std::cout << "Params2: " << param2 << "\n";

    std::cout << "Result:\n";
    std::cout << "\t|-- " << result << " --|" << "\n";
}

// 地址debug
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Address_debug_2parms(DEFINE_SUBTYPE param1, DEFINE_SUBTYPE param2)
{
    std::cout << "\nParams1-Address: " << &param1 << "\n";
    std::cout << "Params2-Address: " << &param2 << "\n\n";
}
template<>
__NORMAL__ __TEMPLATE_IMPL__ void Address_debug_2parms_get_result(DEFINE_SUBTYPE param1, DEFINE_SUBTYPE param2)
{
    std::cout << "\nParams1-Address: " << &param1 << "\n";
    std::cout << "Params2-Address: " << &param2 << "\n";

    std::cout << "Result:\n";
    std::cout << "\t|-- Params1-Address == Params2-Address: " << SIMI::Bool(&param1 == &param2) << " --|" << "\n";
}
#undef DEFINE_TYPE
#undef DEFINE_SUBTYPE


}
