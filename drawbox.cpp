#include "drawbox.h"

drawBox::drawBox(QObject *parent) : QObject(parent)
{

}

drawBox::drawBox(const matrixBoxCamera &mmm)
{
    this->m=mmm;
}

void drawBox::Start()
{
    if(m.isOK() == 0){
        qDebug() << " is ok !!!";
        HDC hdc = GetWindowDC(GetDesktopWindow());
        HPEN hpen1 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
        SelectObject(hdc, hpen1);
        HBRUSH hBrush=(HBRUSH)GetStockObject (NULL_BRUSH) ;
        SelectObject (hdc, hBrush);
        int left =m.BOX_X+m.WIN_W;
        int top = m.Y2+m.WIN_H;
        int right = left + m.BOX_W;
        int bottom = top + m.BOX_H;
        int right_maxw=m.G_W+m.WIN_W;
        int bottom_maxh=m.G_H+m.WIN_H;

        if(right_maxw > right && left > m.WIN_W && top > m.WIN_H && bottom_maxh > bottom){
            Rectangle(hdc, left,top,right,bottom);
        }
    }
    emit Finished();

}
