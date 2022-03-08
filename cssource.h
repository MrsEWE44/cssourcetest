#ifndef CSSOURCE_H
#define CSSOURCE_H


#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QThread>
#include <QVBoxLayout>


#include <Windows.h>

#include "rolehp.h"
#include "drawmatrixbox.h"
#include "lockhead.h"


class cssource
{
public:
    cssource();

public:
    void test(QMainWindow *m);

private:
  QMainWindow *m;
  QWidget *ww;
  QVBoxLayout *vbox;

public:
  roleHP *rhp =NULL;
  drawMatrixBox *dmb = NULL;
  lockHead *lh = NULL;

};

#endif // CSSOURCE_H
