#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <entity/Enemy/Enemy.h>
#include <entity/Enemy/SparkEnemy.h>
#include <animation/Animation.h>

class EnemyManager {
public:
    EnemyManager();
    SparkEnemy& getSparkEnemy(){return m_sparkEnemy;};
    std::vector<std::shared_ptr<Enemy>>& getEnemies(){return m_enemies;}
    void addEnemy(SparkEnemy& enemy);
    void updateAll(float deltaTime, Background& bg);
    void drawAll(sf::RenderWindow& window);
    void clear();

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    SparkEnemy m_sparkEnemy;
    std::vector<std::shared_ptr<Enemy>> m_enemies;

    //eneny动画
    Animation sparkEnemyAnimation;
};

#endif