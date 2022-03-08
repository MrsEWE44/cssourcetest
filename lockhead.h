#ifndef LOCKHEAD_H
#define LOCKHEAD_H

#include <QObject>
#include <QDebug>
#include "csscore.h"


#define FOV_BASE_ADDR 0x4622CC

class lockHead : public QObject
{
    Q_OBJECT
public:
    explicit lockHead(QObject *parent = nullptr);


public:
    int islockhead=0;
private:
    csscore c;
public slots:
  void Start();

signals:
  void Finished();
};

#endif // LOCKHEAD_H
