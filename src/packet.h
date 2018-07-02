#ifndef _PACKET_H_
#include <iostream>
// #include <cstdio>
#include <GL/glew.h>
//#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <math.h>
#include "const.h"

class Packet{
public:
    Packet();
    Packet(int x, int y, double force, int type);
    void update_packet();
    float get_x_y_height(int x, int y);
    /* 看这个波包能量是不是0 */
    int is_zero();
private:
    float point_height[STRIP_COUNT+1][STRIP_LENGTH+1];
    double energy;
    double cur_energy;
    double start_time;
    double last_time;
    int x;
    int y;
    double delay;
    int type;
};


class PacketManager{
public:
    PacketManager();

    /* 将所有波包的高度之和清空为0，方便重新计算 */
    void clear_height();

    /* x, y 指水面的x,y坐标（在水面正上方看下去）， force：波包的力度，0-1 */
    void add_packet(int x, int y, double force, int type);
    /* 每一个时刻都需要更新波包的状态 */
    void update_all_packet();
    /* 计算波包高度的总和 */
    void calculate_all_packet_height();
    /* TODO: 每一章都要调用 */
    void update_data();
    /* 得到波包总和中，(x,y)对应的波包的高度 */
    float get_x_y_height(int x, int y);
private:
    float point_height[STRIP_COUNT+1][STRIP_LENGTH+1];
    std::vector<Packet> my_packet;
    int packet_num;
};

#endif // !_PACKET_H_