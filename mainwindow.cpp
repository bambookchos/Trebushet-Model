#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"
#include <QHBoxLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);


    // This is one way to programatically add a custom widget

    myPicture = new MyGraphicView();
    /* и добавляем его на слой */

    ui->gridLayout->addWidget(myPicture);    // instead, you could use the UI Designer to "Promote" a widget to a specific type.




    //    for(int i = 1; i< n; i++)
    //        scene->addEllipse(points[i].x(), points[i].y(), 512, 512);
    ui->scale_ground->setText("1");
    ui->scale_barrel->setText("1");
    ui->scale_trebushet->setText("1");
    ui->dx_ground->setText("0");
    ui->dy_ground->setText("0");
    ui->dz_ground->setText("0");
    ui->dx_trebushet->setText("0");
    ui->dy_trebushet->setText("0");
    ui->dz_trebushet->setText("0");
    ui->dx_barrel->setText("0");
    ui->dy_barrel->setText("0");
    ui->dz_barrel->setText("0");
    ui->rotate_x_barrel->setText("0");
    ui->rotate_y_barrel->setText("0");
    ui->rotate_z_barrel->setText("0");
    ui->rotate_x_ground->setText("0");
    ui->rotate_y_ground->setText("0");
    ui->rotate_z_ground->setText("0");
    ui->rotate_x_trebushet->setText("0");
    ui->rotate_y_trebushet->setText("0");
    ui->rotate_z_trebushet->setText("0");
    ui->x_target->setText("0");
    ui->y_target->setText("0");
    ui->z_target->setText("0");

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_checkBox_toggled(bool checked)
{
    myPicture->checked_ground = checked;
}




void MainWindow::on_checkBox_2_toggled(bool checked)
{
    myPicture->checked_barel = checked;
}


void MainWindow::on_checkBox_3_toggled(bool checked)
{
    myPicture->checked_trebushet = checked;
}


void MainWindow::on_pushButton_clicked()
{
    myPicture->mod[0].scale_x = ui->scale_ground->text().toDouble();
    myPicture->mod[0].scale_y = ui->scale_ground->text().toDouble();
    myPicture->mod[0].scale_z = ui->scale_ground->text().toDouble();
    myPicture->mod[0].dx = ui->dx_ground->text().toDouble();
    myPicture->mod[0].dy = ui->dy_ground->text().toDouble();
    myPicture->mod[0].dz = ui->dz_ground->text().toDouble();
    myPicture->mod[0].rotate_x = ui->rotate_x_ground->text().toDouble();
    myPicture->mod[0].rotate_y = ui->rotate_y_ground->text().toDouble();
    myPicture->mod[0].rotate_z = ui->rotate_z_ground->text().toDouble();
}

void MainWindow::on_pushButton_2_clicked()
{
    myPicture->mod[1].scale_x = ui->scale_barrel->text().toDouble();
    myPicture->mod[1].scale_y = ui->scale_barrel->text().toDouble();
    myPicture->mod[1].scale_z = ui->scale_barrel->text().toDouble();
    myPicture->mod[1].dx = ui->dx_barrel->text().toDouble();
    myPicture->mod[1].dy = ui->dy_barrel->text().toDouble();
    myPicture->mod[1].dz = ui->dz_barrel->text().toDouble();
    myPicture->mod[1].rotate_x = ui->rotate_x_barrel->text().toDouble();
    myPicture->mod[1].rotate_y = ui->rotate_y_barrel->text().toDouble();
    myPicture->mod[1].rotate_z = ui->rotate_z_barrel->text().toDouble();
}

void MainWindow::on_pushButton_3_clicked()
{
    myPicture->mod[2].scale_x = ui->scale_trebushet->text().toDouble();
    myPicture->mod[2].scale_y = ui->scale_trebushet->text().toDouble();
    myPicture->mod[2].scale_z = ui->scale_trebushet->text().toDouble();
    myPicture->mod[2].dx = ui->dx_trebushet->text().toDouble();
    myPicture->mod[2].dy = ui->dy_trebushet->text().toDouble();
    myPicture->mod[2].dz = ui->dz_trebushet->text().toDouble();
    myPicture->mod[2].rotate_x = ui->rotate_x_trebushet->text().toDouble();
    myPicture->mod[2].rotate_y = ui->rotate_y_trebushet->text().toDouble();
    myPicture->mod[2].rotate_z = ui->rotate_z_trebushet->text().toDouble();
}


void MainWindow::on_pushButton_4_clicked()
{
    myPicture->target.setX(ui->x_target->text().toDouble());
    myPicture->target.setY(ui->y_target->text().toDouble());
    myPicture->target.setZ(ui->z_target->text().toDouble());
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{

    if (e->type()==QEvent::KeyPress) {

        QKeyEvent* key = static_cast<QKeyEvent*>(e);

        for (int i = 0; i<4; i++) {
            if (i == 0 && ! myPicture->checked_ground){
                continue;
            }
            if (i == 3 && !myPicture->checked_barel){
                continue;
            }
            if (i == 2 && !myPicture->checked_trebushet){
                continue;
            }
            if (i == 1 && !myPicture->checked_trebushet){
                continue;
            }
            switch (key->key()) {
            case Qt::Key_W:
                myPicture->mod[i].dy-=0.01;
                break;
            case Qt::Key_A:
                myPicture->mod[i].dx-=0.01;
                break;
            case Qt::Key_S:
                myPicture->mod[i].dy+=0.01;
                break;
            case Qt::Key_D:
                myPicture->mod[i].dx+=0.01;
                break;
            case Qt::Key_Q:
                myPicture->mod[i].dz-=1;
                break;
            case Qt::Key_E:
                myPicture->mod[i].dz+=1;
                break;
            case Qt::Key_Y:
                myPicture->mod[i].rotate_x+=2;
                break;
            case Qt::Key_H:
                myPicture->mod[i].rotate_x-=2;
                break;
            case Qt::Key_U:
                myPicture->mod[i].rotate_y+=2;
                break;
            case Qt::Key_J:
                myPicture->mod[i].rotate_y-=2;
                break;
            case Qt::Key_I:
                myPicture->mod[i].rotate_z+=2;
                break;
            case Qt::Key_K:
               myPicture->mod[i].rotate_z-=2;
                break;
            default:
                break;
            }
        }
        ui->scale_ground->setText(QString::number(myPicture->mod[0].scale_x));
        ui->scale_barrel->setText(QString::number(myPicture->mod[1].scale_x));
        ui->scale_trebushet->setText(QString::number(myPicture->mod[2].scale_x));
        ui->dx_ground->setText(QString::number(myPicture->mod[0].dx));
        ui->dy_ground->setText(QString::number(myPicture->mod[0].dy));
        ui->dz_ground->setText(QString::number(myPicture->mod[0].dz));
        ui->dx_trebushet->setText(QString::number(myPicture->mod[2].dx));
        ui->dy_trebushet->setText(QString::number(myPicture->mod[2].dy));
        ui->dz_trebushet->setText(QString::number(myPicture->mod[2].dz));
        ui->dx_barrel->setText(QString::number(myPicture->mod[3].dx));
        ui->dy_barrel->setText(QString::number(myPicture->mod[3].dy));
        ui->dz_barrel->setText(QString::number(myPicture->mod[3].dz));
        ui->rotate_x_barrel->setText(QString::number(myPicture->mod[3].rotate_x));
        ui->rotate_y_barrel->setText(QString::number(myPicture->mod[3].rotate_y));
        ui->rotate_z_barrel->setText(QString::number(myPicture->mod[3].rotate_z));
        ui->rotate_x_ground->setText(QString::number(myPicture->mod[0].rotate_x));
        ui->rotate_y_ground->setText(QString::number(myPicture->mod[0].rotate_y));
        ui->rotate_z_ground->setText(QString::number(myPicture->mod[0].rotate_z));
        ui->rotate_x_trebushet->setText(QString::number(myPicture->mod[2].rotate_x));
        ui->rotate_y_trebushet->setText(QString::number(myPicture->mod[2].rotate_y));
        ui->rotate_z_trebushet->setText(QString::number(myPicture->mod[2].rotate_z));
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    myPicture->barrel_speed = true;
}

void MainWindow::on_pushButton_6_clicked()
{
    myPicture->camera_z =ui->lineEdit->text().toDouble();
    myPicture->camera_x =ui->lineEdit_2->text().toDouble();
    myPicture->camera_y =ui->lineEdit_3->text().toDouble();

}
