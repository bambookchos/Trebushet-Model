#include "paintwidget.h"
#include <QRgb>
#include <QGraphicsPixmapItem>

#define S_WIDTH 850
#define S_HEIGHT 850

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)

{
    checked_ground = false;
    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;
    zbuffer = new int[S_WIDTH*S_HEIGHT];
    mod = new Model[3];
    camera_z = 0;
    camera_x = 0;
    camera_y = 0;
    target.setX(0);
    target.setY(0);
    target.setZ(0);
    ofstream Out("/Users/yadotrof/Desktop/Drawer/build-persistent_paint-Desktop_Qt_5_9_1_clang_64bit-Debug/ground.obj");


    checked_barel = false;
    checked_ground = false;
    checked_trebushet = false;

    ground a;
    a.generate_ground(Out,20,20,-0.05,0.05);
    Out.close();

    mod[2].load_obj("/Users/yadotrof/Desktop/Drawer/build-persistent_paint-Desktop_Qt_5_9_1_clang_64bit-Debug/untitled.obj");
//    mod[0].load_obj("/Users/yadotrof/BMSTU/CG/Course/build-CourseProject-Desktop_Qt_5_9_1_MinGW_32bit-Debug/models/test2.obj");
    mod[2].color[0]=130;
    mod[2].color[1]=82;
    mod[2].color[2]=20;
    mod[1].load_obj("/Users/yadotrof/BMSTU/CG/Course/build-CourseProject-Desktop_Qt_5_9_1_MinGW_32bit-Debug/models/1.obj");
    mod[1].color[0]=130;
    mod[1].color[1]=82;
    mod[1].color[2]=20;
    mod[0].load_obj("/Users/yadotrof/Desktop/Drawer/build-persistent_paint-Desktop_Qt_5_9_1_clang_64bit-Debug/ground.obj");
    mod[0].rotate_x=90;
    mod[0].color[0]=20;
    mod[0].color[1]=200;
    mod[0].color[2]=20;


    dx=0;
    dy=0;
    dz=0;

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

    timer->start(1);                   // Стартуем таймер на 50 миллисекунд
}


MyGraphicView::~MyGraphicView()
{

}



void MyGraphicView::slotAlarmTimer()
{



    QImage img(S_WIDTH,S_HEIGHT,QImage::Format_RGB32);
    img.fill(qRgb(200,200,200));
    for (int i = 0; i < S_WIDTH*S_HEIGHT; i++){
        zbuffer[i] = -INT_MAX;
    }

    QVector3D camera(camera_y,camera_x,camera_z);
    QVector3D up(0,-1,0);
    QMatrix4x4 matrix_p = matrix_perspective(camera.z());
    QMatrix4x4 Look;
    Look.lookAt(camera, target, up);
    QVector3D light(0,1,-1);
    light.normalize();
    QMatrix4x4 viewport_perspective_matrix = my_viewport(850,850,2500,0,0)*matrix_p;

    for (int m = 0; m < 3; m++ ){

        QMatrix4x4 model_matrix = matrix_delta(mod[m].dx,mod[m].dy,mod[m].dz)*matrix_scale(mod[m].scale_x,mod[m].scale_y,mod[m].scale_z)*rotate_matrix_x2(mod[m].rotate_x)*rotate_matrix_y2(mod[m].rotate_y)*rotate_matrix_z2(mod[m].rotate_z);
        QMatrix4x4 look_model_matrix = Look*model_matrix;
        for (int i = 0; i < mod[m].num_of_f;i++){

            int index1 = mod[m].f_array[i].point_num[0];
            int index2 = mod[m].f_array[i].point_num[1];
            int index3 = mod[m].f_array[i].point_num[2];

            QVector3D t0 = mod[m].v_array[index1];
            QVector3D t1 = mod[m].v_array[index2];
            QVector3D t2 = mod[m].v_array[index3];


            t0 = look_model_matrix*t0;
            t1 = look_model_matrix*t1;
            t2 = look_model_matrix*t2;




            //LIGHT

            QVector3D normal  = QVector3D::crossProduct(t0 - t2,t0 - t1);
            normal.normalize();
            mod[m].f_array[i].light_intensive = QVector3D::dotProduct(normal,light);

            if (mod[m].f_array[i].light_intensive < 0)
                mod[m].f_array[i].light_intensive = 0;

            double temp_light_intensive = mod[m].f_array[i].light_intensive;
            //END



            t0 = viewport_perspective_matrix* t0;
            t1 = viewport_perspective_matrix* t1;
            t2 = viewport_perspective_matrix*t2;


            if (t0.y()==t1.y() && t0.y()==t2.y()) continue; // i dont care about degenerate triangles
            // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)

            if (t0.x() < 0 || t1.x()<0 || t2.x() < 0)  continue;
            if (t0.y() < 0|| t1.y()<0 || t2.y() < 0)  continue;
            if (t0.x() > S_WIDTH || t1.x()> S_WIDTH || t2.x() > S_WIDTH)  continue;
            if (t0.y() > S_WIDTH || t1.y()> S_WIDTH || t2.y() > S_WIDTH)  continue;


            if (t0.y()>t1.y()) std::swap(t0, t1);
            if (t0.y()>t2.y()) std::swap(t0, t2);
            if (t1.y()>t2.y()) std::swap(t1, t2);

            t0.setX(round(t0.x()));
            t1.setX(round(t1.x()));
            t2.setX(round(t2.x()));
            t0.setY(round(t0.y()));
            t1.setY(round(t1.y()));
            t2.setY(round(t2.y()));
            t0.setZ(round(t0.z()));
            t1.setZ(round(t1.z()));
            t2.setZ(round(t2.z()));

            int total_height = t2.y()-t0.y();


            for (int h=0; h<total_height; h++) {
                bool second_half = h>t1.y()-t0.y() || t1.y()==t0.y();
                int segment_height = second_half ? t2.y()-t1.y() : t1.y()-t0.y();
                float alpha = (float)h/total_height;
                float beta  = (float)(h-(second_half ? t1.y()-t0.y() : 0))/segment_height; // be careful: with above conditions no division by zero here
                QVector3D A =               t0 + (t2-t0)*alpha;
                A.setX(round(A.x()));
                A.setY(round(A.y()));
                A.setZ(round(A.z()));
                QVector3D B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
                B.setX(round(B.x()));
                B.setY(round(B.y()));
                B.setZ(round(B.z()));
                if (A.x()>B.x()) std::swap(A, B);
                for (int j=A.x(); j<=B.x(); j++) {
                    float phi = B.x()==A.x() ? 1. : (float) (j-A.x())/(float)(B.x()-A.x());
                    QVector3D P = A + (B-A)*phi;
                    P.setX(round(P.x()));
                    P.setY(round(P.y()));
                    P.setZ(round(P.z()));
                    int idx = (P.x())+(P.y())*S_WIDTH;
                    if (idx < 0 || idx >= S_WIDTH*S_HEIGHT) continue;

                    if (zbuffer[idx]<P.z())
                    {
                        if (P.x() >= S_WIDTH || P.y()>=S_HEIGHT || P.x()< 0 || P.y()<0) continue;
                        zbuffer[idx] = P.z();
                        img.setPixel(P.x(), P.y(),qRgb(temp_light_intensive*mod[m].color[0],temp_light_intensive*mod[m].color[1],temp_light_intensive*mod[m].color[2])); // attention, due to int casts t0.y+i != A.y
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

