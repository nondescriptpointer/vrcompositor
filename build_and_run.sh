#/usr/bin/env sh
qmake -o Makefile vrcompositor.pro && make && vblank_mode=0 primusrun ./vrcompositor
