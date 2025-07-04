#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

// 动画相关常量
namespace AnimationFrame {
    const sf::IntRect standAnimationRect = sf::IntRect(4,5,22,18);
    const sf::IntRect walkAnimationRect = sf::IntRect(2,98,25,20);
    const sf::IntRect jumpAnimationRect = sf::IntRect(5,73,20,20);
    const sf::IntRect fallAnimationRect = sf::IntRect(180,73,20,20);
    //kirby起飞动画（按下x触发）
    const std::vector<sf::IntRect> flyPrepareAnimationRect = {
        sf::IntRect(4,205,25,26),sf::IntRect(33,205,25,26),
        sf::IntRect(62,205,25,26),sf::IntRect(91,205,27,26),
        sf::IntRect(121,205,27,26),sf::IntRect(152,205,25,26)
    };
    const std::vector<sf::IntRect> flyingAnimationRect = {
        sf::IntRect(62,205,25,26),sf::IntRect(91,205,27,26),
        sf::IntRect(121,205,27,26),sf::IntRect(152,205,25,26)
    };
    //kirby攻击动画
    const std::vector<sf::IntRect> attackAnimationRect = {
        sf::IntRect(5,1898,21,19),sf::IntRect(31,1896,23,21),
        sf::IntRect(59,1896,22,21),sf::IntRect(86,1899,23,18),
        sf::IntRect(114,1902,24,15),sf::IntRect(143,1900,20,17)
    };
    //kirby死亡动画
    const std::vector<sf::IntRect> deathAnimationRect = {
        sf::IntRect(4,2520,21,17),sf::IntRect(29,2520,21,17),
        sf::IntRect(54,2517,21,20),sf::IntRect(79,2520,21,17),
        sf::IntRect(104,2520,20,17),sf::IntRect(128,2517,16,20),
        sf::IntRect(1,1,1,1)
    };
    //sparkEnemy动画参数
    const std::vector<sf::IntRect> sparkEnemyAnimationRects = {
        sf::IntRect(0,3,21,18),sf::IntRect(25,3,20,18),
        sf::IntRect(51,3,24,18),sf::IntRect(77,3,23,18),
        sf::IntRect(103,5,23,16),sf::IntRect(128,5,23,15),
        sf::IntRect(155,3,19,18),sf::IntRect(177,3,19,18)
    };
    //敌人死亡动画
    const std::vector<sf::IntRect> enemyDeadAnimationRects = {
        sf::IntRect(10,26,49,18),sf::IntRect(75,28,59,43),
        sf::IntRect(156,19,63,64),sf::IntRect(238,19,85,64),
        sf::IntRect(362,33,26,24),sf::IntRect(411,27,32,32),
        sf::IntRect(464,27,33,32),sf::IntRect(1,1,1,1)
    };
}

// 物理相关常量
namespace Physics {
    const float gravity = 0.8f;  // 重力加速度
}

// 地图/场景相关常量
namespace Map {
    const int TILE_WIDTH = 32;   // 草方块宽度
    const int TILE_HEIGHT = 32;  // 草方块高度
    const int row = 2;           // 行数
    const int col = 8;           // 列数
    const int ground_left = 0;   // 地面左像素
    const int ground_top = 194;  // 地面上边界像素
    const int ground_width = 512;// 地面宽度
    const int ground_height = 60; // 地面高度
    const int ground_offsetX = 0; // 地面图片水平偏移量
    const int ground_offsetY = 56; // 地面图片竖直偏移量
    const int ground_split_left = 10; // 地面图片切割左像素
    const int ground_split_top = 12; // 地面图片切割右像素
    const int ground_split_width = 512; // 地面图片切割宽度
    const int ground_split_height = 212; // 地面图片切割高度
}

// 障碍物相关常量
namespace Obstacle {
    const sf::FloatRect barrier_1 = sf::FloatRect(325,120+Map::ground_offsetY,65,35);
}

// 游戏机制相关常量
// namespace GameMechanics {
//     const qreal maxFlyHeight = 100;  // 最大飞行高度
//     const qreal scale = 1.5;         // 默认缩放比例
// }

#endif
