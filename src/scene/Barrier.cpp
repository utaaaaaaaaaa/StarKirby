#include "Barrier.h"

Barrier::Barrier(){}

// 返回碰撞方向 (0:无碰撞, 1:下方, 2:左面, 3:上方, 4:右面)
int Barrier::checkCollisionDirection(sf::FloatRect playerRect, sf::Vector2f speed) {
    for(const auto& barrier : barrierRects){
        if (playerRect.intersects(barrier)){
            theOneBarrier = barrier;
            //计算卡比底部和障碍物顶部距离
            float kirbyBottom = playerRect.top + playerRect.height;
            float barrierBottom = barrier.top + barrier.height;
            float kirbyRight = playerRect.left + playerRect.width;
            float barrierRight = barrier.left + barrier.width;
            //如果距离很近且在下落，视为下方碰撞
            if(kirbyBottom-barrier.top <= 6.0 && speed.y > 0){
                return 1; //可站立移动
            }
            if(playerRect.top-barrierBottom <= 6.0 && speed.y < 0){
                return 3; //卡比头撞到障碍物
            }
            if(kirbyRight-barrier.left <= 6.0 && speed.x > 0)return 4; // 卡比向右走碰撞障碍物
            if(barrierRight-playerRect.left <= 6.0 && speed.x < 0)return 2; // 卡比向左走碰撞障碍物
        }
    }
    return 0;
}