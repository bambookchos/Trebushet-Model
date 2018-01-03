#ifndef TREBUSHET_H
#define TREBUSHET_H


#include "model.h"
#include "matrix.h"
#include "barrel.h"

class Trebushet
{

public:
    Trebushet();

    void tick(int time, Barrel *barrel);
    void fire();
        void reboot();
    bool visible;
    void calculateShoot(double angel);


    Model *trebushet_top;
    Model *trebushet_bottom;
    QMatrix4x4 model_bottom;
    QMatrix4x4 model_top;
    QVector3D position;
    bool trebushet_rotate;
    double *m;
    double m1;
    double m2;


private:
    int start_time;
    double rotate[3];
    double scale[3];
    double stick_angel;
    double vt;
    double l1;
    double l2;
    double shoot_angel;
};

#endif // TREBUSHET_H
