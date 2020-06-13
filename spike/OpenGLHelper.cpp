#include "OpenGLHelper.h"

const char* OpenGLHelper::getVendor()
{
    GL_GetString getStringFunc = (GL_GetString)SDL_GL_GetProcAddress("glGetString");
    return (const char *)getStringFunc(GL_VENDOR);
}

const char* OpenGLHelper::getRenderer()
{
    GL_GetString getStringFunc = (GL_GetString)SDL_GL_GetProcAddress("glGetString");
    return (const char *)getStringFunc(GL_RENDERER);
}

const char* OpenGLHelper::getGLVersion()
{
    GL_GetString getStringFunc = (GL_GetString)SDL_GL_GetProcAddress("glGetString");
    return (const char *)getStringFunc(GL_VERSION);
}

const char* OpenGLHelper::getShaderVersion()
{
    GL_GetString getStringFunc = (GL_GetString)SDL_GL_GetProcAddress("glGetString");
    return (const char *)getStringFunc(GL_SHADING_LANGUAGE_VERSION);
}