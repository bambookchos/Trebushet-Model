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

    myPicture = new MyGraphicView();

    ui->gridLayout->addWidget(myPicture);

    //CAMERA SET COORDS
    ui->lineEdit_4->setText("1.0");
    ui->lineEdit_5->setText("1.0");
    ui->lineEdit_6->setText("1.0");

    //TARGET SET COORDS
    ui->lineEdit_7->setText("0.0");
    ui->lineEdit_8->setText("0.0");
    ui->lineEdit_9->setText("0.0");

    ui->lineEdit_10->setText("40");
    ui->lineEdit_11->setText("8000");
    ui->lineEdit_12->setText("45");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()  //Применение настроек камеры
{
    if (ui->radioButton->isChecked()){
        myPicture->setWorldCoord(ui->lineEdit_4->text().toDouble(),ui->lineEdit_5->text().toDouble(),ui->lineEdit_6->text().toDouble());
    }
    if (ui->radioButton_2->isChecked()){
        myPicture->setBarrelCoord(ui->lineEdit_4->text().toDouble(),ui->lineEdit_5->text().toDouble(),ui->lineEdit_6->text().toDouble());
    }
    if (ui->radioButton_3->isChecked()){
        myPicture->setLookAtBarrel();
    }
    if (ui->radioButton_4->isChecked()){
        myPicture->setLookAtCoord(ui->lineEdit_7->text().toDouble(),ui->lineEdit_8->text().toDouble(),ui->lineEdit_9->text().toDouble());
    }
}

void MainWindow::on_pushButton_2_clicked() //Настройки требушета
{
    myPicture->setTrebushetParam(ui->lineEdit_10->text().toDouble(), ui->lineEdit_11->text().toDouble(), ui->lineEdit_12->text().toDouble());
}

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if (checked){
        ui->lineEdit_7->setReadOnly(true);
        ui->lineEdit_8->setReadOnly(true);
        ui->lineEdit_9->setReadOnly(true);
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::gray);
        palette->setColor(QPalette::Text,Qt::darkGray);
        ui->lineEdit_7->setPalette(*palette);
        ui->lineEdit_8->setPalette(*palette);
        ui->lineEdit_9->setPalette(*palette);
    }
}

void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if (checked){
        ui->lineEdit_7->setReadOnly(false);
        ui->lineEdit_8->setReadOnly(false);
        ui->lineEdit_9->setReadOnly(false);
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::white);
        palette->setColor(QPalette::Text,Qt::black);
        ui->lineEdit_7->setPalette(*palette);
        ui->lineEdit_8->setPalette(*palette);
        ui->lineEdit_9->setPalette(*palette);
    }
}



void MainWindow::on_checkBox_2_clicked(bool checked)
{
    myPicture->setTrebushetVisible(checked);
}

void MainWindow::on_checkBox_3_clicked(bool checked)
{
    myPicture->setBarrelVisible(checked);
}

void MainWindow::on_checkBox_5_clicked(bool checked)
{
    myPicture->setGroundVisible(checked);
}

void MainWindow::on_checkBox_4_clicked(bool checked)
{
    myPicture->setArrowsVisible(checked);
}



void MainWindow::on_pushButton_5_clicked() //Запуск выстрела требушета
{
    myPicture->launch_trebushet();
}
void MainWindow::on_pushButton_7_clicked()
{
    myPicture->reboot();
}
void MainWindow::on_pushButton_3_clicked()
{
    myPicture->dropArrows();
}
