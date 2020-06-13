#pragma once

#include <memory>

class TextureManager
{
public:
    virtual ~TextureManager() = default;
    static TextureManager &getInstance();

private:
    TextureManager() = default;
    TextureManager(const TextureManager &object) = delete;
    TextureManager &operator=(const TextureManager &object) = delete;
    static std::unique_ptr<TextureManager> m_instance;
};