#include "PlantEnemy.h"
#include <iostream>

void PlantEnemy::update(float deltaTime, Background& bg){
    //死亡检测
    if(isDying()){
        return; //跳过其他逻辑
    }
    //碰撞检测
    checkCollisions(bg);
    // //被吞噬时速度方向不变
    // //每过一秒钟反转一次运动方向
    // if(!m_isBeingDevoured){
    //     elapsedTime += deltaTime;
    //     if((elapsedTime >= 2.0 || m_isBlock) && isAlive()){
    //         setSpeed({-m_speed.x,0});
    //         elapsedTime = 0;
    //         m_isBlock = false;
    //     }
    // }
    // m_sprite.move(m_speed.x,0);
}