#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

// 动画相关常量
namespace AnimationFrame {
    const int frameWidth = 25;   // 单帧宽度
    const int frameHeight = 20;  // 单帧高度
    const int startX = 2;        // 起始帧左上角X坐标
    const int startY = 98;       // 起始帧左上角Y坐标
    const int frameCount = 10;   // 动画总帧数
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
