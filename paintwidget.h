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
    int camera_z;
    int camera_x;
    int camera_y;
    QVector3D target;


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
    int rotate_x,rotate_y,rotate_z;
    float dx,dy,dz;
    void deleteItemsFromGroup();


};

#endif // PAINTWIDGET_H

