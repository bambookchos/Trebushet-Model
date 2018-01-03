#ifndef BARREL_H
#define BARREL_H

#include "model.h"
#include "ground.h"
#include "matrix.h"


class Barrel
{

public:
    Barrel();
    void tick(int time, Ground *ground);

    QVector3D position;
    QMatrix4x4 model;
    Model *barrel;
    bool visible;
    bool enable_boom;


private:
    int last_time;
    double scale[3];
    double rotate[3];
    QVector3D F,a,V;
    bool fire_now;
    double start_speed;
public:
    double seesaw_angel;
    void fired(double velocity,  double shoot_angel);

    void reboot();

};

#endif // BARREL_H
