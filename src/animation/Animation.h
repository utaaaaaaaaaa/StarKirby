#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

// animation状态枚举
enum class AnimationState {
    Standing,
    Walking,
    Jumping,
    Attacking,
    AttackFly,
    Falling,
    Death,
    Flying,
    FlyPre,
    Devour,
};

class Animation {
public:
    Animation() = default;
    void addFrame(sf::IntRect frame);
    //设置动画播放参数
    void play(float speed,bool loop = true);
    //更新动画
    sf::IntRect& update(float deltaTime);
    //动画是否完成
    bool isFinished();
    void setFrames(std::vector<sf::IntRect> frameVec){frames = frameVec;}

private:
    std::vector<sf::IntRect> frames;
    float speed = 0.1f;
    int currentFrame = 0;
    float elapsedTime = 0.0f; // 积累的时间
    bool loop = true;
};

#endif