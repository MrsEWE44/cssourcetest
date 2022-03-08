#ifndef CSSCORE_H
#define CSSCORE_H

#include <QList>

#include <Windows.h>
#include "personposition.h"
#include "matrixboxcamera.h"

#ifndef PSAPI_ VERSION
#define PSAPI_ VERSION 1
#endif

#include <Tlhelp32.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")


#define PLAYER_NUM_ADDR 0x5D29BC
#define POSITION_BASE_ADDR 0x4F2FEC
#define POSITION_Z_ADDR 0x288
#define POSITION_Y_ADDR 0x284
#define POSITION_X_ADDR 0x280
#define POSITION_NEXT_PERSON_ADDR 0x10
#define MATRIX_BOX_BASE_ADDR 0x596EF0
#define HP_ADDR POSITION_BASE_ADDR
#define HP_ADDR2 0xE4
#define FOV_ADDR 0x4622CC
#define FOV_LEFT_ADDR 0x4622D0


class csscore
{
public:
    csscore();
    QList<PROCESSENTRY32> getAllProcess();
    int getPidByProcessName(QString processName);
    QList<MODULEENTRY32> getProcessByModules(int pid);
    BYTE * getModuleBaseAddrByProcessID(int processID,QString moduleName);
    BYTE * getByProcessModuleBaseAddr(QString processName,QString moduleName);
    void formatPrintPosition(PERSONPOSITION p);
    float formatDwordToFloat(DWORD w);
    float formatFloatToTwoLen(float f);
    double formatDwordToDouble(DWORD w);
    float getMyFov(HANDLE Process,DWORD PID);
    float getMyFovLeft(HANDLE Process,DWORD PID);
    int setMyFov(HANDLE Process,DWORD PID,float fov);
    int setMyFovLeft(HANDLE Process,DWORD PID,float fovleft);
    int getPlayerNum(HANDLE Process,DWORD PID);
    int getPlayerPersonHP(HANDLE Process,DWORD PID,DWORD baseAddr);
    int getMyHP(HANDLE Process,DWORD PID);
    int setMyHP(HANDLE Process,DWORD PID,int hp);
    int setPlayerPersonHP(HANDLE Process,DWORD PID,DWORD baseAddr,int hp);
    PERSONPOSITION getPlayerPersonPosition(HANDLE Process,DWORD PID,DWORD baseAddr);
    matrixBoxCamera getCamera(HANDLE Process,DWORD PID,PERSONPOSITION p);


};

#endif // CSSCORE_H
