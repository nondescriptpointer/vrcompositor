#pragma once

#include <GL/glew.h>
#include <QOpenGLWindow>
#include <QRect>
#include <QOpenGLShaderProgram>
#ifdef QT_DEBUG
    #include "../util/framecounter.h"
#endif
#include "Batch.h"
#include "Actor.h"
#include "TextureManager.h"

class Window : public QOpenGLWindow {
    Q_OBJECT

public:
    Window();
    ~Window();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    QOpenGLShaderProgram program;
    gliby::Batch quad;
    gliby::Actor* plane;
    gliby::TextureManager* textureManager;

    void printContextInformation();
    #ifdef QT_DEBUG
        FrameCounter frameCounter;
    #endif
};