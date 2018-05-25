#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fields.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // QPixmap board_picture("/home/ana/Desktop/Predmeti/RS/projekat/Connect-4/grafika/board.png");
 //   ui->mouseArea->setPixmap(board_picture);
    connect(ui->mouseArea,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->mouseArea,SIGNAL(Mouse_pressed()),this,SLOT(Mouse_pressed()));
    connect(ui->mouseArea,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));


    this->setFixedSize(470,500);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Mouse_current_pos()
{
    ui->testLabel->setText(QString("X:%1,Y:%2").arg(ui->mouseArea->x).arg(ui->mouseArea->y));
}
void MainWindow::Mouse_pressed()
{
    ui->testLabel2->setText("kliknulo");
}
void MainWindow::Mouse_left()
{
    ui->testLabel2->setText("mouse left");

}

