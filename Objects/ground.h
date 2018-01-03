#ifndef GROUND_H
#define GROUND_H

#include "model.h"
#include "matrix.h"


class Ground
{
public:
    Ground();

    QVector3D position;
    QMatrix4x4 model;
    Model *ground;
    bool visible;

private:
    double rotate[3];
    double scale[3];
};

void generate_ground(std::ofstream &InputFile, double size_x, double size_y, double step,  qreal min_z, qreal max_z);
#endif // GROUND_H
