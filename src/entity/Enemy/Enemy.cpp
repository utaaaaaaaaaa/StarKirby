#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Sprite& sprite, float gravity) 
    : m_sprite(sprite), m_gravity(gravity), temp_enemy(sprite, m_speed) {}

void Enemy::checkCollisions(Background& bg){
    temp_enemy.checkGroundCollision(bg);
    temp_enemy.checkBarrierCollision(bg.getBarrier());
    //将temp_enemy经过碰撞检测后修改的参数赋值给自己
    // std::cout<<m_speed.x<<","<<m_speed.y<<"|";
    if(temp_enemy.getSpeed().x==0){
        m_isBlock = true;
    }
    m_isGround = temp_enemy.getIsGround();
}