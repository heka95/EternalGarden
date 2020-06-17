#include "ImageLayer.hpp"
#include "TextureManager.hpp"

ImageLayer::ImageLayer(std::string textureId, int x, int y, float scrollRatio, float scaleX, float scaleY)
{
    m_textureId = textureId;
    m_offsetX = x;
    m_offsetY = y;
    m_scrollRatio = scrollRatio;
    m_repeat = true;
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    queryImage(m_textureId);
}

void ImageLayer::render()
{
    TextureManager::getInstance().draw(m_textureId, Garden::Vector2I{m_offsetX, m_offsetY},
                                       Garden::Size{m_imageWidth, m_imageHeight}, Garden::Vector2F{m_scaleX, m_scaleY}, m_flip, m_scrollRatio);
}

void ImageLayer::update()
{ }

void ImageLayer::queryImage(std::string textureId)
{
    SDL_Texture* texture = TextureManager::getInstance().getTextureFromId(m_textureId);
    SDL_QueryTexture(texture, NULL, NULL, &m_imageWidth, &m_imageHeight);
}