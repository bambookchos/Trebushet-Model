#include "matrix.h"







QMatrix4x4 rotate_matrix_x2(double alpha){
    double alpha_in_rad = M_PI/180*alpha;


    QMatrix4x4  rm;
    rm(0,0)= 1; rm(0,1)= 0;                 rm(0,2)= 0;                     rm(0,3)= 0;
    rm(1,0)= 0; rm(1,1)= cos(alpha_in_rad); rm(1,2)= sin(alpha_in_rad);    rm(1,3)= 0;
    rm(2,0)= 0; rm(2,1)= -sin(alpha_in_rad); rm(2,2)= cos(alpha_in_rad);     rm(2,3)= 0;
    rm(3,0)= 0; rm(3,1)= 0;                 rm(3,2)= 0;                     rm(3,3)= 1;
    return rm;
}

QMatrix4x4 rotate_matrix_y2(double alpha){
    double alpha_in_rad = M_PI/180*alpha;


    QMatrix4x4  rm;
    rm(0,0)= cos(alpha_in_rad); rm(0,1)= 0;     rm(0,2)= sin(alpha_in_rad);      rm(0,3)= 0;
    rm(1,0)= 0;                 rm(1,1)= 1;     rm(1,2)= 0;                      rm(1,3)= 0;
    rm(2,0)= -sin(alpha_in_rad); rm(2,1)= 0;     rm(2,2)= cos(alpha_in_rad);     rm(2,3)= 0;
    rm(3,0)= 0;                  rm(3,1)= 0;     rm(3,2)= 0;                     rm(3,3)= 1;
    return rm;
}


QMatrix4x4 rotate_matrix_z2(double alpha){
    double alpha_in_rad = M_PI/180*alpha;


    QMatrix4x4  rm;
    rm(0,0)= cos(alpha_in_rad); rm(0,1)= sin(alpha_in_rad);                 rm(0,2)= 0;                     rm(0,3)= 0;
    rm(1,0)= -sin(alpha_in_rad); rm(1,1)= cos(alpha_in_rad); rm(1,2)= 0;    rm(1,3)= 0;
    rm(2,0)= 0; rm(2,1)= 0; rm(2,2)= 1;     rm(2,3)= 0;
    rm(3,0)= 0; rm(3,1)= 0;                 rm(3,2)= 0;                     rm(3,3)= 1;
    return rm;
}


QMatrix4x4 matrix_scale(double x, double y, double z){


    QMatrix4x4  rm;
    rm(0,0)= x; rm(0,1)= 0; rm(0,2)= 0;  rm(0,3)= 0;
    rm(1,0)= 0; rm(1,1)= y; rm(1,2)= 0;  rm(1,3)= 0;
    rm(2,0)= 0; rm(2,1)= 0; rm(2,2)= z;  rm(2,3)= 0;
    rm(3,0)= 0; rm(3,1)= 0; rm(3,2)= 0;  rm(3,3)= 1;
    return rm;
}

QMatrix4x4 matrix_delta(double x, double y, double z){


    QMatrix4x4  rm;
    rm(0,0)= 1; rm(0,1)= 0; rm(0,2)= 0;  rm(0,3)= x;
    rm(1,0)= 0; rm(1,1)= 1; rm(1,2)= 0;  rm(1,3)= y;
    rm(2,0)= 0; rm(2,1)= 0; rm(2,2)= 1;  rm(2,3)= z;
    rm(3,0)= 0; rm(3,1)= 0; rm(3,2)= 0;  rm(3,3)= 1;
    return rm;
}


QMatrix4x4 matrix_perspective(double c){


    QMatrix4x4  rm;
    rm(0,0)= 1; rm(0,1)= 0; rm(0,2)= 0;  rm(0,3)= 0;
    rm(1,0)= 0; rm(1,1)= 1; rm(1,2)= 0;  rm(1,3)= 0;
    rm(2,0)= 0; rm(2,1)= 0; rm(2,2)= 1;  rm(2,3)= 0;
    rm(3,0)= 0; rm(3,1)= 0; rm(3,2)= -1/c;  rm(3,3)= 1;
    return rm;
}




QMatrix4x4 my_viewport(double w, double h, double d, double x, double y){


    QMatrix4x4  rm;
    rm(0,0)= w/2; rm(0,1)= 0; rm(0,2)= 0;  rm(0,3)= x+w/2;
    rm(1,0)= 0; rm(1,1)= h/2; rm(1,2)= 0;  rm(1,3)= y+h/2;
    rm(2,0)= 0; rm(2,1)= 0; rm(2,2)= d/2;  rm(2,3)= d/2;
    rm(3,0)= 0; rm(3,1)= 0; rm(3,2)= 0;  rm(3,3)= 1;
    return rm;
}



