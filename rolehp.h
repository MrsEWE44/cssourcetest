#ifndef ROLEHP_H
#define ROLEHP_H
#include <QObject>
#include <QDebug>

#include "csscore.h"

class roleHP : public QObject
{
    Q_OBJECT
public:
    explicit roleHP(QObject *parent = nullptr);

public:
    DWORD MYHPADDRVALUE=0;
    DWORD MYHPADDR2VALUE=0;
    int lockhp=0;

public slots:
  void Start();

signals:
  void Finished();

};

#endif // ROLEHP_H
