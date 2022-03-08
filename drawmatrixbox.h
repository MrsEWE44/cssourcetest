#ifndef DRAWMATRIXBOX_H
#define DRAWMATRIXBOX_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include <io.h>
#include <map>
#include <fstream>
#include <atlimage.h>

#include "csscore.h"
#include "drawbox.h"



class drawMatrixBox : public QObject
{
    Q_OBJECT
public:
    explicit drawMatrixBox(QObject *parent = nullptr);

public:
    int drawmb=0;
private:
    csscore c;

public slots:
  void Start();

signals:
  void Finished();

};

#endif // DRAWMATRIXBOX_H
