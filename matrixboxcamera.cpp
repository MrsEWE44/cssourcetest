#include "matrixboxcamera.h"

matrixBoxCamera::matrixBoxCamera()
{

}

void matrixBoxCamera::print()
{
    qDebug() << X<< Z << Y<<Y2 << BOX_W << BOX_H << BOX_X<<WIN_W << WIN_H << G_W << G_H;
}

int matrixBoxCamera::isOK()
{
    if(G_W > 0 && G_H > 0 &&WIN_W > 0&&WIN_H > 0&&X >0 && Z > 0 && Y > 0 && Y2 > 0 && BOX_H > 0 && BOX_W > 0 && BOX_X > 0){
        return 0;
    }
    return -1;
}
