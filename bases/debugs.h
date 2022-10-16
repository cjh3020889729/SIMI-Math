#ifndef __SIMI_DEBUGS_BASE__
#define __SIMI_DEBUGS_BASE__

#include "basetype.h"
#include <string.h>

namespace SIMI {

__STATIC_DATA__ u64 _error_msg_count = 0;
__STATIC_DATA__ u64 _assert_msg_count = 0;
__STATIC_DATA__ u64 _warning_msg_count = 0;
__STATIC_DATA__ char _debug_temp[1000];

#define _ERROR_QUIT(error_info_str, class_desc) \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, ("In File:" __FILE__ ", at Line: %d of Function: %s::%s\n"), __LINE__, class_desc, __FUNCTION__); \
        int _debug_str_len = strlen(_debug_temp); \
        int print_len = _debug_str_len; \
        int _debug_str_print_times = _debug_str_len / print_len; \
        for(int i = 0; i < print_len; i++) { \
            putchar('-');    \
        } \
        putchar('\n'); \
        printf("Error-%lu Exit:\n", _error_msg_count); \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % print_len) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, "Error-%lu Descrip:\n\t%s\n", _error_msg_count, error_info_str); \
        _debug_str_len = strlen(_debug_temp); \
        _debug_str_print_times = _debug_str_len / print_len; \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % (print_len+8)) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        for(int i = 0; i < print_len; i++) { \
            putchar('-');    \
        } \
        fflush(stdout);\
        _error_msg_count += 1; \
        exit(1);
// 类异常
#define CLASS_ERROR_QUIT(error_info_str, class_desc) _ERROR_QUIT(error_info_str, class_desc)
// 矩阵算法族异常
#define MATRIX_ERROR_QUIT(error_info_str) _ERROR_QUIT(error_info_str, "SIMI::MATRIX")
// 常用方法异常
#define UTILS_ERROR_QUIT(error_info_str) _ERROR_QUIT(error_info_str, "SIMI::UTILS")
// 解算方法族警告
#define SOLVES_ERROR_QUIT(error_info_str) _ERROR_QUIT(error_info_str, "SIMI::SOLVES")


// 断言退出
// static int _assert_state = 0;
#define _ASSERT_QUIT(assert_expr, class_desc) \
    if(!assert_expr) { \
        if(class_desc) { \
            memset(_debug_temp, 0, 1000); \
            sprintf(_debug_temp, ("In File:" __FILE__ ", at Line: %d of Function: %s::%s\n"), __LINE__, class_desc, __FUNCTION__); \
            int _debug_str_len = strlen(_debug_temp); \
            int print_len = _debug_str_len; \
            int _debug_str_print_times = _debug_str_len / print_len; \
            for(int i = 0; i < print_len; i++) { \
                putchar('-');    \
            } \
            putchar('\n'); \
            printf("Assert-%lu Exit:\n", _assert_msg_count); \
            for(int i = 0; i < _debug_str_len; i++) {   \
                if(((i+1) % print_len) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
                else putchar(_debug_temp[i]); \
            } \
            memset(_debug_temp, 0, 1000); \
            sprintf(_debug_temp, ("Assert-%lu Descrip:\n\t" TOSTR(assert_expr) "\n"), _assert_msg_count); \
            _debug_str_len = strlen(_debug_temp); \
            _debug_str_print_times = _debug_str_len / print_len; \
            for(int i = 0; i < _debug_str_len; i++) {   \
                if(((i+1) % (print_len+8)) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
                else putchar(_debug_temp[i]); \
            } \
            for(int i = 0; i < print_len; i++) { \
                putchar('-');    \
            } \
            putchar('\n'); \
        }\
        fflush(stdout);\
        _assert_msg_count += 1; \
        exit(1); \
    }
// 类断言
#define CLASS_ASSERT_QUIT(assert_expr, class_desc) _ASSERT_QUIT(assert_expr, class_desc)
// 矩阵算法族断言
#define MATRIX_ASSERT_QUIT(assert_expr) _ASSERT_QUIT(assert_expr, "SIMI::MATRIX")
// 常用方法族断言
#define UTILS_ASSERT_QUIT(assert_expr) _ASSERT_QUIT(assert_expr, "SIMI::UTILS")
// 解算方法族断言
#define SOLVES_ASSERT_QUIT(assert_expr) _ASSERT_QUIT(assert_expr, "SIMI::SOLVES")

// 无参数展示警告实现
#define _WARNING_NO_PARAMS(warning_str, class_desc) \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, ("In File:" __FILE__ ", at Line: %d of Function: %s::%s\n"), __LINE__, class_desc, __FUNCTION__); \
        int _debug_str_len = strlen(_debug_temp); \
        int print_len = _debug_str_len; \
        int _debug_str_print_times = _debug_str_len / print_len; \
        printf("Warning-%lu Location:\n", _warning_msg_count); \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % print_len) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, "Warning-%lu Info:\n\t%s\n", _warning_msg_count, warning_str); \
        _debug_str_len = strlen(_debug_temp); \
        _debug_str_print_times = _debug_str_len / print_len; \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % (print_len+8)) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        fflush(stdout); \
        _warning_msg_count += 1;
// 类警告
#define CLASS_WARNING_NO_PARAMS(warning_str, class_desc) _WARNING_NO_PARAMS(warning_str, class_desc)
// 矩阵算法族警告
#define MATRIX_WARNING_NO_PARAMS(warning_str) _WARNING_NO_PARAMS(warning_str, "SIMI::MATRIX")
// 常用方法警告
#define UTILS_WARNING_NO_PARAMS(warning_str) _WARNING_NO_PARAMS(warning_str, "SIMI::UTILS")
// 解算方法族警告
#define SOLVES_WARNING_NO_PARAMS(warning_str) _WARNING_NO_PARAMS(warning_str, "SIMI::SOLVES")


// 单参数展示警告实现 -- 参数为基本类型参数，对应格式修饰符需包含在warning_str中
#define _WARNING_1_PARAMS(warning_str, class_desc, param1) \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, ("In File:" __FILE__ ", at Line: %d of Function: %s::%s\n"), __LINE__, class_desc, __FUNCTION__); \
        int _debug_str_len = strlen(_debug_temp); \
        int print_len = _debug_str_len; \
        int _debug_str_print_times = _debug_str_len / print_len; \
        printf("Warning-%lu Location:\n", _warning_msg_count); \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % print_len) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, "Warning-%lu Info:\n\t%", _warning_msg_count); \
        _debug_str_len = strlen(_debug_temp); \
        _debug_str_print_times = _debug_str_len / print_len; \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % (print_len+8)) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        memset(_debug_temp, 0, 1000); \
        sprintf(_debug_temp, warning_str, param1); \
        _debug_str_len = strlen(_debug_temp); \
        _debug_str_print_times = _debug_str_len / print_len; \
        for(int i = 0; i < _debug_str_len; i++) {   \
            if(((i+1) % (print_len)) == 0) { putchar(_debug_temp[i]); if(i!=(_debug_str_len-1)) putchar('\n'); } \
            else putchar(_debug_temp[i]); \
        } \
        putchar('\n'); \
        fflush(stdout); \
        _warning_msg_count += 1;
// 类警告
#define CLASS_WARNING_1_PARAMS(warning_str, class_desc, param1) _WARNING_1_PARAMS(warning_str, class_desc, param1)
// 矩阵算法族警告
#define MATRIX_WARNING_1_PARAMS(warning_str, param1) _WARNING_1_PARAMS(warning_str, "SIMI::MATRIX", param1)
// 常用方法警告
#define UTILS_WARNING_1_PARAMS(warning_str) _WARNING_1_PARAMS(warning_str, "SIMI::UTILS")
// 解算方法族警告
#define SOLVES_WARNING_1_PARAMS(warning_str) _WARNING_1_PARAMS(warning_str, "SIMI::SOLVES")


// 输出重定向
bool restdout2file(const char * file_path);

// 配置输出数据显示精度
bool reset_float_show_precision(const u8 offset_size);

// 标明编译时间
void mark_compare_datetime();


// 数值debug
template<class T1, class T2>
__NORMAL__ void Data_debug_2parms(T1 param1, T2 param2);
template<class T1, class T2, class T3>
__NORMAL__ void Data_debug_2parms_with_result(T1 param1, T2 param2, T3 result);

// 地址debug
template<class T1, class T2>
__NORMAL__ void Address_debug_2parms(T1 param1, T2 param2);
template<class T1, class T2>
__NORMAL__ void Address_debug_2parms_get_result(T1 param1, T2 param2);

}

#endif
