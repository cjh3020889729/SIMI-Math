#ifndef __SIMI_SOLVES_ALGORITHM_
#define __SIMI_SOLVES_ALGORITHM_

#include "../bases/types.h"
#include "../bases/basetype.h"
#include "../bases/shape.h"
#include "../bases/slice.h"
#include "../bases/stride.h"
#include "../bases/tensor.h"
#include "../bases/debugs.h"
#include "../algorithms/utils.h"
#include "../algorithms/matrix.h"

namespace SIMI {

namespace SOLVES {

// 高斯消元求解线性方程组
template<class T>
Tensor<T> gaussian_elimination_solve(Tensor<T>& tensor);

// LU分解求解线性方程组
template<class T>
Tensor<T> lu_solve(Tensor<T>& l_tensor, Tensor<T>& u_tensor, Tensor<T>& b_tensor)
{
    Tensor<T> _x(b_tensor), _y(b_tensor);
    _x.zeros(), _y.zeros();
    u32 _col_num = l_tensor.get_shape()[0].touint32();
    u32 _row_num = l_tensor.get_shape()[1].touint32();

    // fill y --> Ly=b : forward solve
    for(int i = 0; i < _col_num; i++) {
        T _sum = 0;
        for(int j = 0; j <= i; j++) {
            if(j == i) { // i == j: 对应方程未知元素(每一次求解只含有一个未知数)
                _y.iloc(j, 0) = (b_tensor.at(i, 0) - _sum) / l_tensor.at(i, j);
            } else {
                _sum = _sum + _y.iloc(j, 0) * l_tensor.at(i, j);
            }
        }
    }

    // from y to x: Ux=y : backward solve
    for(int i = _col_num-1; i >= 0; i--) {
        T _sum = 0;
        for(int j = _col_num-1; j >= i; j--) {
            if(j == i) {
                _x.iloc(j, 0) = (_y.at(i, 0) - _sum) / u_tensor.at(i, j);
            } else {
                _sum = _sum + _x.iloc(j, 0) * u_tensor.at(i, j);
            }
        }
    }

    return _x;
}

// Jacobi迭代求线性方程组: 逆矩阵转换求解(非回代求解)
template<class T>
void jacobi_iterator_solve(const Tensor<T>& d_tensor,
                            const Tensor<T>& l_tensor,
                            const Tensor<T>& u_tensor,
                            Tensor<T>& init_x,
                            const Tensor<T>& b,
                            float64 error_limit=1e-6,
                            u32 max_iters=20,
                            bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    auto d_inverse_tensor(d_tensor);

    if(!(MATRIX::inverse(d_tensor, d_inverse_tensor).tobool())) {
        std::cout << "Matrix get inverse failed.";
        return;
    }

    auto g_tensor = MATRIX::multiply(d_inverse_tensor * -1., MATRIX::add(l_tensor, u_tensor));
    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::multiply(g_tensor, init_x) + MATRIX::multiply(d_inverse_tensor, b);
        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}

// Jacobi迭代求线性方程组: 回代求解
template<class T>
void jacobi_iterator_iterate_solve(const Tensor<T>& d_tensor,
                                    const Tensor<T>& l_tensor,
                                    const Tensor<T>& u_tensor,
                                    Tensor<T>& init_x,
                                    const Tensor<T>& b,
                                    float64 error_limit=1e-6,
                                    u32 max_iters=20,
                                    bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    u32 _rows = d_tensor.get_shape()[0].touint32();
    auto q_tensor(d_tensor);
    auto a_tensor(MATRIX::add(l_tensor, u_tensor) * -1.);

    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::add(MATRIX::multiply(a_tensor, init_x), b); // caculate left result
        for(int j = 0; j < _rows; j++) init_x.iloc(j, 0) = init_x.iloc(j, 0) / q_tensor.at(j, j); // solve right result
        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}

// Gauss-Seidel迭代求线性方程组: 逆矩阵转换求解(非回代求解)
template<class T>
void gauss_seidel_solve(const Tensor<T>& d_tensor,
                        const Tensor<T>& l_tensor,
                        const Tensor<T>& u_tensor,
                        Tensor<T>& init_x,
                        const Tensor<T>& b,
                        float64 error_limit=1e-6,
                        u32 max_iters=20,
                        bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    auto l_add_d_tensor(MATRIX::add(l_tensor, d_tensor));
    auto l_add_d_inverse_tensor(l_tensor);
    if(!(MATRIX::inverse(l_add_d_tensor, l_add_d_inverse_tensor).tobool())) {
        std::cout << "Matrix get inverse failed.";
        return;
    }
    auto g_tensor = MATRIX::multiply(l_add_d_inverse_tensor * -1., u_tensor);
    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::multiply(g_tensor, init_x) + MATRIX::multiply(l_add_d_inverse_tensor, b);
        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}

// Gauss-Seidel迭代求线性方程组: 回代求解
template<class T>
void gauss_seidel_iterate_solve(const Tensor<T>& d_tensor,
                        const Tensor<T>& l_tensor,
                        const Tensor<T>& u_tensor,
                        Tensor<T>& init_x,
                        const Tensor<T>& b,
                        float64 error_limit=1e-6,
                        u32 max_iters=20,
                        bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    u32 _rows = d_tensor.get_shape()[0].touint32();
    auto q_tensor(MATRIX::add(d_tensor, l_tensor));
    auto a_tensor(u_tensor * -1.);

    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::add(MATRIX::multiply(a_tensor, init_x), b); // caculate left result
        for(int j = 0; j < _rows; j++) {
            T _sum = init_x.at(j, 0);
            for(int k = 0; k <= j; k++) {
                if(j == k) init_x.iloc(j, 0) = _sum / q_tensor.at(j, k);
                else _sum = _sum - init_x.at(k, 0) * q_tensor.at(j, k);
            }
        } // solve init x

        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}


// SOR连续超松弛迭代求线性方程组: 逆矩阵转换求解(非回代求解)
template<class T>
void sor_solve(const Tensor<T>& d_tensor,
                const Tensor<T>& l_tensor,
                const Tensor<T>& u_tensor,
                Tensor<T>& init_x,
                const Tensor<T>& b,
                float64 w=1.,
                float64 error_limit=1e-6,
                u32 max_iters=20,
                bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    
    auto d_add_wl_tensor(MATRIX::add(d_tensor, l_tensor * w));
    auto q_tensor(d_add_wl_tensor * (1./w));
    auto q_inverse_tensor(l_tensor);
    if(!(MATRIX::inverse(q_tensor, q_inverse_tensor).tobool())) {
        std::cout << "Matrix get inverse failed.";
        return;
    }
    auto d_add_wl_inverse_tensor(d_tensor);
    if(!(MATRIX::inverse(d_add_wl_tensor, d_add_wl_inverse_tensor).tobool())) {
        std::cout << "Matrix get inverse failed.";
        return;
    }
    auto g_tensor = MATRIX::multiply(d_add_wl_inverse_tensor, MATRIX::sub(d_tensor * (1. - w), u_tensor * w));
    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::multiply(g_tensor, init_x) + MATRIX::multiply(q_inverse_tensor, b);
        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}

// SOR连续超松弛迭代求线性方程组: 回代求解
template<class T>
void sor_iterate_solve(const Tensor<T>& d_tensor,
                const Tensor<T>& l_tensor,
                const Tensor<T>& u_tensor,
                Tensor<T>& init_x,
                const Tensor<T>& b,
                float64 w=1.,
                float64 error_limit=1e-6,
                u32 max_iters=20,
                bool verbose=false)
{
    UTILS_ASSERT_QUIT(d_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(d_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(d_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(u_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(u_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(u_tensor.get_shape()[0] == d_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(init_x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(init_x.ndims()==2);
    UTILS_ASSERT_QUIT(init_x.get_shape()[0] == d_tensor.get_shape()[1] && init_x.get_shape()[0] == 1);

    auto last_init_x(init_x);
    u32 _rows = d_tensor.get_shape()[0].touint32();
    auto q_tensor( MATRIX::add( d_tensor, l_tensor * w ) * ( 1./w ) );
    auto a_tensor( ( d_tensor * ( (1. - w) / w ) + u_tensor * -1. ) );

    if(verbose) std::cout << "init_x:\n" << init_x;
    for(int i = 0; i < max_iters; i++) {
        init_x = MATRIX::add(MATRIX::multiply(a_tensor, init_x), b); // caculate left result
        for(int j = 0; j < _rows; j++) {
            T _sum = init_x.at(j, 0);
            for(int k = 0; k <= j; k++) {
                if(j == k) init_x.iloc(j, 0) = _sum / q_tensor.at(j, k);
                else _sum = _sum - init_x.at(k, 0) * q_tensor.at(j, k);
            }
        } // solve init x

        if(verbose) std::cout << "Iter-" << i << "-x:\n" << init_x;
        if(verbose) std::cout << "sum: " << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64() << std::endl;
        if(fabs(UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x)).tofloat64()) < error_limit) {
            if(verbose) std::cout << "End iterator at iter-" << i
                                  << ", the value of last x changed(sumed) is"
                                  << UTILS::matrix_sum(MATRIX::sub(init_x, last_init_x))
                                  << " < " << error_limit << ".\n";
            break;
        }
        last_init_x = init_x;
    }
}

// cholesky solve
template<class T>
void cholesky_split_solve(const Tensor<T>& l_tensor,
                          const Tensor<T>& b_tensor,
                          Tensor<T>& x)
{
    UTILS_ASSERT_QUIT(l_tensor.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(l_tensor.ndims()==2);
    UTILS_ASSERT_QUIT(l_tensor.get_shape()[0] == l_tensor.get_shape()[1]);
    UTILS_ASSERT_QUIT(x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(x.ndims()==2);
    UTILS_ASSERT_QUIT(x.get_shape()[0] == l_tensor.get_shape()[1] && x.get_shape()[0] == 1);
    
    u32 _col_num = l_tensor.get_shape()[0].touint32();
    u32 _row_num = l_tensor.get_shape()[1].touint32();
    Tensor<T> _y(x);
    Tensor<T> lt_tensor(MATRIX::transpose(l_tensor));
    _y.zeros();
    // solve y
    for(int i = 0; i < _col_num; i++) {
        T _sum = 0;
        for(int j = 0; j <= i; j++) {
            if(j == i) { // i == j: 对应方程未知元素(每一次求解只含有一个未知数)
                _y.iloc(j, 0) = (b_tensor.at(i, 0) - _sum) / l_tensor.at(i, j);
            } else {
                _sum = _sum + _y.iloc(j, 0) * l_tensor.at(i, j);
            }
        }
    }

    // from y to x: Ux=y : backward solve
    for(int i = _col_num-1; i >= 0; i--) {
        T _sum = 0;
        for(int j = _col_num-1; j >= i; j--) {
            if(j == i) {
                x.iloc(j, 0) = (_y.at(i, 0) - _sum) / lt_tensor.at(i, j);
            } else {
                _sum = _sum + x.iloc(j, 0) * lt_tensor.at(i, j);
            }
        }
    }

}


// gradient_descent_solve
template<class T>
void gradient_descent_solve(const Tensor<T>& a,
                            const Tensor<T>& b,
                            Tensor<T>& x,
                            u32 iter_max=50,
                            float64 error_limit=1e-7)
{
    MATRIX_ASSERT_QUIT(a.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a.ndims() == 2));
    MATRIX_ASSERT_QUIT((a.get_shape()[0] == a.get_shape()[1]));
    UTILS_ASSERT_QUIT(x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(x.ndims()==2);
    UTILS_ASSERT_QUIT(x.get_shape()[0] == a.get_shape()[1] && x.get_shape()[0] == 1);

    Tensor<T> v = MATRIX::sub( b, MATRIX::multiply(a, x) );
    Tensor<T> w;
    T t;
    for(int i = 0; i < iter_max; i++) {
        w = MATRIX::multiply(a, v);
        t = MATRIX::multiply( MATRIX::transpose(v), v ).at(0, 0) / \
            MATRIX::multiply( MATRIX::transpose(v), w ).at(0, 0);
        x = MATRIX::add( x, v * t );
        v = MATRIX::sub( v, w * t );

        if(MATRIX::infinite_norm_for_vector(v) < error_limit) {
            std::cout << "The solve has finished at iter-" << i << std::endl;
            break;
        }
    }
    std::cout << "The End Solve Error(|v|): " << MATRIX::infinite_norm_for_vector(v) << std::endl;
}


// 共轭梯度法
template<class T>
void conjugate_gradient_descent_solve(const Tensor<T>& a,
                                      const Tensor<T>& b,
                                      Tensor<T>& x)
{
    MATRIX_ASSERT_QUIT(a.check_elem_number().tobool());
    MATRIX_ASSERT_QUIT((a.ndims() == 2));
    MATRIX_ASSERT_QUIT((a.get_shape()[0] == a.get_shape()[1]));
    UTILS_ASSERT_QUIT(x.check_elem_number().tobool());
    UTILS_ASSERT_QUIT(x.ndims()==2);
    UTILS_ASSERT_QUIT(x.get_shape()[0] == a.get_shape()[1] && x.get_shape()[0] == 1);

    Tensor<T> v = MATRIX::sub( b, MATRIX::multiply(a, x) );
    Tensor<T> r(v);
    Tensor<T> w;
    T t;
    T s;
    float64 error_limit = 1e-15;
    u32 iter_max = a.get_shape()[0].touint32();
    for(int i = 0; i < iter_max; i++) {
        auto rr0 = MATRIX::multiply( MATRIX::transpose(r), r ).at(0, 0);
        t = rr0 /\
            MATRIX::multiply( MATRIX::multiply( MATRIX::transpose(v), a ), v ).at(0, 0);
        x = MATRIX::add( x, v * t );
        r = MATRIX::sub( r, MATRIX::multiply(a, v) * t );
        s = MATRIX::multiply( MATRIX::transpose(r), r ).at(0, 0) / rr0;
        v = MATRIX::add( r, v * s );

        if(MATRIX::infinite_norm_for_vector(r) <= error_limit) {
            std::cout << "The solve has finished at iter-" << i << std::endl;
            break;
        }
    }
    std::cout << "The End Solve Error(|r|): " << MATRIX::infinite_norm_for_vector(r) << std::endl;
}


// 幂法迭代结果解析
template<class T>
bool power_iterator_result_solve(const Tensor<T>& input_tensor,
                                 u32 enginevalue_count,
                                 Tensor<T>& engine_values,
                                 Tensor<T>& engine_vectors)
{
    switch (enginevalue_count)
    {
    case 1:
        engine_values = Tensor<T>(1, 1);
        engine_vectors = Tensor<T>(input_tensor.get_shape()[0].touint32()-1, 1);
        engine_values.iloc(0, 0) = input_tensor.at(0, 0);
        for(int i = 1; i < input_tensor.get_shape()[0].touint32(); i++) {
            engine_vectors.iloc(i-1, 0) = input_tensor.at(i, 0);
        }
        return true;
    case 2:
        engine_values = Tensor<T>(1, 2);
        engine_vectors = Tensor<T>(input_tensor.get_shape()[0].touint32()-1, 2);
        engine_values.iloc(0, 0) = input_tensor.at(0, 0);
        for(int i = 1; i < input_tensor.get_shape()[0].touint32() / 2; i++) {
            engine_vectors.iloc(i-1, 0) = input_tensor.at(i, 0);
        }
        engine_values.iloc(0, 1) = input_tensor.at(input_tensor.get_shape()[0].touint32() / 2, 0);
        for(int i = 1; i < input_tensor.get_shape()[0].touint32() / 2; i++) {
            engine_vectors.iloc(i-1, 1) = input_tensor.at(i+input_tensor.get_shape()[0].touint32() / 2, 0);
        }
        return true;
    }
    return false;
}


// 反幂法迭代结果解析
template<class T>
bool inverse_power_iterator_result_solve(const Tensor<T>& input_tensor,
                                 u32 enginevalue_count,
                                 Tensor<T>& engine_values,
                                 Tensor<T>& engine_vectors)
{
    return power_iterator_result_solve(
           input_tensor, enginevalue_count,
           engine_values, engine_vectors);
}


// QR求特征值
template<class T>
Tensor<T> QR_solve(const Tensor<T>& input_tensor,
              u32 iter_max,
              Tensor<T>& output_tensor)
{
    Tensor<T> _temp(input_tensor);
    Tensor<T> _r, _q;

    for(int i = 0; i < iter_max; i++) {
        _q = MATRIX::householder_transform(_temp, _r);
        _temp = MATRIX::multiply(_r, _q);
    }

    output_tensor = _r;
    return _q;
}


// 牛顿插值函数计算
// 牛顿插值函数系数求解
template<class T>
bool newton_interpolation_caculate(
    const Tensor<T>& ax,
    const Tensor<T>& x,
    Tensor<T>& output)
{
    u64 elem_num = x.elem_num().touint64();
    u32 n = ax.get_shape()[0].touint32();
    output = x.clone();

    for(int i = 0; i < elem_num; i++) {
        T _temp = ax.at(0, 0);
        for(int j = 1; j < n; j++) {
            _temp = ax.at(j, 0) + _temp * (x.at(i) - ax.at(j, 1));
        }
        output.iloc(i) = _temp;
    }

    return true;
}


// 三次自然插值函数计算
template<class T>
bool three_nature_interpolation_caculate(
    const Tensor<T>& c,
    const Tensor<T>& o,
    const Tensor<T>& delta,
    const Tensor<T>& origin_xy,
    const Tensor<T>& input_x,
    Tensor<T>& output)
{
    u32 input_size = input_x.get_shape()[0].touint32();
    u32 _size = c.get_shape()[0].touint32() - 1;
    Tensor<T> b(_size, 1); // init
    Tensor<T> d(_size, 1);
    output = input_x.clone();

    for(int i = 0; i < _size; i++) {
        b.iloc(i) = delta.at(i)/o.at(i) - (o.at(i)/3.) * (c.at(i) * 2. + c.at(i+1));
        d.iloc(i) = (c.at(i+1) - c.at(i)) / (o.at(i) * 3.);
    } // init

    for(int i = 0; i < input_size; i++) { // caculate
        T _v = input_x.at(i);
        for(int j = 1; j < _size+1; j++) {
            if(_v <= origin_xy.at(j, 0)) { // input_x <= origin_x(区间上界值)
                T _xi = origin_xy.at(j-1, 0);
                T _yi = origin_xy.at(j-1, 1);
                for(int k = 0; k < 4; k++) {
                    switch (k)
                    {
                        case 0:
                            output.iloc(i) = d.at(j-1) * (_v - _xi);
                            break;
                        case 1:
                            output.iloc(i) = (output.at(i) + c.at(j-1)) * (_v - _xi);
                            break;
                        case 2:
                            output.iloc(i) = (output.at(i) + b.at(j-1)) * (_v - _xi);
                            break;
                        case 3:
                            output.iloc(i) = output.at(i) + _yi;
                            break;
                    }
                }
                break;
            }
        }
    } // caculate over

    return true;
}

}

}

#endif
