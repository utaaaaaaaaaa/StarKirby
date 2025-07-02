#include "SparkEnemy.h"
#include <iostream>

void SparkEnemy::update(float deltaTime, Background& bg){
    checkCollisions(bg);
    //每过一秒钟反转一次运动方向
    elapsedTime += deltaTime;
    if((elapsedTime >= 1.0 || m_isBlock) && isAlive()){
        setSpeed({-m_speed.x,0});
        if(!m_isBlock)elapsedTime = 0;
        else m_isBlock = false;
    }
    m_sprite.move(m_speed.x,0);
}

void SparkEnemy::takeDamage(int amount){
    m_health -= amount;
}