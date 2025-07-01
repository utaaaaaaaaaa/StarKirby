#include "Animation.h"
#include <algorithm>


void Animation::addFrame(sf::IntRect frame){
    frames.push_back(frame);
}

// 设置动画帧参数
void Animation::play(float speed,bool loop){
    this->speed = speed;
    this->loop = loop;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

sf::IntRect& Animation::update(float deltaTime){
    elapsedTime += deltaTime;
    if(elapsedTime >= speed){
        currentFrame = loop ? (currentFrame + 1)%frames.size()
            : std::min(currentFrame+1,int(frames.size()-1)); 
        elapsedTime = 0;
    }
    return frames[currentFrame];
}

bool Animation::isFinished(){
    return !loop && currentFrame == frames.size() - 1;
}