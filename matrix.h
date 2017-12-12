#ifndef MATRIX_H
#define MATRIX_H
#include "model.h"
#include <QVector3D>

#include <math.h>
#include <QMatrix4x4>
//#include <QGenericMatrix>



//int sravn(const void *a,const  void *b);
QMatrix4x4 rotate_matrix_x2(double alpha);
QMatrix4x4 rotate_matrix_y2(double alpha);
QMatrix4x4 rotate_matrix_z2(double alpha);
QMatrix4x4 matrix_scale(double x, double y, double z);
QMatrix4x4 matrix_delta(double x, double y, double z);
QMatrix4x4 matrix_perspective(double c);
QMatrix4x4 my_viewport(double w, double h, double d, double x, double y);
#endif // MATRIX_H
