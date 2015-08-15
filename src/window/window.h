#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QRect>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#ifdef QT_DEBUG
    #include "../util/framecounter.h"
#endif

class Window : public QOpenGLWindow, protected QOpenGLFunctions {
    Q_OBJECT

public:
    Window();
    ~Window();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    QOpenGLShaderProgram program;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *triangle;

    void printContextInformation();
    #ifdef QT_DEBUG
        FrameCounter frameCounter;
    #endif
};