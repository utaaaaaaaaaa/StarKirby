#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <scene/Barrier.h>
#include "const/Constants.h"

class Background {
public:
    Background();
    void loadTextures(const std::string& texturePathTop, const std::string& texturePathBottom);
    void update();
    void setBottomPos(int width);
    void setBottomRect(sf::IntRect rect);
    void resetPosition(){m_spriteBottom.setPosition(0, 0);};
    // void setTopRects
    void draw(sf::RenderWindow& window);
    void splitMap(sf::Sprite& sprite);
    bool loadFromFile(const std::string& filePath); // 从文件加载地面数据
    Barrier& getBarrier() {return m_barrier;};
    const std::vector<sf::FloatRect>& getGroundRects() const { return groundRects; }

private:
    sf::Texture m_textureTop;
    sf::Texture m_textureBottom;
    sf::Sprite m_spriteTop;
    sf::Sprite m_spriteBottom;
    Barrier m_barrier = Barrier();
    std::vector<sf::FloatRect> groundRects = Map::groundsRects; //存储地面矩形
};

#endif 
