#include "csscore.h"

csscore::csscore()
{

}


void csscore::formatPrintPosition(PERSONPOSITION p)
{
    float z =formatDwordToFloat(p.Z);
    float x = formatDwordToFloat(p.X);
    float y = formatDwordToFloat(p.Y);
    qDebug("z : %f -- x : %f -- y : %f\n",z,x,y);
}

float csscore::formatDwordToFloat(DWORD w)
{
    float f = *((float *)&w);
    return f;
}

float csscore::formatFloatToTwoLen(float f)
{
    QString s =  QString::number(f);
    QString fff=s;
    if(s.mid(0) == "-"){
       fff=s.mid(1);
    }
    if(fff.length() <= 2){
        return f;
    }else{
        return fff.mid(0,2).toFloat();
    }

}

double csscore::formatDwordToDouble(DWORD w)
{
    double f = *((double *)&w);
    return f;
}

float csscore::getMyFov(HANDLE Process, DWORD PID)
{
    DWORD fov = 0;
    DWORD FovAddr = FOV_ADDR;
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
    ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + FovAddr),
                        &fov, sizeof(DWORD), NULL);
    return formatDwordToFloat(fov);
}

float csscore::getMyFovLeft(HANDLE Process, DWORD PID)
{
    DWORD fov = 0;
    DWORD FovLeftAddr = FOV_LEFT_ADDR;
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
    ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + FovLeftAddr),
                        &fov, sizeof(DWORD), NULL);
    return formatDwordToFloat(fov);
}

int csscore::setMyFov(HANDLE Process, DWORD PID, float fov)
{
    DWORD FovAddr = FOV_ADDR;
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
    return WriteProcessMemory(Process, (LPVOID)(engineBaseAddr + FovAddr),
                              &fov, sizeof(DWORD), NULL);
}

int csscore::setMyFovLeft(HANDLE Process, DWORD PID, float fovleft)
{
    DWORD FovLeftAddr = FOV_LEFT_ADDR;
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
       return  ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + FovLeftAddr),
                        &fovleft, sizeof(DWORD), NULL);


}

int csscore::getPlayerNum(HANDLE Process ,DWORD PID)
{
    DWORD NUM = 0;
    DWORD playerNumAddr = PLAYER_NUM_ADDR;
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
    ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + playerNumAddr),
                        &NUM, sizeof(DWORD), NULL);
    return NUM;
}

int csscore::getPlayerPersonHP(HANDLE Process, DWORD PID, DWORD baseAddr)
{
    DWORD HPADDRVALUE=0;
    DWORD HPADDR2VALUE=0;
    DWORD serverBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"server.dll");
    ReadProcessMemory(Process, (LPVOID)(serverBaseAddr + baseAddr),
                        &HPADDRVALUE, sizeof(DWORD), NULL);
    ReadProcessMemory(Process,
                      (LPVOID)(HPADDRVALUE + HP_ADDR2),
                      &HPADDR2VALUE, sizeof(DWORD), NULL);
    int hp = *((int *)&HPADDR2VALUE);
    return hp;
}

int csscore::getMyHP(HANDLE Process, DWORD PID)
{
    DWORD MY_HP_ADDR=HP_ADDR;
    return getPlayerPersonHP(Process,PID,MY_HP_ADDR);
}

int csscore::setMyHP(HANDLE Process, DWORD PID, int hp)
{
    DWORD MY_HP_ADDR=HP_ADDR;
    return setPlayerPersonHP(Process,PID,MY_HP_ADDR, hp);
}

int csscore::setPlayerPersonHP(HANDLE Process, DWORD PID, DWORD baseAddr, int hp)
{
    DWORD HPADDRVALUE=0;
    DWORD serverBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"server.dll");
    ReadProcessMemory(Process, (LPVOID)(serverBaseAddr + baseAddr),
                        &HPADDRVALUE, sizeof(DWORD), NULL);
   return  WriteProcessMemory(Process,
                      (LPVOID)(HPADDRVALUE + HP_ADDR2),
                      &hp, sizeof(DWORD), NULL);
}

PERSONPOSITION csscore::getPlayerPersonPosition(HANDLE Process, DWORD PID, DWORD baseAddr)
{
    PERSONPOSITION p;
    DWORD PositionZAddr=POSITION_Z_ADDR;
    DWORD PositionXAddr=POSITION_X_ADDR;
    DWORD PositionYAddr=POSITION_Y_ADDR;

    DWORD PersonBaseAddr=0;
    DWORD serverBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"server.dll");
    ReadProcessMemory(Process, (LPVOID)(serverBaseAddr + baseAddr),
                        &PersonBaseAddr, sizeof(DWORD), NULL);
    ReadProcessMemory(Process, (LPVOID)(PersonBaseAddr + PositionZAddr),
                        &p.Z, sizeof(DWORD), NULL);
    ReadProcessMemory(Process, (LPVOID)(PersonBaseAddr + PositionXAddr),
                        &p.X, sizeof(DWORD), NULL);
    ReadProcessMemory(Process, (LPVOID)(PersonBaseAddr + PositionYAddr),
                        &p.Y, sizeof(DWORD), NULL);

    return  p;
}

matrixBoxCamera csscore::getCamera(HANDLE Process, DWORD PID,PERSONPOSITION p)
{
    matrixBoxCamera camera;
    DWORD MatrixBoxBaseAddr=MATRIX_BOX_BASE_ADDR;
    DWORD MatrixBoxBaseAddrValue=0;
    float MatrixBoxArray[4][4];
    DWORD engineBaseAddr=(DWORD)getModuleBaseAddrByProcessID(PID,"engine.dll");
    ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + MatrixBoxBaseAddr),
                        &MatrixBoxBaseAddrValue, sizeof(DWORD), NULL);
    ReadProcessMemory(Process, (LPVOID)(engineBaseAddr + MatrixBoxBaseAddr),
                        &MatrixBoxArray[0][0], 64, NULL);
//    qDebug() << formatDwordToFloat(MatrixBoxBaseAddrValue);
    MatrixBoxArray[0][2]=0;
//    for (int i =0;i<4;i++) {
//        for(int k =0;k<4;k++){
//            qDebug() << MatrixBoxArray[i][k] << i << " - " << k;
//        }
//    }
    RECT rectlp={0};
    int width=0,visionWidth=0;
    int height=0,visionHeight=0;
    HWND hWinmine = FindWindowW(NULL, L"Counter-Strike Source"); //找到窗口
    if(GetWindowRect(hWinmine,&rectlp) == NULL){
        qDebug() <<"GetWindowRect error ::: "<< GetLastError();
    }else{
        height=rectlp.bottom-rectlp.top;
        width=rectlp.right-rectlp.left;
        visionWidth=width/2;
        visionHeight=height/2;
        //qDebug() << " h :: " << height << " -- w :: " << width << "hhh : " << visionHeight << " ww : " << visionWidth;

        float x=formatDwordToFloat(p.X);
        float y=formatDwordToFloat(p.Y);
        float z=formatDwordToFloat(p.Z);
        camera.Z=MatrixBoxArray[2][0] * x+MatrixBoxArray[2][1]*y+MatrixBoxArray[2][2]*z+MatrixBoxArray[2][3];
        //qDebug() << "2 -0 " << MatrixBoxArray[2][0];
        float scale=1/camera.Z;
        //qDebug() << MatrixBoxArray[0][2] << " -- " << scale;
        if(camera.Z < 0){
            return camera;
         }
        float ww=0.52f;
        camera.X=visionWidth+(MatrixBoxArray[0][0]*x+MatrixBoxArray[0][1]*y+MatrixBoxArray[0][2]*z+MatrixBoxArray[0][3])*scale*visionWidth;
        camera.Y=visionHeight-(MatrixBoxArray[1][0]*x+MatrixBoxArray[1][1]*y+MatrixBoxArray[1][2]*(z)+MatrixBoxArray[1][3])*scale*visionHeight;
        camera.Y2=visionHeight-(MatrixBoxArray[1][0]*x+MatrixBoxArray[1][1]*y+MatrixBoxArray[1][2]*(z+73)+MatrixBoxArray[1][3])*scale*visionHeight;
        camera.BOX_H=camera.Y-camera.Y2;
        camera.BOX_W=camera.BOX_H*ww;
        camera.BOX_X=camera.X-camera.BOX_W/2;
        camera.WIN_H=rectlp.top;
        camera.WIN_W=rectlp.left;
        camera.G_H=height;
        camera.G_W=width;
    }
//     qDebug() << " h :: " << height << " -- w :: " << width;
    //qDebug() << "zzz :: "<<camera.Z << " xx :: " << camera.X << " yy :: " << camera.Y;
    return camera;
}

QList<PROCESSENTRY32> csscore::getAllProcess()
{
    QList<PROCESSENTRY32> mlist;
    HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        if(hProcessSnapshot != INVALID_HANDLE_VALUE){
           PROCESSENTRY32  pe32 = { 0 };
                pe32.dwSize = sizeof(PROCESSENTRY32);
                BOOL mb = Process32First(hProcessSnapshot,&pe32);
                while(mb){
                    mlist.append(pe32);
                    mb = Process32Next(hProcessSnapshot, &pe32);
                }

        }
        CloseHandle(hProcessSnapshot);
        return mlist;
}

int csscore::getPidByProcessName(QString processName)
{
    QList<PROCESSENTRY32W> allProcess = this->getAllProcess();

    foreach (PROCESSENTRY32W p32, allProcess) {
        QString name=QString::fromWCharArray(p32.szExeFile);
        unsigned int pid = p32.th32ProcessID;
        if(name==processName){
            return pid;
        }
    }
    return -1;
}

QList<MODULEENTRY32W> csscore::getProcessByModules(int pid)
{
    QList<MODULEENTRY32W> mlist;
    HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pid);
        if(hProcessSnapshot != INVALID_HANDLE_VALUE){
           MODULEENTRY32W  me32 = { 0 };
                me32.dwSize = sizeof(MODULEENTRY32W);
                BOOL mb = Module32First(hProcessSnapshot,&me32);
                while(mb){
                    mlist.append(me32);
                    mb = Module32Next(hProcessSnapshot, &me32);
                }

        }
        CloseHandle(hProcessSnapshot);
        return mlist;
}

BYTE *csscore::getModuleBaseAddrByProcessID(int processID, QString moduleName)
{
    if(processID > -1){
        QList<MODULEENTRY32W> processByModules = this->getProcessByModules(processID);
        foreach(MODULEENTRY32W m32,processByModules){
            QString name=QString::fromWCharArray(m32.szModule);
            if(moduleName == name){
                return m32.modBaseAddr;
            }
        }

    }
    return 0;
}

BYTE * csscore::getByProcessModuleBaseAddr(QString processName, QString moduleName)
{
    int pid=this->getPidByProcessName(processName);
    return this->getModuleBaseAddrByProcessID(pid,moduleName);

}
