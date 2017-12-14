#include "bullet.h"

bullet::bullet()
{
    m = 10;
    F = QVector3D(0,-m*9.8,0);
    a = F/m;
    position = QVector3D(0,0,0);
    V = QVector3D(0,700,-900);
}
void bullet::tick(){
    if (position.y()>=0){
        a = F/m;
        V+=a;
        position+=V*0.0001;
    }
    else{
        V = QVector3D(0,0,0);
    }
}
