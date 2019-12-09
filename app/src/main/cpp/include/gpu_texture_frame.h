//
// Created by Macro on 2019-12-05.
//

#ifndef CAMERAPREVIEW_GPU_TEXTURE_FRAME_H
#define CAMERAPREVIEW_GPU_TEXTURE_FRAME_H

#include "texture_frame.h"

/**
 * Video Host Texture
 */
class GPUTextureFrame: public TextureFrame {
private:
    GLuint decodeTexId;
    int initTexture();

public:
    GPUTextureFrame();
    virtual ~GPUTextureFrame();

    bool createTexture();
    void updateTexImage();
    bool bindTexture(GLint* uniformSamplers);
    void dealloc();

    GLuint getDecodeTexId() {
        return decodeTexId;
    };

};

#endif //CAMERAPREVIEW_GPU_TEXTURE_FRAME_H
