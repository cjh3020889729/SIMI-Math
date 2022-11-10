#include <iostream>
#include <cmath>

// 求取面积
// A       B
// _ _ _ _ _ 
//|         |
//|         |
//|         |
//|_ _ _ _ _|
// C       D
float caculate_by_2_2_area(
    int point_a[2], int point_b[2],
    int point_c[2], int point_d[2])
{
    float _area = 0;

    _area += point_a[0] * point_c[1] - point_a[1] * point_c[0]; // x_a * y_c - y_a * x_c
    _area += point_c[0] * point_d[1] - point_c[1] * point_d[0]; // x_c * y_d - y_c * x_d
    _area += point_d[0] * point_b[1] - point_d[1] * point_b[0]; // x_d * y_b - y_d * x_b
    _area += point_b[0] * point_a[1] - point_b[1] * point_a[0]; // x_d * y_b - y_d * x_b
    _area /= 2.; // total area

    return _area;
}

void print_2(int point[2])
{
    std::cout << "Piont: [";
    for(int i = 0; i < 2; i++) {
        if(i == 1) {
            std::cout << point[i] << "]\n";
        } else {
            std::cout << point[i] << ",";
        }
    }
}

float caculate_by_2_2_kernel(
    unsigned int img[][4], unsigned int w, unsigned int h,
    unsigned int backgroud_deep)
{
    float _sum = 0; // 总有效深度值
    float _item_sum = 0; // 每次遍历的有效深度值
    unsigned int* _row1;
    unsigned int* _row2;
    unsigned int _max;
    unsigned int _min;
    bool _h_leave_flag = false; // 行遍历存在未处理行
    bool _w_leave_flag = false; // 列遍历存在未处理列
    for(int i = 0; i < h; i+=2) {
        // 行只要最后遍历出现未处理，则记录一次即可，后续统一处理
        if( (i + 1) == h && _h_leave_flag == false ) { _h_leave_flag = true; break; }
        _row1 = img[i];
        _row2 = img[i+1];
        for(int j = 0; j < w; j+=2) {
            // 列只要出现一次未处理，则记录一次即可，后续统一处理
            if( (j + 1) == w && _w_leave_flag == false ) { _w_leave_flag = true; break; }
            _max = std::max<unsigned int>( std::max<unsigned int>(_row1[j], _row2[j]), \
                                           std::max<unsigned int>(_row1[j+1], _row2[j+1]) );
            _min = std::min<unsigned int>( std::min<unsigned int>(_row1[j], _row2[j]), \
                                           std::min<unsigned int>(_row1[j+1], _row2[j+1]) );
            _item_sum = _row1[j] + _row2[j] + _row1[j+1] + _row2[j+1] - _min - _max; // 剩余2个像素的有效高度
            _item_sum /= 2.; // 平均像素高度
            _item_sum -= backgroud_deep; // 物体单像素平均有效深度
            if(_item_sum <= 0) _item_sum = 0; // 四个像素总有效深度
            else _item_sum *= 4; // 四个像素总有效深度
            _sum += _item_sum; // 累加2x2像素区域的有效深度
        }
    }

    // 如果可以容忍这个误差可以不计算这部分
    if(_h_leave_flag == true) { // 行未处理
        if(_w_leave_flag == true) { // 列未处理
            for(int i = 0; i < h-1; i++) { // 处理行中未处理的列
                _item_sum = img[i][w-1] - backgroud_deep;
                if(_item_sum > 0) {
                    _sum += _item_sum;
                }
            }
            for(int j = 0; j < w; j++) { // 未处理行中所有的列
                _item_sum = img[h-1][j] - backgroud_deep;
                if(_item_sum > 0) {
                    _sum += _item_sum;
                }
            }
        } else {
            for(int j = 0; j < w; j++) { // 未处理行中所有的列
                _item_sum = img[h-1][j] - backgroud_deep;
                if(_item_sum > 0) {
                    _sum += _item_sum;
                }
            }
        }
    } else {
        if(_w_leave_flag == true) { // 列未处理
            for(int i = 0; i < h-1; i++) { // 处理行中未处理的列
                _item_sum = img[i][w-1] - backgroud_deep;
                if(_item_sum > 0) {
                    _sum += _item_sum;
                }
            }
        }
    }

    return _sum;    
}

void print_4x4(unsigned int img[][4]) {
    std::cout << "Data:\n[";
    for(int i = 0; i < 4; i++) {
        std::cout << "[";
        for(int j = 0; j < 4; j++) {
            if(j == 3) {
                std::cout << img[i][j] << "]";
            } else {
                std::cout << img[i][j] << ",";
            }
        }
        if(i == 3) {
            std::cout << "]\n";
        } else {
            std::cout << ",\n";
        }
    }
}



int main()
{
    unsigned int backgroud_deep = 1000;
    unsigned int img[4][4] = {
        {1200, 980, 1140, 0},
        {1080, 1140, 1310, 990},
        {800, 900, 1200, 0},
        {900, 1000, 1100, 1080}
    };

    print_4x4(img);
    std::cout << "V caculate result: " << caculate_by_2_2_kernel(img, 4, 4, backgroud_deep) << std::endl;

    int point_a[2] = {1, 0};
    int point_b[2] = {2, 0};
    int point_c[2] = {1, -1};
    int point_d[2] = {2, -1};

    print_2(point_a);
    print_2(point_b);
    print_2(point_c);
    print_2(point_d);
    std::cout << "S caculate result: " << caculate_by_2_2_area(point_a, point_b, point_c, point_d) << std::endl;

    return 0;
}