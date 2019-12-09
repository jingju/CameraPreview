//
// Created by Macro on 2019-12-05.
//

#ifndef CAMERAPREVIEW_GPU_TEXTURE_FRAME_COMPIER_H
#define CAMERAPREVIEW_GPU_TEXTURE_FRAME_COMPIER_H


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "CommonTools.h"
#include "texture_frame_compier.h"
#include "matrix.h"

/***/
static char* GPU_FRAME_VERTEX_SHADER =
        "attribute vec4 vPosition;\n"
        "attribute vec4 vTexCords;\n"
        "varying vec2 yuvTexCoords;\n"
        "uniform highp mat4 trans; \n"
        "void main() {\n"
        "  yuvTexCoords = vTexCords.xy;\n"
        "  gl_Position = trans * vPosition;\n"
        "}\n";
//TODO 学完opengl再来看zh
static char* GPU_FRAME_FRAGMENT_SHADER =
        "#extension GL_OES_EGL_image_external : require\n"
        "precision mediump float;\n"
        "uniform samplerExternalOES yuvTexSampler;\n"
        "varying vec2 yuvTexCoords;\n"
        "void main() {\n"
        "  gl_FragColor = texture2D(yuvTexSampler, yuvTexCoords);\n"
        "}\n";

class GPUTextureFrameCopier : public TextureFrameCopier{
public:
    GPUTextureFrameCopier();
    virtual ~GPUTextureFrameCopier();

    virtual bool init();
    virtual void renderWithCoords(TextureFrame* textureFrame, GLuint texId, GLfloat* vertexCoords, GLfloat* textureCoords);
protected:
    GLint mGLUniformTexture;
};

#endif //CAMERAPREVIEW_GPU_TEXTURE_FRAME_COMPIER_H
