#include "packet.h"


Packet::Packet(){}

Packet::Packet(int x, int y, int force){
    last_time = glfwGetTime();
    energy = force;
    delay = 0;
    this->x = x;
    this->y = y;
    update_packet();
}

void Packet::update_packet(){
    delay += glfwGetTime() - last_time;
    last_time = glfwGetTime();

    // printf("%d", delay);

    // double r = delay * DELAY_TO_R; 
    // double e_diff = delay * DELAY_TO_E;
    // if (energy > 0){
    //     energy -= e_diff;
    // }
    // else {
    //     energy = 0;
    // }

    // (energy, r, l)
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j < STRIP_LENGTH; j++){
            float d = sqrt(pow(i-x, 2) + pow(j-y, 2));
            /* 当d==r的时候取得最大值，自变量是d */
            point_height[i][j] = 0.1 * sin(d/40 * 2/PI);
            // printf("%f\n", point_height[i][j]);
        }
    }
}

float Packet::get_x_y_height(int x, int y){
    // printf("point_height:%f\n", point_height[x][y]);
    return point_height[x][y];
}

PacketManager::PacketManager(){
    clear_height();
    packet_num = 0;
}

/* 将所有波包的高度之和清空为0，方便重新计算 */
void PacketManager::clear_height(){
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j <STRIP_LENGTH; j++){
            point_height[i][j] = 0;
        }
    }
}

/* x, y 指水面的x,y坐标（在水面正上方看下去）， force：波包的力度，0-100 */
void PacketManager::add_packet(int x, int y, int force=50){
    my_packet[packet_num] = Packet(x, y, force);
    packet_num++;

}
/* 每一个时刻都需要更新波包的状态 */
void PacketManager::update_all_packet(){
    for (int i = 0; i < packet_num; i++){
        my_packet[i].update_packet();
    }
}
/* 计算波包高度的总和 */
void PacketManager::calculate_all_packet_height(){
    clear_height();
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j < STRIP_LENGTH; j++){
            for (int k = 0; k < packet_num; k++){
                // printf("get_x_y_h:%f\n", my_packet[k].get_x_y_height(i, j));
                point_height[i][j] += my_packet[k].get_x_y_height(i, j);
            }
            // printf("point_height:%f\n", point_height[i][j]);
        }
    }
}
/* TODO: 每一章都要调用 */
void PacketManager::update_data(){
    update_all_packet();
    calculate_all_packet_height();
}
/* 得到波包总和中，(x,y)对应的波包的高度 */
float PacketManager::get_x_y_height(int x, int y){
    return point_height[x][y];
}
