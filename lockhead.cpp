#include "lockhead.h"

lockHead::lockHead(QObject *parent) : QObject(parent)
{

}

void lockHead::Start()
{
    DWORD PID=c.getPidByProcessName("hl2.exe");
    HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);
      if (NULL == Process) {
        qDebug() << "进程打开失败";
      }else{

          while(islockhead == 1){
              int playerNum = c.getPlayerNum(Process,PID);
              //qDebug() << "playerNum :: " << playerNum;
              DWORD PositionBaseAddr=POSITION_BASE_ADDR;
              DWORD nextPersonAddr=POSITION_NEXT_PERSON_ADDR;
              DWORD pp=PositionBaseAddr;
              PERSONPOSITION me;
              float myfov=c.getMyFov(Process,PID);
              float myfovleft=c.getMyFovLeft(Process,PID);
               float setfovh = myfov,setfovleft=myfovleft;

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
                          //m.print();

                          float fovleft=(m.BOX_X-(m.G_W/2));
                          float fovh=((m.G_H/2)-m.Y2);

                          fovleft=c.formatFloatToTwoLen(fovleft);
                          fovh=c.formatFloatToTwoLen(fovh);

                          if(fovh <= -3 || fovh >= 3){
                              setfovh = myfov-fovh;
                               //c.setMyFov(Process,PID,setfovh);

                          }
                          if(fovleft <=-3 || fovleft >= 3 ){
                              setfovleft=myfovleft-fovleft;
                              //c.setMyFovLeft(Process,PID,setfovleft);

                          }
                          qDebug() <<fovleft << " -- " << fovh << " -- " << setfovh << " -- " << setfovleft << " -- " << myfov << " -- " << myfovleft;


                      }

                  }
              }
              // Sleep(300);
          }

      }

    CloseHandle(Process);
    emit Finished();
}
