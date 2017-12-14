#ifndef BULLET_H
#define BULLET_H
#include <QVector3D>


class bullet
{
public:
    bullet();
    void tick();
    QVector3D F,a,V,position;
    double m;

};

#endif // BULLET_H
