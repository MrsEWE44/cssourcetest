#include "cssource.h"

cssource::cssource()
{

}

void cssource::test(QMainWindow *mmm)
{
    this->m = mmm;
      ww = new QWidget();
      m->setWindowTitle("cs source");
      m->setCentralWidget(ww);
      m->close();
      QPushButton *b1 = new QPushButton("lock hp");
      QPushButton *b2 = new QPushButton("drawBox");
      QPushButton *b3 = new QPushButton("lock head");

      QPushButton *exitbutton = new QPushButton("exit");

      QObject::connect(b1, &QPushButton::clicked, [=]() {
          if (rhp == NULL) {
            rhp = new roleHP();
          }
          if (rhp->lockhp == 1) {
            b1->setText("lock hp");
            rhp->lockhp = 0;
          } else {
            QThread *th = new QThread();
            rhp = new roleHP();
            rhp->lockhp = 1;
            th->start();
            b1->setText("unlock hp");
            rhp->moveToThread(th);
            QObject::connect(th, &QThread::started, rhp, &roleHP::Start);
            QObject::connect(rhp, &roleHP::Finished, rhp,
                             &roleHP::deleteLater);
            QObject::connect(rhp, &roleHP::Finished, th, &QThread::quit);
            QObject::connect(th, &QThread::finished, th, &QThread::deleteLater);
          }
        });


      QObject::connect(b2, &QPushButton::clicked, [=]() {
          if (dmb == NULL) {
            dmb = new drawMatrixBox();
          }
          if (dmb->drawmb == 1) {
            b2->setText("drawBox");
            dmb->drawmb = 0;
          } else {
            QThread *th = new QThread();
            dmb = new drawMatrixBox();
            dmb->drawmb = 1;
            th->start();
            b2->setText("undrawBox");
            dmb->moveToThread(th);
            QObject::connect(th, &QThread::started, dmb, &drawMatrixBox::Start);
            QObject::connect(dmb, &drawMatrixBox::Finished, dmb,
                             &drawMatrixBox::deleteLater);
            QObject::connect(dmb, &drawMatrixBox::Finished, th, &QThread::quit);
            QObject::connect(th, &QThread::finished, th, &QThread::deleteLater);
          }
        });

      QObject::connect(b3, &QPushButton::clicked, [=]() {
          if (lh == NULL) {
            lh = new lockHead();
          }
          if (lh->islockhead == 1) {
            b3->setText("lock head");
            lh->islockhead = 0;
          } else {
            QThread *th = new QThread();
            lh = new lockHead();
            lh->islockhead = 1;
            th->start();
            b3->setText("unlock head");
            lh->moveToThread(th);
            QObject::connect(th, &QThread::started, lh, &lockHead::Start);
            QObject::connect(lh, &lockHead::Finished, lh,
                             &lockHead::deleteLater);
            QObject::connect(lh, &lockHead::Finished, th, &QThread::quit);
            QObject::connect(th, &QThread::finished, th, &QThread::deleteLater);
          }
        });


      QObject::connect(exitbutton, &QPushButton::clicked, [=]() { exit(0); }

        );


      QHBoxLayout *hbox = new QHBoxLayout();

        hbox->addWidget(b1);
        hbox->addWidget(b2);
        hbox->addWidget(b3);

        vbox = new QVBoxLayout();
        vbox->addLayout(hbox);
        vbox->addWidget(exitbutton);

        ww->setLayout(vbox);
}
