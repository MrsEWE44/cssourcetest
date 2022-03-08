#ifndef MATRIXBOXCAMERA_H
#define MATRIXBOXCAMERA_H

#include <QDebug>

class matrixBoxCamera
{
public:
    matrixBoxCamera();
public:
    float X,Y,Z,Y2,BOX_W,BOX_H,BOX_X,WIN_W,WIN_H,G_W,G_H;
    void print();
    int isOK();
};

#endif // MATRIXBOXCAMERA_H
