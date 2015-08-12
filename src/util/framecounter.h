#pragma once

#include <QDebug>
#include <QTime>

class FrameCounter {
public:
    FrameCounter();
    void tick();
private:
    int frameCount;
    QTime lastTime;
    QTime currentTime;
};