#include "FlyEnemy.h"
#include <iostream>

void FlyEnemy::update(float deltaTime, Background& bg){
    //死亡检测
    if(isDying()){
        return; //跳过其他逻辑
    }
    //碰撞检测
    checkCollisions(bg);
    //被吞噬时速度方向不变
    //每过一秒钟反转一次运动方向
    if(!m_isBeingDevoured){
        elapsedTime += deltaTime;
        if((elapsedTime >= 2.0 || m_isBlock) && isAlive()){
            setSpeed({0,-m_speed.y});
            elapsedTime = 0;
            m_isBlock = false;
        }
    }
    m_sprite.move(0,m_speed.y);
}
