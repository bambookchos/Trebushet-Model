#include "ground.h"

ground::ground()
{

}
void ground::generate_ground(std::ofstream &InputFile, int size_x, int size_y, qreal min_z, qreal max_z)
{


    if (InputFile.is_open())
      {
        for (int i=0; i < size_x; i++){
            for (int j=0; j < size_y; j++){
                InputFile << "v " << j*0.2-2 << " "<< i*0.2-2 <<" "<< min_z + ((double)rand() / RAND_MAX)* (max_z-min_z) << "\n";
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
