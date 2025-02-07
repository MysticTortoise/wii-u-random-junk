#include "camTablet.hpp"

#include "stdlib.h"

#include <fstream>

#include "coreinit/debug.h"
#include "gx2/registers.h"

#include "CafeGLSLCompiler.h"


int InitializeGraphics()
{
    if (!GLSL_Init()) // Initialize Shader Compiler
    {
        return -1;
    }
    if (!WHBGfxInit()) // Initialize main graphics core.
    {
        return -1;
    }



    return 1;
}

WHBGfxShaderGroup *GLSL_CompileShader(const char *vsSrc, const char *psSrc)
{
    char infoLog[1024];
    GX2VertexShader *vs = GLSL_CompileVertexShader(vsSrc, infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if (!vs)
    {
        OSReport("Failed to compile vertex shader. Infolog: %s\n", infoLog);
        return NULL;
    }
    GX2PixelShader *ps = GLSL_CompilePixelShader(psSrc, infoLog, sizeof(infoLog), GLSL_COMPILER_FLAG_NONE);
    if (!ps)
    {
        OSReport("Failed to compile pixel shader. Infolog: %s\n", infoLog);
        return NULL;
    }
    WHBGfxShaderGroup *shaderGroup = (WHBGfxShaderGroup *)malloc(sizeof(WHBGfxShaderGroup));
    memset(shaderGroup, 0, sizeof(*shaderGroup));
    shaderGroup->vertexShader = vs;
    shaderGroup->pixelShader = ps;
    return shaderGroup;
}

WHBGfxShaderGroup *GLSL_CompileShaderFromFiles(std::string *vertexShaderPath, std::string *fragmentShaderPath)
{
    std::ifstream vShaderIn("romfs:/" + *vertexShaderPath);
    std::string vShaderContents((std::istreambuf_iterator<char>(vShaderIn)),
                                std::istreambuf_iterator<char>());
    const char *vShader = vShaderContents.c_str();

    std::ifstream fShaderIn("romfs:/" + *fragmentShaderPath);
    std::string fShaderContents((std::istreambuf_iterator<char>(fShaderIn)),
                                std::istreambuf_iterator<char>());
    const char *fShader = fShaderContents.c_str();

    return GLSL_CompileShader(vShader, fShader);
}
WHBGfxShaderGroup *GLSL_CompileShaderFromFiles(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    std::string vPathString = vertexShaderPath;
    std::string fPathString = fragmentShaderPath;
    return GLSL_CompileShaderFromFiles(&vPathString, &fPathString);
}