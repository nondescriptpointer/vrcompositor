#include "framecounter.h"

FrameCounter::FrameCounter():frameCount(0),lastTime(QTime::currentTime()){
    // pass
}

void FrameCounter::tick(){
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