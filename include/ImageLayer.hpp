#pragma once

#include <iostream>
#include "GameTypes.hpp"
#include "Layer.hpp"

class ImageLayer : public Layer
{
public:
    ImageLayer(std::string textureId, int x, int y, float scrollRatio = 1.0f, float scaleX = 1.0f, float scaleY = 1.0f);
    void setScrollRation(float ratio) { m_scrollRatio = ratio; }
    void setOffset(int x, int y) { m_offsetX = x, m_offsetY = y; }
    void setRepeat(bool mustRepeat) { m_repeat = mustRepeat; }
    void queryImage(std::string textureId);
    virtual void render();
    virtual void update();

private:
    bool m_repeat;
    float m_scrollRatio;
    std::string m_textureId;
    float m_scaleX;
    float m_scaleY;
    int m_offsetX;
    int m_offsetY;
    int m_imageWidth;
    int m_imageHeight;
    Garden::Flip m_flip;
};