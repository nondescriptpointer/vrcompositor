#include "window.h"

#include <QDebug>
#include <QString>
#include "GeometryFactory.h"
#include "Math3D.h"

Window::Window(){
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,5);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(16);
    setFormat(format);
}

Window::~Window(){
    // clear resources
}

void Window::resizeGL(int width, int height){
    // change gl viewport size
    glViewport(0,0,width,height);
    // reset the frustum and projection matrix
    viewFrustum.setPerspective(45.0f, float(width)/float(height),0.1f,5000.0f);
    projectionMatrix.loadMatrix(viewFrustum.getProjectionMatrix());
}

void Window::initializeGL(){
    //initializeOpenGLFunctions();
    #ifdef QT_DEBUG
        printContextInformation();
    #endif
    // init glew
    glewExperimental = GL_TRUE;
    glewInit();
    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    // enable culling
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);*/
    // blend mode
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // enable antialiasing
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    // a create test shader program
    program.addShaderFromSourceFile(QOpenGLShader::Vertex,"shaders/identity.vp");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment,"shaders/identity.fp");
    program.link();
    // create a texture manager
    textureManager = new gliby::TextureManager();
    const char* textures[] = {"assets/textures/1.png"};
    textureManager->loadTextures(sizeof(textures)/sizeof(char*),textures,GL_TEXTURE_2D,GL_TEXTURE0);
    // create plane geometry
    quad = gliby::GeometryFactory::plane(1.0f,1.0f,0.0f,0.0f,0.0f);
    plane = new gliby::Actor(&quad,textureManager->get("assets/textures/1.png"));
    // configure shader
    //program.enableAttributeArray(0);
    program.bindAttributeLocation("vVertex",0);
    program.bindAttributeLocation("vTexCoord",3);
    program.setAttributeBuffer(0,GL_FLOAT,0,4,0);
    // clear color
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    // setup viewport
    glViewport(0,0,width(),height());
    // setup transform pipeline
    transformPipeline.setMatrixStacks(modelViewMatrix,projectionMatrix);
    viewFrustum.setPerspective(35.0f, float(width())/float(height()), 1.0f, 5000.0f);
    projectionMatrix.loadMatrix(viewFrustum.getProjectionMatrix());
    modelViewMatrix.loadIdentity();
    // setup camera
    cameraFrame.setOrigin(0.0f,1.0f,0.0f);
    cameraFrame.lookAt(0.0f,0.0f,0.0f);
}

void Window::paintGL(){
    // clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // setup model view matrix to use the camera
    Math3D::Matrix44f mCamera;
    cameraFrame.getCameraMatrix(mCamera);
    modelViewMatrix.pushMatrix();
    modelViewMatrix.multMatrix(mCamera);

    // bind shader
    program.bind();

    // bind the texture
    glBindTexture(GL_TEXTURE_2D,plane->getTexture());
    // set the texture uniform
    program.setUniformValue("textureUnit",0);
    program.setUniformValue("mvpMatrix",*transformPipeline.getModelViewProjectionMatrix());
    // draw plane
    plane->getGeometry().draw();

    // ask for another update
    update();

    // reset model view matrix
    modelViewMatrix.popMatrix();

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