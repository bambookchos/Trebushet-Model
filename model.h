#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <fstream>
#include <iostream>
#include <string>
#include "model.h"
#include "face.h"
#include "ground.h"
using namespace std;

class Model
{
public:
    Model(string file_name);
    Model();

    void load_obj(string file_name);
    double scale_x;
    double scale_y;
    double scale_z;
    QVector3D *v_array, *vn_array;
    Face *f_array;
    int num_of_v;
    int num_of_f;
    int num_of_vn;

    int rotate_x;
    int rotate_y;
    int rotate_z;
    double dx;
    double dy;
    double dz;

    int color[3];

private:
};
#endif // MODEL_H
