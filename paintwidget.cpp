#include "paintwidget.h"

MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView(parent)
{
    zbuffer = new int[S_WIDTH*S_HEIGHT];

    //CAMERA INIT SETTINGS
    camera = QVector3D(1,1,1);
    up = QVector3D(0,1,0);
    barrel_coord = false;
    look_at_barrel = false;

    target.setX(0);
    target.setY(0);
    target.setZ(0);

    //GENERATE GROUND
    ofstream Out("/Users/yadotrof/Desktop/Drawer/ground.obj");
    generate_ground(Out,100,100,0.2,-0.05,0.05);
    Out.close();

    ground = new Ground;
    trebushet = new Trebushet;
    barrel = new Barrel;
    boom = new Sprite();

    last_position = QVector3D(0,0,0);
    arrows_visible = true;
    Arrow = new Model("/Users/yadotrof/Desktop/Drawer/arrow.obj");
    Arrow->color[0]=255;
    Arrow->color[1]=100;
    Arrow->color[2]=100;
    num_of_arrows = 0;
    arrow_distance = 0;

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

    timer->start(1);                   // Стартуем таймер на 1 миллисекунду
    time.start();
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

    int temp_time =     time.elapsed(); //Время кадра

    trebushet->tick(temp_time,barrel);
    barrel->tick(temp_time,ground);

    if (last_position.x()==0 && last_position.y()==0 && last_position.z()==0){
        last_position = barrel->position;
    }

    arrow_distance += (last_position-barrel->position).length();
    last_position = barrel->position;
    if (arrow_distance>=0.2){
        arrow_distance = 0;
        num_of_arrows+=1;
        if (num_of_arrows==1000){
            num_of_arrows=1;
        }
        arrows[num_of_arrows-1] = matrix_delta(barrel->position.x(),barrel->position.y(),barrel->position.z())*QMatrix4x4();
    }

    QMatrix4x4 lookat_matrix;

    if (look_at_barrel){
        target = barrel->position;
    }

    if (barrel_coord){
        lookat_matrix.lookAt(camera+barrel->position, target, up);
    }
    else{
        lookat_matrix.lookAt(camera, target, up);
    }

    QMatrix4x4 viewport_perspective_matrix;


    viewport_perspective_matrix.viewport(0,0,S_WIDTH,S_HEIGHT,1,100000);
    viewport_perspective_matrix.perspective(60,S_WIDTH/S_HEIGHT,1,100000);


    if (trebushet->visible)  draw_model(&img,trebushet->trebushet_bottom,trebushet->model_bottom,lookat_matrix,viewport_perspective_matrix);
    if (trebushet->visible)  draw_model(&img,trebushet->trebushet_top,trebushet->model_top,lookat_matrix,viewport_perspective_matrix);
    if (barrel->visible)  draw_model(&img,barrel->barrel,barrel->model,lookat_matrix,viewport_perspective_matrix);
    if (ground->visible)  draw_model(&img,ground->ground,ground->model,lookat_matrix,viewport_perspective_matrix);

    if (arrows_visible){
        for (int a=0; a < num_of_arrows; a++){
            draw_model(&img,Arrow,arrows[a],lookat_matrix,viewport_perspective_matrix);
        }
    }

    QPixmap map = QPixmap::fromImage(img);


    //Отрисовка спрайта
    if (barrel->enable_boom){
        QPainter painter(&map);
        if (s <= 30){
            painter.drawPixmap((viewport_perspective_matrix*lookat_matrix*barrel->position).x()-50,S_HEIGHT-(viewport_perspective_matrix*lookat_matrix*barrel->position).y()-71,100,100,*(boom->spriteImage[s]));
            s+=1;
        }
    }

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

void  MyGraphicView::draw_model(QImage *img, Model* mod, QMatrix4x4 model_matrix, QMatrix4x4 lookat_matrix, QMatrix4x4 viewport_perspective_matrix){

    int color_r = mod->color[0];
    int color_g = mod->color[1];
    int color_b = mod->color[2];
    QVector3D light(1,-0.75,-1);
    light.normalize();

    QMatrix4x4 lookat_model_matrix = lookat_matrix*model_matrix;

    /////VARIABLES FOR FACE DRAW
    ///
    QVector3D t0,t1,t2,normal;
    double temp_light_intensive;

    for (int i = 0; i < mod->num_of_f;i++){
        t0 = mod->v_array[ mod->f_array[i].point_num[0] ];
        t1 = mod->v_array[ mod->f_array[i].point_num[1] ];
        t2 = mod->v_array[ mod->f_array[i].point_num[2] ];

        t0 = lookat_model_matrix*t0;
        t1 = lookat_model_matrix*t1;
        t2 = lookat_model_matrix*t2;

        //LIGHT
        normal  = QVector3D::crossProduct(t0 - t2,t0 - t1).normalized();
        temp_light_intensive = QVector3D::dotProduct(normal,light);
        if (temp_light_intensive < 0)  temp_light_intensive = 0;

        t0 = viewport_perspective_matrix* t0;
        t1 = viewport_perspective_matrix* t1;
        t2 = viewport_perspective_matrix* t2;

        normal  = QVector3D::crossProduct(t0 - t1,t0 - t2).normalized();
        if (QVector3D::dotProduct(normal,QVector3D(0,0,1))< 0) continue;
        if (normal.z()<0) continue;

        p0[0] = t0.x(); p1[0] = t1.x(); p2[0] = t2.x();
        p0[1] = t0.y(); p1[1] = t1.y(); p2[1] = t2.y();
        p0[2] = t0.z(); p1[2] = t1.z(); p2[2] = t2.z();

        if ((p0[2]>1000000 || p1[2]>100000 || p2[2]>100000)) continue;   //Если слишком большой

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
            Ax=p0[0] + ((p2[0]-p0[0])*alpha+.5f);
            Ay=p0[1] + ((p2[1]-p0[1])*alpha+.5f);
            Az=p0[2] + ((p2[2]-p0[2])*alpha+.5f);
            //                B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
            if (second_half){
                Bx=p1[0] + ((p2[0]-p1[0])*beta+.5f);
                By=p1[1] +  ((p2[1]-p1[1])*beta+.5f);
                Bz=p1[2] + ((p2[2]-p1[2])*beta+.5f);
            }
            else{
                Bx=p0[0] +  ((p1[0]-p0[0])*beta+.5f);
                By=p0[1] + ((p1[1]-p0[1])*beta+.5f);
                Bz=p0[2] + ((p1[2]-p0[2])*beta+.5f);
            }
            if (Ax>Bx){ std::swap(Ax, Bx); std::swap(Ay, By); std::swap(Az, Bz);}
            for (int j=Ax; j<=Bx; j++) {
                phi = Bx==Ax ? 1. : (float) (j-Ax)/(float)(Bx-Ax);
                //                    P = A + (B-A)*phi;
                Px=Ax +  ((Bx-Ax)*phi+.5f);
                Py=Ay + ((By-Ay)*phi+.5f);
                Pz=Az + ((Bz-Az)*phi+.5f);
                if (Px < 0 || Px>=S_WIDTH || Py<0 || Py>=S_HEIGHT) continue;
                idx = (Px)+(Py)*S_WIDTH;

                if (zbuffer[idx]>Pz)
                {
                    zbuffer[idx] = Pz;
                    img->setPixel(Px, S_HEIGHT-Py-1,face_color); // attention, due to int casts t0.y+i != A.y
                }
            }
        }
    }
}




void MyGraphicView::setBarrelCoord(double x, double y, double z){
    barrel_coord = true;
    camera = QVector3D(x,y,z);
}

void MyGraphicView::setWorldCoord(double x, double y, double z){
    barrel_coord = false;
    camera = QVector3D(x,y,z);
}

void MyGraphicView::setLookAtCoord(double x, double y, double z){
    target = QVector3D(x,y,z);
    look_at_barrel = false;
}
void MyGraphicView::setLookAtBarrel(){
    look_at_barrel = true;
}

void MyGraphicView::setTrebushetParam(double m2, double m1, double angel){
    trebushet->m1 = m1;
    trebushet->m2 = m2;
    trebushet->calculateShoot(angel);
}
void MyGraphicView::setBarrelVisible(bool state){
    barrel->visible = state;
}
void MyGraphicView::setTrebushetVisible(bool state){
    trebushet->visible = state;
}
void MyGraphicView::setGroundVisible(bool state){
    ground->visible = state;
}
void MyGraphicView::setArrowsVisible(bool state){
    arrows_visible = state;
}


void MyGraphicView::launch_trebushet(){
    trebushet->trebushet_rotate = true;   //TODO ADD LAUNCH INTERFACE
}
void MyGraphicView::reboot(){
    barrel->reboot();
    trebushet->reboot();
    arrow_distance = 0;
    s = 0;
}
void MyGraphicView::dropArrows(){
    num_of_arrows = 0;
}
