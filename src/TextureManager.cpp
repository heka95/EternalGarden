#include "TextureManager.hpp"

std::unique_ptr<TextureManager> TextureManager::m_instance;
TextureManager& TextureManager::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance.reset(new TextureManager());
    }
    return *m_instance.get();
}