#pragma once

#include <GL/glew.h>
#include <QOpenGLWindow>
#include <QRect>
#ifdef QT_DEBUG
    #include "../util/framecounter.h"
#endif
#include "Batch.h"
#include "Actor.h"
#include "TextureManager.h"
#include "TransformPipeline.h"
#include "MatrixStack.h"
#include "Frustum.h"
#include "Frame.h"
#include "ShaderManager.h"
#include "UniformManager.h"

class Window : public QOpenGLWindow {
    Q_OBJECT

public:
    Window();
    ~Window();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    // shader
    gliby::ShaderManager* shaderManager;
    gliby::UniformManager* uniformManager;
    GLuint shader;
    // texture
    gliby::TextureManager* textureManager;
    // transforms
    gliby::TransformPipeline transformPipeline;
    gliby::MatrixStack modelViewMatrix;
    gliby::MatrixStack projectionMatrix;
    gliby::Frame cameraFrame;
    gliby::Frustum viewFrustum;
    // objs
    gliby::Batch quad;
    gliby::Actor* plane;
    

    void printContextInformation();
    #ifdef QT_DEBUG
        FrameCounter frameCounter;
    #endif
};