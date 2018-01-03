#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H



#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QEvent>
#include <QRgb>
#include <QGraphicsPixmapItem>
#include <QTime>



#define S_WIDTH 700
#define S_HEIGHT 700


#include "sprite.h"
#include "Objects/barrel.h"
#include "Objects/trebushet.h"
#include "Objects/ground.h"

// Расширяем класс QGraphicsView
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

    void draw_model(QImage *img, Model* mod, QMatrix4x4 model_matrix, QMatrix4x4 lookat_matrix, QMatrix4x4 viewport_perspective_matrix);

    void setWorldCoord(double x, double y, double z);
    void setBarrelCoord(double x, double y, double z);

    void setLookAtCoord(double x, double y, double z);
    void setLookAtBarrel();

    void setBarrelVisible(bool state);
    void setTrebushetVisible(bool state);
    void setGroundVisible(bool state);
    void setArrowsVisible(bool state);

    void launch_trebushet();

    void setTrebushetParam(double m2, double m1, double angel);

    void reboot();
    void dropArrows();



signals:

private slots:
    void slotAlarmTimer();  /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                             * */

private:
    int num_of_arrows;
    Sprite *boom;
    bool arrows_visible;
    QMatrix4x4 arrows[1000];
    Model* Arrow;
    double arrow_distance;
    QVector3D last_position;


    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QTimer              *timer;  //Таймер отрисовки кадра
    QTime time; //Часы сцены


    Trebushet *trebushet;
    Barrel *barrel;
    Ground *ground;

    QVector3D up;
    QVector3D camera;
    QVector3D target;

    int s = 0;                    //Счетчик отрисованных спрайтов взрыва

    int *zbuffer;           // Z-BUFFER
    void deleteItemsFromGroup();    //Очистка сцены

    bool barrel_coord;  //Включает координаты относительно бочки
    bool look_at_barrel; //Включает взгля на бочку


    //////////VARS FOR Z BUFFER
    int p0[3];
    int p1[3];
    int p2[3];
    int Ax,Ay,Az;
    int Bx,By,Bz;
    int Px,Py,Pz;

    /////VARS FOR FACE DRAW
    bool second_half;
    int segment_height;
    float alpha;
    float beta;
    float phi;
    int idx;
    int total_height;
    uint face_color;
};

#endif // PAINTWIDGET_H

