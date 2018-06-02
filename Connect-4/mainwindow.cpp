#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fields.h"
#include <iostream>


using namespace std;

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
    player=1;//red one


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
    insertAtBoard(ui->mouseArea->x, ui->mouseArea->y);
}


void MainWindow::Mouse_left()
{
    ui->testLabel2->setText("mouse left");
}



int MainWindow::restrictionMove(int tmpX,int tmpY){


    if(tmpY==5){
        return 1;

    }
    else{
        if(matrix[tmpY+1][tmpX]==1 or matrix[tmpY+1][tmpX]==2 ){
            return 1;
         }
        else
            return 0;
    }



}
int MainWindow::checkCoordinates(int x, int y){

    int tmpX=x/60;
    int tmpY=y/60;


    if (y>361)
        return 0;
    else{

        if (matrix[tmpY][tmpX]==0)
            return 1;
        return 0;

    }

}
void MainWindow::insertAtBoard(int x, int y) {

    if (checkCoordinates(x, y)){

        int tmpX=x/60;
        int tmpY=y/60;

        if( restrictionMove( tmpX, tmpY)){

        // cout << tmpX << ":" << tmpY << endl;

            if(player){//red player

                 QPixmap kuglica(":/grafika/r1.png");
                 QLabel * temp=new QLabel(this);

                 temp->setPixmap(kuglica);
                 temp->resize(57, 57);
                 ui->gridLayout->addWidget(temp, tmpY, tmpX);
                 matrix[tmpY][tmpX]=1;

                 player=0;
             }
             else{

                    QPixmap kuglica(":/grafika/blue.png");
                    QLabel * temp=new QLabel(this);
                    temp->resize(57, 57);
                    temp->setPixmap(kuglica);
                    // TODO:
                    ui->gridLayout->addWidget(temp, tmpY, tmpX);
                    matrix[tmpY][tmpX]=2;
                    player=1;
     }



     for(int m=0;m<6;m++) {
             for(int k=0;k<7;k++) {
                cout << matrix[m][k] <<  " ";
             }
             cout << endl;
     }

     cout << endl;

    }
    }

};
