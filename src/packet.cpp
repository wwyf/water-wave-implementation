#include "packet.h"

/* 随着x变,越靠近boundary,越小，大于boundary后，值为0 */
double decrease_function(double x, double boundary){
    if (x > boundary){
        return 0;
    }
    else {
        return (boundary - x)/boundary;
    }
}

// 波包上的每一点的高度计算的关键函数
// 一个二维的波，计算波包中横坐标为x对应的波的高度
// start为波包开始的地方，end为波包结束的地方
double wave_packet_function(double start, double end, double x, double p){
    if (x < start){
        return 0;
    }
    else if (x > end ){
        return 0;
    }
    else {
        return sin(PI * (x-start)/(end - start));
    }
}


double wave_packet_function2(double start, double end, double x, double p){
    if (x < start){
        return 0;
    }
    else if (x > end ){
        return 0;
    }
    else {
        return -sin(PI * (x-start)/(end - start));
    }
}

Packet::Packet(){}

Packet::Packet(int x, int y, double force, int type){
    start_time = glfwGetTime();
    last_time = glfwGetTime();
    cur_energy = force;
    energy = force;
    printf("this->energy:%f\n", this->energy);
    delay = 0;
    this->x = x;
    this->y = y;
    this->type = type;
    update_packet();
}

void Packet::update_packet(){

    // /*******************************************
    // 一种波的渲染方式
    // for (int i = 0; i < STRIP_COUNT; i++){
    //     for (int j = 0; j < STRIP_LENGTH; j++){
    //         float packet_range = 5;
    //         float d = sqrt(pow(i-x, 2) + pow(j-y, 2));
    //         //  当d==r的时候取得最大值，自变量是d 
    //         if ( d > packet_range){
    //             point_height[i][j] = 0;
    //         }
    //         else {
    //             point_height[i][j] = 0.2 * sin(PI * d/packet_range);
    //         }
    //         // printf("%f\n", point_height[i][j]);
    //     }
    // }
    // *******************************************/

    //具备能量衰减的渲染方式

    delay = glfwGetTime() - start_time;
    last_time = glfwGetTime();
    double max_delay = 5;

    // 根据波的持续时间，计算当前波的能量大小还有半径
    // 波的能量就是三角函数的A
    // 半径就是后期传播的波的范围的一半


    double cur_r = 0.3 - 0.3 * decrease_function(delay,max_delay); 
    double e_fraction = decrease_function(delay, max_delay);

    cur_energy = this->energy * e_fraction;

    // printf("energy:%f\n", energy);
    // printf("delay:%f\n", delay);
    // printf("cur_r:%f\n", cur_r);
    // printf("cur_energy:%f\n", cur_energy);

    // 根据波的能量大小还有半径，计算当前波的形状
    // cur_energy, cur_r
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j < STRIP_LENGTH; j++){
            float one_range = DIS_TO_COORDINATE * (cur_r);
            float packet_range = 2 * one_range;
            float d = sqrt(pow(i-x, 2) + pow(j-y, 2));
            if (this->type == 1){
                point_height[i][j] = cur_energy * wave_packet_function(one_range, 3 * one_range, d, packet_range);
            }
            else if (this->type == 2){
                point_height[i][j] = cur_energy * wave_packet_function2(one_range, 3 * one_range, d, packet_range);
            }
        }
    }


    // (energy, r, l)

}

float Packet::get_x_y_height(int x, int y){
    // printf("point_height:%f\n", point_height[x][y]);
    return point_height[x][y];
}

int Packet::is_zero(){
    return cur_energy == 0;
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
void PacketManager::add_packet(int x, int y, double force, int type){
    my_packet.push_back(Packet(x, y, force, type));
    packet_num++;
}
/* 每一个时刻都需要更新波包的状态 */
void PacketManager::update_all_packet(){
    std::vector<Packet>::iterator it;
    for (it = my_packet.begin(); it != my_packet.end(); ){
        if (it->is_zero()){
            it = my_packet.erase(it);
            packet_num--;
        }
        else{
            it->update_packet();
            it++;
        }
    }
}
/* 计算波包高度的总和 */
void PacketManager::calculate_all_packet_height(){
    clear_height();
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j < STRIP_LENGTH; j++){
            for (std::vector<Packet>::iterator it = my_packet.begin(); it != my_packet.end(); it++){
                point_height[i][j] += it->get_x_y_height(i, j);
            }
        }
    }
}
/* TODO: 每一章都要调用 */
void PacketManager::update_data(){
    update_all_packet();
    calculate_all_packet_height();
    printf("1packet number: %lu\n", my_packet.size());
    printf("2packet number: %d\n", packet_num);
}
/* 得到波包总和中，(x,y)对应的波包的高度 */
float PacketManager::get_x_y_height(int x, int y){
    return point_height[x][y];
}


    delay = glfwGetTime() - start_time;
    last_time = glfwGetTime();
    double max_delay = 5;
    double cur_r = 0.3 - 0.3 * decrease_function(delay,max_delay); 
    double e_fraction = decrease_function(delay, max_delay);
    cur_energy = this->energy * e_fraction;
    // 根据波的能量大小还有半径，计算当前波的形状
    for (int i = 0; i < STRIP_COUNT; i++){
        for (int j = 0; j < STRIP_LENGTH; j++){
            float one_range = DIS_TO_COORDINATE * (cur_r);
            float packet_range = 2 * one_range;
            float d = sqrt(pow(i-x, 2) + pow(j-y, 2));
            point_height[i][j] = cur_energy * wave_packet_function(one_range, 3 * one_range, d, packet_range);
        }
    }
