#include "window.h"

#include <QDebug>
#include <QString>
#include "GeometryFactory.h"
#include "Math3D.h"

#include <iostream>

Window::Window(){
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,5);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(16);
    setFormat(format);
    // create hmd
    hmd = new OculusHMD(winId());
}

Window::~Window(){
    // clear resources
}

void Window::resizeGL(int width, int height){
    // change gl viewport size
    glViewport(0,0,width,height);
    // reset the frustum and projection matrix
    viewFrustum.setPerspective(45.0f, float(width)/float(height),0.1f,500.0f);
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
    // create test shader program
    const char* searchPath[] = {"./shaders/","/home/ego/projects/personal/gliby/shaders/"};
    shaderManager = new gliby::ShaderManager(sizeof(searchPath)/sizeof(char*),searchPath);
    gliby::ShaderAttribute attrs[] = {{0,"vVertex"},{2,"vNormal"},{3,"vTexCoord"}};
    shader = shaderManager->buildShaderPair("windowshader.vp","windowshader.fp",sizeof(attrs)/sizeof(gliby::ShaderAttribute),attrs);
    const char* uniforms[] = {"mvpMatrix","textureUnit"};
    uniformManager = new gliby::UniformManager(shader,sizeof(uniforms)/sizeof(char*),uniforms);
    // create a texture manager
    textureManager = new gliby::TextureManager();
    const char* textures[] = {"assets/textures/1.png"};
    textureManager->loadTextures(sizeof(textures)/sizeof(char*),textures,GL_TEXTURE_2D,GL_TEXTURE0);
    // create plane geometry
    quad = gliby::GeometryFactory::plane(1.0f,1.0f,0.0f,0.0f,0.0f);
    plane = new gliby::Actor(&quad,textureManager->get("assets/textures/1.png"));
    // clear color
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    // setup viewport
    glViewport(0,0,width(),height());
    // setup transform pipeline
    transformPipeline.setMatrixStacks(modelViewMatrix,projectionMatrix);
    viewFrustum.setPerspective(35.0f, float(width())/float(height()), 1.0f, 500.0f);
    projectionMatrix.loadMatrix(viewFrustum.getProjectionMatrix());
    modelViewMatrix.loadIdentity();
    // setup camera
    cameraFrame.moveForward(-3.0f);
    /*cameraFrame.setOrigin(50.0f,50.0f,0.0f);
    cameraFrame.lookAt(0.0f,0.0f,0.0f);*/
}

void Window::paintGL(){
    // clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // setup model view matrix to use the camera
    Math3D::Matrix44f mCamera;
    cameraFrame.getCameraMatrix(mCamera);
    modelViewMatrix.pushMatrix();
    modelViewMatrix.multMatrix(mCamera);

    plane->getFrame().rotateLocalY(0.01f);
    modelViewMatrix.pushMatrix();
    Math3D::Matrix44f mObject;
    plane->getFrame().getMatrix(mObject);
    modelViewMatrix.multMatrix(mObject);

    // bind shader
    glUseProgram(shader);

    // bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,plane->getTexture());
    // set the texture uniform0
    glUniform1i(uniformManager->get("textureUnit"),0);
    // set transformation matrix
    glUniformMatrix4fv(uniformManager->get("mvpMatrix"),1,GL_FALSE,transformPipeline.getModelViewProjectionMatrix());

    // draw plane
    plane->getGeometry().draw();

    // reset model view matrix
    modelViewMatrix.popMatrix();
    modelViewMatrix.popMatrix();

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