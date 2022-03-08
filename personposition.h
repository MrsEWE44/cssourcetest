#ifndef PERSONPOSITION_H
#define PERSONPOSITION_H

#include <Windows.h>

class PERSONPOSITION
{
public:
    PERSONPOSITION();
    int operator==(const PERSONPOSITION& p);
public:
    DWORD X;
    DWORD Y;
    DWORD Z;
};

#endif // PERSONPOSITION_H
