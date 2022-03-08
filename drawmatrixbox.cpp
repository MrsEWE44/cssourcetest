#include "drawmatrixbox.h"

drawMatrixBox::drawMatrixBox(QObject *parent) : QObject(parent)
{

}

void drawMatrixBox::Start()
{
    DWORD PID=c.getPidByProcessName("hl2.exe");
    HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);
      if (NULL == Process) {
        qDebug() << "进程打开失败";
      }else{
          while(drawmb == 1){
              int playerNum = c.getPlayerNum(Process,PID);
              //qDebug() << "playerNum :: " << playerNum;
              DWORD PositionBaseAddr=POSITION_BASE_ADDR;
              DWORD nextPersonAddr=POSITION_NEXT_PERSON_ADDR;
              DWORD pp=PositionBaseAddr;
              PERSONPOSITION me;
              for(int i =0 ;i<playerNum;i++){
                  if(i >0){
                      pp=pp+nextPersonAddr;
                  }
                  PERSONPOSITION p = c.getPlayerPersonPosition(Process,PID,pp);
                  int hp = c.getPlayerPersonHP(Process,PID,pp);
                  if(i == 0){
                      me=p;
                      //qDebug() << "me : ";
                      //formatPrintPosition(me);
                  }
                  if((me == p) ==1){

                      if(hp > 1){
                          matrixBoxCamera m =c.getCamera(Process,PID,p);
//                          m.print();
                          drawBox *d = new drawBox(m);
                          QThread *th = new QThread();
                          th->start();
                          d->moveToThread(th);
                          QObject::connect(th, &QThread::started, d, &drawBox::Start);
                          QObject::connect(d, &drawBox::Finished, d,
                                           &drawBox::deleteLater);
                          QObject::connect(d, &drawBox::Finished, th, &QThread::quit);
                          QObject::connect(th, &QThread::finished, th, &QThread::deleteLater);



                          //formatPrintPosition(p);
                      }

                  }
              }
          }

      }

    CloseHandle(Process);
    emit Finished();
}
