#include "paintwidget.h"
#include <QRgb>
#include <QGraphicsPixmapItem>

#define S_WIDTH 600
#define S_HEIGHT 600

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)



{
    zbuffer = new int[S_WIDTH*S_HEIGHT];

    //MOVEABLE OBJECT
    checked_barel = false;
    checked_ground = false;
    checked_trebushet = false;
    trebushet_angel=0;


    //CAMERA INIT SETTINGS
    camera_z =3;
    camera_x = 3;
    camera_y =3;

    target.setX(0);
    target.setY(0);
    target.setZ(0);

    //GENERATE GROUND
    ofstream Out("/Users/yadotrof/Desktop/Drawer/build-persistent_paint-Desktop_Qt_5_9_1_clang_64bit-Debug/ground.obj");
    ground a;
    a.generate_ground(Out,20,20,-0.05,0.05);
    Out.close();


    //LOAD MODELS
    mod = new Model[4];
    mod[2].load_obj("/Users/yadotrof/Desktop/Drawer/trebushet_bottom.obj");
    mod[2].color[0]=130;
    mod[2].color[1]=82;
    mod[2].color[2]=20;
    mod[2].scale_x = 0.2;
    mod[2].scale_y = 0.2;
    mod[2].scale_z = 0.2;
    mod[3].load_obj("/Users/yadotrof/BMSTU/CG/Course/build-CourseProject-Desktop_Qt_5_9_1_MinGW_32bit-Debug/models/1.obj");
    mod[3].color[0]=130;
    mod[3].color[1]=82;
    mod[3].color[2]=20;
    mod[3].scale_x = 0.2;
    mod[3].scale_y = 0.2;
    mod[3].scale_z = 0.2;
    mod[1].load_obj("/Users/yadotrof/Desktop/Drawer/trebushet_top.obj");
    mod[1].color[0]=130;
    mod[1].color[1]=82;
    mod[1].color[2]=20;
    mod[1].scale_x = 0.2;
    mod[1].scale_y = 0.2;
    mod[1].scale_z = 0.2;
    mod[1].dy= 0.6;
    mod[0].load_obj("/Users/yadotrof/Desktop/Drawer/build-persistent_paint-Desktop_Qt_5_9_1_clang_64bit-Debug/ground.obj");
    mod[0].rotate_x=90;
    mod[0].color[0]=20;
    mod[0].color[1]=200;
    mod[0].color[2]=20;
    mod[0].scale_x=10;
    mod[0].scale_y=10;
    mod[0].scale_z=10;


    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    scene->setSceneRect(0, 0, S_WIDTH, S_HEIGHT);
    this->setScene(scene);          // Устанавливаем сцену в виджет

    timer = new QTimer();               // Инициализируем Таймер
    // Подключаем СЛОТ для отрисовки к таймеру
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));

    timer->start(0);                   // Стартуем таймер на 50 миллисекунд
    trebushet_rotate = true;
    barrel_speed = false;


    barrel = new bullet;
}


MyGraphicView::~MyGraphicView()
{

}

void MyGraphicView::slotAlarmTimer()
{

    //////////INIT FRAME
    QImage img(S_WIDTH,S_HEIGHT,QImage::Format_RGB32);
    img.fill(qRgb(200,200,200));

    for (size_t i = 0; i < S_WIDTH*S_HEIGHT; i++){
        zbuffer[i] = INT_MAX;
    }



    camera_y+=0.02;
        camera_x+=0.02;

    //////////ANIMATION
    if (trebushet_angel<-60 || trebushet_angel>45)
        trebushet_rotate = !trebushet_rotate;

    if (trebushet_rotate==true){
        trebushet_angel+=6;
    }
    else {
        trebushet_angel-=6;
    }


    if (barrel_speed){
        //        cout << barrel->position.x() << " " << barrel->position.y() << " " << barrel->position.z() << endl;
        barrel->tick();
        mod[3].dx = barrel->position.x();
        mod[3].dy = barrel->position.y();
        mod[3].dz = barrel->position.z();
    }




    ///////////TRANSFORM MATRIXS, SOME VARIABLE
    QVector3D camera(camera_y,camera_x,camera_z);
    QVector3D up(0,1,0);
    QVector3D light(1,-0.75,-1);
    light.normalize();


    QMatrix4x4 lookat_matrix;
    //    lookat_matrix.lookat_matrixAt(camera, target, up);
    lookat_matrix.lookAt(camera+barrel->position, barrel->position, up);

    QMatrix4x4 viewport_perspective_matrix;
    viewport_perspective_matrix.viewport(0,0,S_WIDTH,S_HEIGHT,1,100000);
    viewport_perspective_matrix.perspective(60,1,1,100000);





    for (int m = 0; m < 4; m++ ){
        int color_r = mod[m].color[0];
        int color_g = mod[m].color[1];
        int color_b = mod[m].color[2];
        QMatrix4x4 model_matrix;
        if (m==1){
            model_matrix = matrix_delta(mod[m].dx,mod[m].dy,mod[m].dz)*matrix_scale(mod[m].scale_x,mod[m].scale_y,mod[m].scale_z) *rotate_matrix_x2(mod[m].rotate_x)*rotate_matrix_y2(mod[m].rotate_y)*rotate_matrix_z2(mod[m].rotate_z)*rotate_matrix_x2(trebushet_angel);
        }
        else{
            model_matrix = matrix_delta(mod[m].dx,mod[m].dy,mod[m].dz)*matrix_scale(mod[m].scale_x,mod[m].scale_y,mod[m].scale_z)*rotate_matrix_x2(mod[m].rotate_x)*rotate_matrix_y2(mod[m].rotate_y)*rotate_matrix_z2(mod[m].rotate_z);
        }
        QMatrix4x4 lookat_matrix_model_matrix = lookat_matrix*model_matrix;

        /////VARIABLES FOR FACE DRAW
        ///
        QVector3D t0,t1,t2,normal;
        double temp_light_intensive;

        for (int i = 0; i < mod[m].num_of_f;i++){


            t0 = mod[m].v_array[ mod[m].f_array[i].point_num[0] ];
            t1 = mod[m].v_array[ mod[m].f_array[i].point_num[1] ];
            t2 = mod[m].v_array[ mod[m].f_array[i].point_num[2] ];





            t0 = lookat_matrix_model_matrix*t0;
            t1 = lookat_matrix_model_matrix*t1;
            t2 = lookat_matrix_model_matrix*t2;


            //LIGHT
            normal  = QVector3D::crossProduct(t0 - t2,t0 - t1).normalized();
            temp_light_intensive = QVector3D::dotProduct(normal,light);
            if (temp_light_intensive < 0)  temp_light_intensive = 0;


            t0 = viewport_perspective_matrix* t0;
            t1 = viewport_perspective_matrix* t1;
            t2 = viewport_perspective_matrix* t2;

//            normal  = QVector3D::crossProduct(t0 - t2,t0 - t1).normalized();
//            if (QVector3D::dotProduct(normal,target-camera) > 0 ) continue;


            //            normal  = QVector3D::crossProduct(t0 - t1,t0 - t2).normalized();
            //            if (QVector3D::dotProduct(normal,target-camera)< 0) continue;

            p0[0] = t0.x(); p1[0] = t1.x(); p2[0] = t2.x();
            p0[1] = t0.y(); p1[1] = t1.y(); p2[1] = t2.y();
            p0[2] = t0.z(); p1[2] = t1.z(); p2[2] = t2.z();

            //IF FACE HAVE NO VERTEX IN SCREEN AREA
            if (!(((p0[0]>=0 && p0[0]<=S_WIDTH) && (p0[1]>=0 && p0[1]<=S_HEIGHT)) || ((p1[0]>=0 && p1[0]<=S_WIDTH) && (p1[1]>=0 && p1[1]<=S_HEIGHT)) || ((p2[0]>=0 && p2[0]<=S_WIDTH) && (p2[1]>=0 && p2[1]<=S_HEIGHT)))) continue;



            if (p0[1]==p1[1] && p0[1]==p2[1]) continue; // i dont care about degenerate triangles


            // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
            if (p0[1]>p1[1]) std::swap(p0, p1);
            if (p0[1]>p2[1]) std::swap(p0, p2);
            if (p1[1]>p2[1]) std::swap(p1, p2);


            total_height = p2[1]-p0[1];


            face_color= qRgb(temp_light_intensive*color_r,temp_light_intensive*color_g,temp_light_intensive*color_b);


            for (int h=0; h<total_height; h++) {
                second_half = h>p1[1]-p0[1] || p1[1]==p0[1];
                segment_height = second_half ? p2[1]-p1[1] : p1[1]-p0[1];
                alpha = (float)h/total_height;
                beta  = (float)(h-(second_half ? p1[1]-p0[1] : 0))/segment_height; // be careful: with above conditions no division by zero here
                //                A =               t0 + (t2-t0)*alpha;
                A[0]=p0[0] + ((p2[0]-p0[0])*alpha+.5f);
                A[1]=p0[1] + ((p2[1]-p0[1])*alpha+.5f);
                A[2]=p0[2] + ((p2[2]-p0[2])*alpha+.5f);
                //                B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
                if (second_half){
                    B[0]=p1[0] + ((p2[0]-p1[0])*beta+.5f);
                    B[1]=p1[1] +  ((p2[1]-p1[1])*beta+.5f);
                    B[2]=p1[2] + ((p2[2]-p1[2])*beta+.5f);
                }
                else{
                    B[0]=p0[0] +  ((p1[0]-p0[0])*beta+.5f);
                    B[1]=p0[1] + ((p1[1]-p0[1])*beta+.5f);
                    B[2]=p0[2] + ((p1[2]-p0[2])*beta+.5f);
                }
                if (A[0]>B[0]) std::swap(A, B);
                for (int j=A[0]; j<=B[0]; j++) {
                    phi = B[0]==A[0] ? 1. : (float) (j-A[0])/(float)(B[0]-A[0]);
                    //                    P = A + (B-A)*phi;
                    P[0]=A[0] +  ((B[0]-A[0])*phi+.5f);
                    P[1]=A[1] + ((B[1]-A[1])*phi+.5f);
                    P[2]=A[2] + ((B[2]-A[2])*phi+.5f);
                    if (P[0] < 0 || P[0]>=S_WIDTH || P[1]<0 || P[1]>=S_HEIGHT) continue;
                    idx = (P[0])+(P[1])*S_WIDTH;
                    //                    cout << P[2] <<endl;
                    if (zbuffer[idx]>P[2])
                    {
                        zbuffer[idx] = P[2];
                        img.setPixel(P[0], S_HEIGHT-P[1]-1,face_color); // attention, due to int casts t0.y+i != A.y
                    }
                }
            }
        }
    }



    QPixmap map = QPixmap::fromImage(img);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(map);


    this->deleteItemsFromGroup();
    scene->addItem(item);
}


void MyGraphicView::deleteItemsFromGroup()
{
    foreach( QGraphicsItem *item, scene->items()) {
        delete item;
    }
}

