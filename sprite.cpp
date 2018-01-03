#include "sprite.h"

Sprite::Sprite(QObject *parent) :
    QObject(parent)
{
    for (int i=0; i<31;i++){
        QString name = ":/sprites/exp08_00"+QString::number(i+1)+".png";
        spriteImage[i] = new QPixmap(name);
    }
}
