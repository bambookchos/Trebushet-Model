#include "model.h"


Model::Model(){
}

Model::Model(string file_name)
{
    this->load_obj(file_name);
}


void Model::load_obj(string file_name){

    ifstream InputFile(file_name);

    string  line;

    //Get amout of faces and vertexes
    int v=0,f=0,vn=0;
    if (InputFile.is_open())
      {
        while ( getline(InputFile,line) )
        {
            if (line[0]=='v' && line[1]==' '){
                v+=1;
            }
            if (line[0]=='v' && line[1]=='n'&& line[2]==' '){
                vn+=1;
            }

            if (line[0]=='f'){
                f+=1;
            }
        }
      }

    num_of_f = f;
    num_of_v = v;
    num_of_vn = vn;
    v_array = new QVector3D[v];
    vn_array = new QVector3D[vn];
    f_array = new Face[f];



    v=0, f=0, vn=0;

    InputFile.clear();
    InputFile.seekg(0);
    size_t pos = 0;
    size_t n =0;
    while ( getline(InputFile,line) )
    {
        if (line[0]=='v' && line[1]==' '){
            for (int i = 0; (i < 4)
                 ; i++) {
                pos = line.find(' ');
                string token = line.substr(0, pos);
//                cout << token << " " << i << endl;
                if (i == 1){
                    v_array[v].setX(stod(token,&n));
                }
                if (i == 2){
                    v_array[v].setY(stod(token,&n));
                }
                if (i == 3){
                    v_array[v].setZ(stod(token,&n));
                }
                line.erase(0, pos + 1);
            }
            v+=1;
        }
        if (line[0]=='v' && line[1]=='n'&& line[2]==' '){
            for (int i = 0; (i < 4)
                 ; i++) {
                pos = line.find(' ');
                string token = line.substr(0, pos);
//                cout << token << " " << i << endl;
                if (i == 1){
                    vn_array[vn].setX(stod(token,&n));
                }
                if (i == 2){
                    vn_array[vn].setY(stod(token,&n));
                }
                if (i == 3){
                    vn_array[vn].setZ(stod(token,&n));
                }
                line.erase(0, pos + 1);
            }
            vn+=1;
        }

        if (line[0]=='f'){
            string token;
            for (int i = 0; (i < 4); i++) {
                pos = line.find(' ');
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                if (i!= 0){
                    pos = token.find('/');
                    string face_n = token.substr(0, pos);
                    f_array[f].point_num[i-1] = stoi(face_n, &n)-1;
                }
            }

            f+=1;

        }
    }
    InputFile.close();



}
