#ifndef GROUND_H
#define GROUND_H
#include <fstream>
#include <iostream>
#include <string>
#include <QVector3D>

class ground
{
public:
    ground();
    void generate_ground(std::ofstream &InputFile, int size_x, int size_y, qreal min_z, qreal max_z);

private:
    QVector3D *coords;
    int *faces;

};

#endif // GROUND_H
