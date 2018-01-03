#include "ground.h"

Ground::Ground()
{
    visible = true;
    ground = new Model("/Users/yadotrof/Desktop/Drawer/ground.obj");
    position = QVector3D(0,-0.05,0);
    rotate[0] = 90;
    rotate[1] = 0;
    rotate[2] = 0;
    scale[0] = 1;
    scale[1] = 1;
    scale[2] = 1;
    ground->color[0] = 20;
    ground->color[1] = 230;
    ground->color[2] = 20;

    model = matrix_delta(position.x(),position.y(),position.z())*
            matrix_scale(scale[0],scale[1],scale[2]) *
            rotate_matrix_x2(rotate[0])*
            rotate_matrix_y2(rotate[1])*
            rotate_matrix_z2(rotate[2]);

}
void generate_ground(std::ofstream &InputFile, double size_x, double size_y, double step,  qreal min_z, qreal max_z)
{
    if (InputFile.is_open())
    {
        for (int i=0; i < size_x; i++){
            for (int j=0; j < size_y; j++){
                InputFile << "v " << j*step-step*size_x/2<< " "<< i*step-step*size_y/2 <<" "<< min_z + ((double)rand() / RAND_MAX)* (max_z-min_z) << "\n";
            }
        }

        for (int i=0; i < size_x-1; i++){
            for (int j=0; j < size_y-1; j++){

                InputFile << "f " << size_x*i + (j+1)  <<"/1/1 " <<  size_x*i + (j+2) << "/1/1 "<<  size_x*(i+1)+(j+1)  << "/1/1\n";

                InputFile << "f " << size_x*(i+1) + (j+2)  <<"/1/1 " <<  size_x*(i+1) + (j+1) << "/1/1 "<<  size_x*(i)+(j+2)  << "/1/1\n";
            }
        }
    }
}
\
