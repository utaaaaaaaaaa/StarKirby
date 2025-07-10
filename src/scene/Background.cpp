#include "Background.h"
#include "const/Constants.h"

using namespace Map;

Background::Background() {
    // 初始化精灵的位置或其他属性
}

void Background::loadTextures(const std::string& texturePathTop, const std::string& texturePathBottom) {
    // 加载顶部背景
    if (!m_textureTop.loadFromFile(texturePathTop)) {
        throw std::runtime_error("加载背景失败");
    }
    m_spriteTop.setTexture(m_textureTop);
    m_spriteTop.setPosition(ground_offsetX, ground_offsetY);
    splitMap(m_spriteTop);

    // 加载底部背景
    if (!m_textureBottom.loadFromFile(texturePathBottom)) {
        throw std::runtime_error("加载背景失败");
    }
    m_spriteBottom.setTexture(m_textureBottom);

    // 设置底部背景的位置
    m_spriteBottom.setPosition(0, 0);
}

void Background::update() {
    // 如果背景需要滚动，可以在这里更新精灵的位置
}

void Background::setBottomPos(int x){
    sf::Vector2f pos = m_spriteBottom.getPosition();
    m_spriteBottom.setPosition(x,pos.y);
}

void Background::setBottomRect(sf::IntRect rect){
    m_spriteBottom.setTextureRect(rect);
}

void Background::splitMap(sf::Sprite& tile) {
    //切割图片
    tile.setTextureRect(sf::IntRect(ground_split_left, ground_split_top,ground_split_width,ground_split_height));
}

void Background::draw(sf::RenderWindow& window) {
    // 渲染背景
    window.draw(m_spriteBottom);
    window.draw(m_spriteTop);
}
