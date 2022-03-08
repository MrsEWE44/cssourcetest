#include "personposition.h"

PERSONPOSITION::PERSONPOSITION()
{

}

int PERSONPOSITION::operator==(const PERSONPOSITION &p)
{
    if(this->X == p.X && this->Y == p.Y && this->Z == p.Z){
        return 0;
    }
    return 1;
}
