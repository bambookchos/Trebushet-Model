#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <fstream>
#include <iostream>
#include <string>
#include "face.h"

#define TIME_COEF 1/1
using namespace std;

class Model
{
public:
    Model(string file_name);
    Model();
    void load_obj(string file_name);

    QVector3D *v_array, *vn_array;
    Face *f_array;
    int num_of_v;
    int num_of_f;
    int num_of_vn;
    int color[3];

private:
};
#endif // MODEL_H
