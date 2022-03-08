#ifndef DRAWBOX_H
#define DRAWBOX_H

#include <QObject>
#include <qDebug>

#include <Windows.h>
#include "matrixboxcamera.h"


class drawBox : public QObject
{
    Q_OBJECT
public:
    explicit drawBox(QObject *parent = nullptr);
    drawBox(const matrixBoxCamera &m);
public:
    matrixBoxCamera m;

public slots:
  void Start();

signals:
  void Finished();

};

#endif // DRAWBOX_H
