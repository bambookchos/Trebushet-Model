#include "trebushet.h"

Trebushet::Trebushet()
{
    visible = true;
    trebushet_bottom = new Model("/Users/yadotrof/Desktop/Drawer/trebushet_bottom.obj");
    trebushet_top = new Model("/Users/yadotrof/Desktop/Drawer/trebushet_top.obj");
    position = QVector3D(0,0,0);
    rotate[0] = 0;
    rotate[1] = 180;
    rotate[2] = 0;
    scale[0] = 0.1;
    scale[1] = 0.1;
    scale[2] = 0.1;

    m1 = 8000;
    m2 = 40;
    l1 = 1;
    l2 = 5;

    trebushet_rotate = false;

    trebushet_bottom->color[0] = 130;
    trebushet_bottom->color[1] = 82;
    trebushet_bottom->color[2] = 20;

    trebushet_top->color[0] = 130;
    trebushet_top->color[1] = 82;
    trebushet_top->color[2] = 20;

    model_bottom = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);


    model_top = matrix_delta(position.x(),position.y()+3*scale[1],position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2])*
            rotate_matrix_x2(stick_angel);

    m = new double[100000];
    start_time = -1;
    stick_angel = 30;
    shoot_angel = 45;
    calculateShoot(shoot_angel);
}



void Trebushet::tick(int time, Barrel *barrel){

    if (trebushet_rotate==true){
        if (start_time == -1){
            start_time = time;
        }

    stick_angel = m[time-start_time];


   if (stick_angel> -(90-shoot_angel)){
       barrel->seesaw_angel = -stick_angel;
    }
   else{
       barrel->fired(vt*l2, shoot_angel);
//       cout << shoot_angel << " " << stick_angel<< endl;

   }
  }

    model_bottom = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);


    model_top = matrix_delta(position.x(),position.y()+3*scale[1],position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2])*
            rotate_matrix_x2(stick_angel);
}

void Trebushet::calculateShoot(double angel){
    double ac = 0;
    double v = 0;
    shoot_angel = angel;
    m[0] = 30;
    bool founded =false;
    for (int i =1; i< 100000; i++){
        if (founded){
            ac = (m1*l1)/(m1*l1*l1)*9.8*cos(m[i-1]*3.1415/180);

        }
        else {
        ac = (m1*l1-m2*l2)/(m1*l1*l1+m2*l2*l2)*9.8*cos(m[i-1]*3.1415/180);
        }
        v -= ac/1000;
        m[i]=m[i-1]+v*180/3.1415/1000;
        if (m[i]<-angel && !founded){
            founded = true;
            vt = v;
        }
    }
}


void Trebushet::reboot(){
    position = QVector3D(0,0,0);

    trebushet_rotate = false;

    model_bottom = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);


    model_top = matrix_delta(position.x(),position.y()+3*scale[1],position.z())*
            matrix_scale(scale[0],scale[1],scale[0]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2])*
            rotate_matrix_x2(stick_angel);
    calculateShoot(shoot_angel);
    start_time = -1;
    stick_angel = 30;
}
