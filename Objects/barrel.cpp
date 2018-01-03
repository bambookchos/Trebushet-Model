#include "barrel.h"

Barrel::Barrel()
{
    enable_boom = false;
    visible = true;
    last_time = 0;
    //    a = QVector3D(0,-9.8,0);
    a = QVector3D(0,-9.8,0);
    position = QVector3D(0,0,0);
    V = QVector3D(0,8,-8);

    barrel = new Model("/Users/yadotrof/Desktop/Drawer/barrel.obj");
    rotate[0] = 0;
    rotate[1] = 0;
    rotate[2] = 0;
    scale[0] = 0.1;
    scale[1] = 0.1;
    scale[2] = 0.1;
    barrel->color[0] = 130;
    barrel->color[1] = 82;
    barrel->color[2] = 20;
    seesaw_angel = -30;
    position = rotate_matrix_x2(seesaw_angel)*position * QVector3D(0,0,5*scale[0])+ QVector3D(0,3.1*scale[1],0);
    model = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[2]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);
    fire_now = false;
}

void Barrel::tick(int time, Ground *ground){
    if (last_time ==0){
        last_time = time;
    }
    if (fire_now){
        double range;
        double x = position.x();
        double y = position.y();
        double z = position.z();
        double min_range = sqrt(pow((x-ground->ground->v_array[0].x()),2)+pow((y-ground->ground->v_array[0].y()),2));
        double min_range2 = sqrt(pow((x-ground->ground->v_array[1].x()),2)+pow((y-ground->ground->v_array[1].y()),2));
        double min_range3 = sqrt(pow((x-ground->ground->v_array[2].x()),2)+pow((y-ground->ground->v_array[2].y()),2));

        int g = 0;
        int g2 = 1;
        int g3 = 2;

        if (min_range>min_range2){ std::swap(min_range, min_range2); std::swap(g, g2);}
        if (min_range>min_range3){ std::swap(min_range, min_range3); std::swap(g, g3);}
        if (min_range2>min_range3){ std::swap(min_range2, min_range3); std::swap(g2, g3);}




        for (int g_v = 3; g_v < ground->ground->num_of_v; g_v++){
            range = sqrt(pow((x-(ground->model*ground->ground->v_array[g_v]).x()),2)+pow((z-(ground->model*ground->ground->v_array[g_v]).z()),2));
            if (range < min_range){
                min_range = range;
                g3=g2;
                g2=g;
                g = g_v;
            }
            else if (range < min_range2){
                min_range2 = range;
                g3=g2;
                g2 = g_v;
            }
            else if (range < min_range3){
                min_range3 = range;
                g3 = g_v;
            }
        }
        cout << g << " " << g2 << " " << g3 << endl;

        QVector3D t0 = ground->model*ground->ground->v_array[g];
        QVector3D t1 = ground->model*ground->ground->v_array[g2];
        QVector3D t2 = ground->model*ground->ground->v_array[g3];
        if (position.y()>(t0.y()+t1.y()+t2.y())/3){
            double dt = time-last_time;
            V+=a*dt/1000*TIME_COEF;
            position+=V*dt/1000*TIME_COEF*0.1;
        }
        else{
            enable_boom = true;
        }
    }
    else{
        position = rotate_matrix_x2(seesaw_angel)*QVector3D(0,0,5*scale[0]) + QVector3D(0,3.1*scale[1],0);
    }

    last_time = time;


    model = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[2]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);
    //    cout << position.z()<< endl;

}

void Barrel::fired(double velocity, double shoot_angel){
    if (!fire_now){
        fire_now= true;
        start_speed = velocity;
        cout << start_speed<< endl;
        V = rotate_matrix_x2(-shoot_angel)*QVector3D(0,0,start_speed);
        position = rotate_matrix_x2(90-shoot_angel)*QVector3D(0,0,5*scale[0]) + QVector3D(0,3.1*scale[1],0);
    }
}

void Barrel::reboot(){
    last_time = 0;
    position = QVector3D(0,0,0);

    seesaw_angel = -30;
    position = rotate_matrix_x2(seesaw_angel)*position * QVector3D(0,0,5*scale[0])+ QVector3D(0,3.1*scale[1],0);
    model = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[2]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);
    fire_now = false;
    enable_boom = false;
}


