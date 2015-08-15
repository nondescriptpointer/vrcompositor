GLIBY_DIR = "../gliby"

MOC_DIR = build/moc
OBJECTS_DIR = build/object

CONFIG += debug

QMAKE_CXXFLAGS += -O3 -march=native -std=c++0x

LIBS += -lassimp -lfreeimage -lGL -lGLU -lGLEW -lboost_system -lboost_filesystem
QT += opengl

INCLUDEPATH += $$GLIBY_DIR/include
HEADERS += $$GLIBY_DIR/include/Actor.h $$GLIBY_DIR/include/Batch.h $$GLIBY_DIR/include/Frame.h $$GLIBY_DIR/include/Frustum.h $$GLIBY_DIR/include/GeometryFactory.h $$GLIBY_DIR/include/Math3D.h $$GLIBY_DIR/include/MatrixStack.h $$GLIBY_DIR/include/ModelLoader.h $$GLIBY_DIR/include/ShaderManager.h $$GLIBY_DIR/include/TextureManager.h $$GLIBY_DIR/include/Grid.h $$GLIBY_DIR/include/TransformPipeline.h $$GLIBY_DIR/include/TriangleBatch.h $$GLIBY_DIR/include/UniformManager.h
SOURCES += $$GLIBY_DIR/src/Actor.cpp $$GLIBY_DIR/src/Batch.cpp $$GLIBY_DIR/src/Frame.cpp $$GLIBY_DIR/src/Frustum.cpp $$GLIBY_DIR/src/GeometryFactory.cpp $$GLIBY_DIR/src/Math3D.cpp $$GLIBY_DIR/src/MatrixStack.cpp $$GLIBY_DIR/src/ModelLoader.cpp $$GLIBY_DIR/src/ShaderManager.cpp $$GLIBY_DIR/src/TextureManager.cpp $$GLIBY_DIR/src/Grid.cpp $$GLIBY_DIR/src/TransformPipeline.cpp $$GLIBY_DIR/src/TriangleBatch.cpp $$GLIBY_DIR/src/UniformManager.cpp

HEADERS += src/window/window.h src/util/framecounter.h
SOURCES += src/window/window.cpp src/util/framecounter.cpp src/main.cpp