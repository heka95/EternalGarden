#ifndef OPENGLHELPER_H
#define OPENGLHELPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

class OpenGLHelper
{
public:
    static const char *getVendor();
    static const char *getRenderer();
    static const char *getGLVersion();
    static const char *getShaderVersion();

private:
    typedef const GLubyte *(*GL_GetString)(GLenum);
};

#endif // OPENGLHELPER_H