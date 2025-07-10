#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <entity/Enemy/Enemy.h>
#include <entity/Enemy/SparkEnemy.h>
#include <entity/Enemy/FlyEnemy.h>
#include <entity/Enemy/PlantEnemy.h>
#include <animation/Animation.h>

class EnemyManager {
public:
    EnemyManager();
    void spawnEnemy(const std::string& type, float x, float y); //按类型生成敌人
    std::vector<std::shared_ptr<Enemy>>& getEnemies(){return m_enemies;}
    void addEnemy(SparkEnemy& enemy);
    void updateAll(float deltaTime, Background& bg);
    void updateAnimation(float deltaTime, std::shared_ptr<Enemy>);
    void drawAll(sf::RenderWindow& window);
    void clear();
    void loadTextures(); 
    void initEnemy();

private:
    sf::Texture m_texture;
    sf::Texture m_deathTexture;
    std::unordered_map<std::string, sf::Texture> m_textures; //纹理资源池
    std::vector<std::shared_ptr<Enemy>> m_enemies;

    //eneny动画
    Animation plantEnemyAnimation;
    Animation flyEnemyAnimation;
    Animation sparkEnemyAnimation;
    Animation enemyDeadAnimation;
};

#endif