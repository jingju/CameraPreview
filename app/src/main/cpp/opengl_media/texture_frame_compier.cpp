//
// Created by Macro on 2019-12-05.
//

#include "texture_frame_compier.h"
#define LOG_TAG "TextureFrameCopier"

TextureFrameCopier::TextureFrameCopier() {
}

TextureFrameCopier::~TextureFrameCopier() {
}

void TextureFrameCopier::destroy() {
    mIsInitialized = false;
    if (mGLProgId) {
        glDeleteProgram(mGLProgId);
        mGLProgId = 0;
    }
}