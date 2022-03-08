#include "rolehp.h"

roleHP::roleHP(QObject *parent) : QObject(parent)
{

}

void roleHP::Start()
{
    csscore c;
    DWORD PID=c.getPidByProcessName("hl2.exe");
    HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS, 0, PID);
      if (NULL == Process) {
        qDebug() << "进程打开失败";
      }else{
          int hp =c.getMyHP(Process,PID);
          int lockhpvalue=255;
          while(lockhp == 1){
              if(hp < lockhpvalue){
                 c.setMyHP(Process,PID,lockhpvalue);
              }

              hp = c.getMyHP(Process,PID);
              //qDebug() << "my hp :: " << hp;

          }

      }
      CloseHandle(Process);
      emit Finished();
}
