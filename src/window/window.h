#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QRect>
#include <QTime>

class Window : public QOpenGLWindow, protected QOpenGLFunctions {
    Q_OBJECT

public:
    Window();
    ~Window();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

private:
    void printContextInformation();
    void measureFramerate();

    int frameCount;
    QTime lastTime;
    QTime currentTime;
};