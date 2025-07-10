#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

// 动画相关常量
namespace AnimationFrame {
    //==========Normal Kirby====================
    const sf::IntRect standAnimationRect = sf::IntRect(4,5,22,18);
    //kirby行走动画
    const std::vector<sf::IntRect> walkAnimationRect = {
        sf::IntRect(2,99,21,19),sf::IntRect(29,98,22,20),
        sf::IntRect(55,99,21,19),sf::IntRect(80,101,20,17),
        sf::IntRect(106,100,18,18),sf::IntRect(128,99,18,18),
        sf::IntRect(152,98,22,20),sf::IntRect(178,99,21,19),
        sf::IntRect(203,101,20,17),sf::IntRect(227,100,20,17)
    };
    //kirby跳跃动画
    const std::vector<sf::IntRect> jumpAnimationRect = {
        sf::IntRect(4,72,21,21),sf::IntRect(29,73,22,20),
        sf::IntRect(55,74,21,18),sf::IntRect(80,73,21,20),
        sf::IntRect(104,72,21,21),sf::IntRect(129,75,22,18),
        sf::IntRect(155,74,21,19)
    };
    //kirby降落动画
    const std::vector<sf::IntRect> fallAnimationRect = {
        sf::IntRect(180,73,20,20),sf::IntRect(205,73,21,19)
    };
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
    //kirby吞噬动画
    const std::vector<sf::IntRect> devourAnimationRect = {
        sf::IntRect(4,152,23,19),sf::IntRect(31,154,23,17),
        sf::IntRect(58,150,20,21),sf::IntRect(82,148,21,23),
        sf::IntRect(107,146,22,25)
    };
    //kirby吞噬动画粒子
    const std::vector<sf::IntRect> devourParticlesAnimationRect = {
        sf::IntRect(0,0,35,25),sf::IntRect(40,0,38,25),
        sf::IntRect(83,0,38,25),sf::IntRect(130,0,36,25),
    };
    //kirby攻击动画
    const std::vector<sf::IntRect> attackAnimationRect = {
        sf::IntRect(5,1898,21,19),sf::IntRect(31,1896,23,21),
        sf::IntRect(59,1896,22,21),sf::IntRect(86,1899,23,18),
        sf::IntRect(114,1902,24,15),sf::IntRect(143,1900,20,17)
    };
    //kirby飞行模式攻击动画
    const std::vector<sf::IntRect> attackFlyAnimationRect = {
        sf::IntRect(4,265,21,23),sf::IntRect(29,267,20,21),
        sf::IntRect(53,267,21,21),sf::IntRect(78,267,22,21),
    };
    //kirby飞行模式下攻击粒子效果
    const std::vector<sf::IntRect> attackFlyParticlesAnimationRect = {
        sf::IntRect(0,0,6,15),sf::IntRect(0,0,21,15),
        sf::IntRect(0,0,42,15),sf::IntRect(46,0,16,15),
        sf::IntRect(66,0,11,15),sf::IntRect(1,1,1,1)
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
    //flyEnemy动画参数
    const std::vector<sf::IntRect> flyEnemyAnimationRects = {
        sf::IntRect(1,2,20,21),sf::IntRect(27,2,19,21),
        sf::IntRect(51,2,26,21),sf::IntRect(84,2,20,21),
        sf::IntRect(111,2,19,21),sf::IntRect(134,2,23,21),
        sf::IntRect(159,2,22,21)
    };
    //plantEnemy动画参数
    const std::vector<sf::IntRect> plantEnemyAnimationRects = {
        sf::IntRect(2,4,25,21),sf::IntRect(30,6,22,19),
        sf::IntRect(53,7,22,18),sf::IntRect(77,9,22,16),
        sf::IntRect(100,11,23,14),sf::IntRect(123,3,25,22),
        sf::IntRect(149,6,24,19)
    };
    //敌人死亡动画
    const std::vector<sf::IntRect> enemyDeadAnimationRects = {
        sf::IntRect(10,26,49,18),sf::IntRect(75,28,59,43),
        sf::IntRect(156,19,63,64),sf::IntRect(238,19,85,64),
        sf::IntRect(362,33,26,24),sf::IntRect(411,27,32,32),
        sf::IntRect(464,27,33,32),sf::IntRect(1,1,1,1)
    };
    //==================Spark Kirby===========================
    const std::vector<sf::IntRect> standSparkAnimationRect = {
        sf::IntRect(7,6,23,32),sf::IntRect(34,6,23,32),
        sf::IntRect(60,6,23,32),sf::IntRect(86,6,23,32),
    };
    // //kirby行走动画
    const std::vector<sf::IntRect> walkSparkAnimationRect = {
        sf::IntRect(7,298,23,32),sf::IntRect(61,298,23,32),
        sf::IntRect(114,298,23,32),sf::IntRect(168,298,23,32),
        sf::IntRect(221,298,22,32),sf::IntRect(247,298,22,32),
        sf::IntRect(302,298,23,32),sf::IntRect(416,298,25,32),
        sf::IntRect(449,298,22,32),sf::IntRect(525,298,22,32)
    };
    //kirby跳跃动画
    const std::vector<sf::IntRect> jumpSparkAnimationRect = {
        sf::IntRect(7,252,24,28),sf::IntRect(35,252,25,28),
        sf::IntRect(64,252,22,28),sf::IntRect(90,252,22,29),
        sf::IntRect(116,252,23,29),sf::IntRect(143,257,26,28),
        sf::IntRect(174,258,27,25),sf::IntRect(208,253,24,28),
    };
    //kirby降落动画
    const std::vector<sf::IntRect> fallSparkAnimationRect = {
        sf::IntRect(238,245,23,35),sf::IntRect(266,245,22,35)
    };
    //kirby起飞动画（按下x触发）
    const std::vector<sf::IntRect> flyPrepareSparkAnimationRect = {
        sf::IntRect(7,474,25,38),sf::IntRect(95,474,25,38),
        sf::IntRect(124,474,26,38),sf::IntRect(154,474,27,38),
        sf::IntRect(185,474,27,38),sf::IntRect(217,474,25,38),
    };
    const std::vector<sf::IntRect> flyingSparkAnimationRect = {
        sf::IntRect(124,474,26,38),sf::IntRect(154,474,27,38),
        sf::IntRect(185,474,27,38),sf::IntRect(217,474,25,38),
    };
    //kirby攻击动画
    const std::vector<sf::IntRect> attackASparkAnimationRect = {
        sf::IntRect(7,1113,23,35),sf::IntRect(34,1107,65,63),
        sf::IntRect(103,1117,25,31),sf::IntRect(135,1107,59,64),
        sf::IntRect(204,1107,59,64),sf::IntRect(204,1107,59,64),
        sf::IntRect(299,1117,25,31),
    };
    //kirby吞噬动画
    const std::vector<sf::IntRect> devourSparkAnimationRect = {
        sf::IntRect(7,383,23,32),sf::IntRect(34,383,23,32),
        sf::IntRect(63,383,22,32),sf::IntRect(91,383,23,32),
        sf::IntRect(118,383,24,32),
    };
}

//sf::IntRect(,,,),
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
    const int ground_width = 1590;// 地面宽度
    const int ground_height = 60; // 地面高度
    const int ground_offsetX = 0; // 地面图片水平偏移量
    const int ground_offsetY = 56; // 地面图片竖直偏移量
    const int ground_split_left = 10; // 地面图片切割左像素
    const int ground_split_top = 12; // 地面图片切割右像素
    const int ground_split_width = 1590; // 地面图片切割宽度
    const int ground_split_height = 212; // 地面图片切割高度
    const std::vector<sf::FloatRect> groundsRects = {
        sf::FloatRect(0,194,715,60),
        sf::FloatRect(734,116+Map::ground_offsetY,77,60),
        sf::FloatRect(873,120+Map::ground_offsetY,727,90),
    };
}

// 障碍物相关常量
namespace Obstacle {
    const std::vector<sf::FloatRect> barriersRects = {
        sf::FloatRect(325,120+Map::ground_offsetY,65,35),
        sf::FloatRect(580,120+Map::ground_offsetY,25,35),
        sf::FloatRect(714,120+Map::ground_offsetY,37,35),
        sf::FloatRect(810,80+Map::ground_offsetY,65,90),
        sf::FloatRect(1209,64+Map::ground_offsetY,65,90),
    };
}

// 游戏机制相关常量
// namespace GameMechanics {
//     const qreal maxFlyHeight = 100;  // 最大飞行高度
//     const qreal scale = 1.5;         // 默认缩放比例
// }

#endif
