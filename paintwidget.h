#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>



#include "model.h"
#include "matrix.h"
#include "bullet.h"

// Расширяем класс QGraphicsView
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();
    bool checked_ground;
    bool checked_trebushet;
    bool checked_barel;

    Model *mod;
    double camera_z;
    double camera_x;
    double camera_y;
    QVector3D target;
    bool barrel_speed;
    bool second_frame;

signals:

private slots:
    void slotAlarmTimer();  /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                             * */

private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_1;   // Объявляем первую группу элементов
    QTimer              *timer;

    QPixmap m_nPTargetPixmap;

    int *zbuffer;
    bullet *barrel;

    void deleteItemsFromGroup();
    bool trebushet_rotate;
    //////////VARS FOR Z BUFFER
    int p0[3];
    int p1[3];
    int p2[3];
    int A[3];
    int B[3];
    int P[3];

    /////VARS FOR FACE DRAW
    bool second_half;
    int segment_height;
    float alpha;
    float beta;
    float phi;
    int idx;
    int total_height;
    uint face_color;
    double trebushet_angel;

};

#endif // PAINTWIDGET_H

