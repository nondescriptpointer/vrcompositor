#include <QGuiApplication>
#include <QScreen>
#include <iostream>

#include "window/window.h"

int main(int argc, char **argv){
    QGuiApplication app(argc, argv);

    Window window;
    //view.resize(1280,800);
    window.show();

    return app.exec();
}
