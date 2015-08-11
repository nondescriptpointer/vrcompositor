#include "window.h"

#include <QDebug>
#include <QString>

Window::Window():frameCount(0),lastTime(QTime::currentTime()){
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,5);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);


}

Window::~Window(){
    teardownGL();
}

void Window::resizeGL(int width, int height){
    (void)width;
    (void)height;
}

void Window::initializeGL(){
    initializeOpenGLFunctions();
    printContextInformation();
    // clear color
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void Window::paintGL(){
    // measure framerate
    measureFramerate();
    // clear
    glClear(GL_COLOR_BUFFER_BIT);

    // ask for another update
    update();
}

void Window::teardownGL(){
    // no data yet
}

void Window::printContextInformation(){
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get version information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile()){
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
    #undef CASE

    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void Window::measureFramerate(){
    ++frameCount;
    const QTime currentTime = QTime::currentTime();
    const int interval = 2500;
    const int delta = lastTime.msecsTo(currentTime);
    if(delta > interval){
        qreal fps = 1000.0 * frameCount / delta;
        qDebug() << "FPS:" << fps;
        frameCount = 0;
        lastTime = currentTime;
    }
}