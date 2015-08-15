#include "window.h"

#include <QDebug>
#include <QString>

Window::Window(){
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,5);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);
}

Window::~Window(){
    // clear resources
}

void Window::resizeGL(int width, int height){
    (void)width;
    (void)height;
    //qDebug() << width << ", " << height;
}

void Window::initializeGL(){
    initializeOpenGLFunctions();
    #ifdef QT_DEBUG
        printContextInformation();
    #endif
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // create a test shader program
    program.addShaderFromSourceFile(QOpenGLShader::Vertex,"shaders/identity.vp");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment,"shaders/identity.fp");
    program.link();
    // create vertex array object
    vao = new QOpenGLVertexArrayObject;
    vao->create();
    vao->bind();
    triangle = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    triangle->create();
    triangle->bind();
    triangle->setUsagePattern(QOpenGLBuffer::StaticDraw);
    GLfloat tri[] =
    {
        0.0f,1.0f,-1.0f,1.0f,
         1.0f,1.0f,-1.0f,1.0f,
         1.0f,0.0f,-1.0f,1.0f,

    };
    triangle->allocate(tri,sizeof(tri));
    // configure shader
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0,GL_FLOAT,0,4,0);
    // clear color
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void Window::paintGL(){
    // clear
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width(),height());

    // draw
    program.bind();
    program.setUniformValue("vColor",QColor(255,255,255));
    vao->bind();
    glDrawArrays(GL_TRIANGLES,0,3);

    // ask for another update
    update();

    // measure framerate
    #ifdef QT_DEBUG
        frameCounter.tick();
    #endif
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