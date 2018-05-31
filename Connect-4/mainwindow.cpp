#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fields.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QPixmap board_picture("/home/ana/Desktop/Predmeti/RS/projekat/Connect-4/grafika/board.png");
    // ui->mouseArea->setPixmap(board_picture);

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

    //int a = ui->mouseArea->x;
    insertAtBoard(ui->mouseArea->x);

}

void MainWindow::Mouse_left()
{
    ui->testLabel2->setText("mouse left");

}

//Treba odraditi algoritam

void MainWindow::insertAtBoard(int x) {

    if (x < 60) {
        ui->testLabel2->setText("prva kolona");

        QPixmap kuglica(":/grafika/r1.png");
        QLabel * temp=new QLabel(this);

        temp->setPixmap(kuglica);
        temp->resize(57, 57);
        ui->gridLayout->addWidget(temp, 5, 0);
    }


    else if (x < 120) {
        ui->testLabel2->setText("druga kolona");

        QPixmap kuglica(":/grafika/blue.png");
        QLabel * temp=new QLabel(this);
        temp->resize(57, 57);
        temp->setPixmap(kuglica);
        ui->gridLayout->addWidget(temp, 5, 1);
    }

};
