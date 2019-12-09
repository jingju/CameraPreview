//
// Created by Macro on 2019-12-05.
//

#ifndef CAMERAPREVIEW_YUV_TEXTURE_FRAME_H
#define CAMERAPREVIEW_YUV_TEXTURE_FRAME_H


#include "movie_frame.h"
#include "texture_frame.h"

/**
 * Video Host Texture
 */
class YUVTextureFrame: public TextureFrame {
private:
    bool writeFlag;
    GLuint textures[3];
    int initTexture();

    VideoFrame *frame;
public:
    YUVTextureFrame();
    virtual ~YUVTextureFrame();

    void setVideoFrame(VideoFrame *yuvFrame);

    bool createTexture();
    void updateTexImage();
    bool bindTexture(GLint* uniformSamplers);
    void dealloc();
};

#endif //CAMERAPREVIEW_YUV_TEXTURE_FRAME_H
