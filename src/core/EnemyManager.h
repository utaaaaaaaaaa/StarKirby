#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <entity/Enemy/Enemy.h>
#include <entity/Enemy/SparkEnemy.h>
#include <animation/Animation.h>

class EnemyManager {
public:
    EnemyManager();
    SparkEnemy& getSparkEnemy();
    void addEnemy(const Enemy& enemy);
    void updateAll(float deltaTime, Background& bg);
    void drawAll(sf::RenderWindow& window);
    void clear();

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    SparkEnemy m_sparkEnemy;

    //eneny动画
    Animation sparkEnemyAnimation;
};

#endif