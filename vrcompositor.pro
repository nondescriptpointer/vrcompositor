SET(FRAMERATE TRUE)

MOC_DIR = build/moc
OBJECTS_DIR = build/object

CONFIG += debug

HEADERS += src/window/window.h src/util/framecounter.h
SOURCES += src/window/window.cpp src/util/framecounter.cpp src/main.cpp