#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fields.h"
#include <iostream>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->mouseArea,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->mouseArea,SIGNAL(Mouse_pressed()),this,SLOT(Mouse_pressed()));
    connect(ui->mouseArea,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));

    this->setFixedSize(470,500);

    newGame();



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
{ }



int MainWindow::restrictionMove(int tmpX,int tmpY){

    if (matrix[tmpY][tmpX]!=0)
        return 0;

    if(tmpY==5) {
        return 1;
    }
    else {
        if(matrix[tmpY+1][tmpX]==1 || matrix[tmpY+1][tmpX]==2) {
            return 1;
         }
        else
            return 0;
    }

}




void MainWindow::insertAtBoard(int x, int y) {

        int tmpX=x/60;
        int tmpY=y/60;


        if( restrictionMove(tmpX, tmpY)) {

            if(player) {  //red player

                QPixmap kuglica(":/grafika/r1.png");
                QLabel * temp = new QLabel(this);

                temp->setPixmap(kuglica);
                temp->resize(60, 60);
                ui->gridLayout->addWidget(temp, tmpY, tmpX);
                matrix[tmpY][tmpX]=1;

                if(checkForWinner(tmpY,tmpX,1)){
                    ui->testLabel2->setText("Player 1 wins");
                    endGame(1);
                    return;
                }

                if(isComputer) {
                    computerPlaying(tmpY,tmpX);
                }
                else{
                    player=0;
                }
            }
            //player 2
            else {

               QPixmap kuglica(":/grafika/blue.png");
               QLabel * temp=new QLabel(this);
               temp->resize(60, 60);
               temp->setPixmap(kuglica);

               // TODO:
               ui->gridLayout->addWidget(temp, tmpY, tmpX);
               matrix[tmpY][tmpX]=2;

               if(checkForWinner(tmpY,tmpX,2)){
                    ui->testLabel2->setText("Player 2 wins");
                    endGame(2);
                    return;
                }

               player=1;
               checkIfEqual();
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







bool MainWindow::checkForWinner(int x,int y,int player) {
    if( checkRows(x, player) || checkColumns(y, player) ||checkDiagonal(x, y, player))
        return true;
    else return false;
}

bool MainWindow::checkRows(int x, int player)
{
    int counter=0;
    for (int i=0;i<7;i++){
        if(matrix[x][i]!=player)
            counter=0;
        else if(matrix[x][i]==player)
            counter++;
        if(counter==4)
            return true;
    }
   return false;

}

bool MainWindow::checkColumns(int y, int player)
{
    int counter=0;
    for(int i=0;i<6;i++){
        if(matrix[i][y]!=player)
            counter=0;
        else if(matrix[i][y]==player)
            counter++;
        if(counter==4)
            return true;
    }
    return false;
}

bool MainWindow::checkDiagonal(int x,int y,int player)
{
    int xhelp=x;
    int yhelp=y;

    int counter=0;
    while(x>=0 && y>=0)
    {
        if(matrix[x][y]!=player)
            break;
        else if(matrix[x][y]==player)
            counter++;
        x--;
        y--;
    }

    int counter2=0;
    x=xhelp+1;
    y=yhelp+1;
    while(x<6 && y<7)
    {

        if(matrix[x][y]!=player)
            break;
        else if(matrix[x][y]==player)
            counter2++;
        x++;
        y++;

    }

    if (counter+counter2 == 4) {
        return true;
    }

    counter = 0;
    x = xhelp;
    y = yhelp;

    while(x>=0 && y<7)
    {
        if(matrix[x][y]!=player)
            break;
        else if(matrix[x][y]==player)
            counter++;
        x--;
        y++;
        if(counter==4)
            break;
    }

    counter2=0;
    x=xhelp+1;
    y=yhelp-1;

    while(x<6 && y>=0)
    {

        if(matrix[x][y]!=player)
            break;
        else if(matrix[x][y]==player)
            counter2++;
        if(counter+counter2==4)
             break;
        x++;
        y--;
    }

    return (counter+counter2==4);
}



void MainWindow::endGame(int pl)
{

    QMessageBox msgBox;
    if(pl==2)
        msgBox.setText("Blue player wins.\nCongratulations!");
    else if(pl==1)
        msgBox.setText("Red player wins.\nCongratulations!");
    else msgBox.setText("It's a tie!");

    msgBox.setWindowTitle("End!");
    msgBox.addButton("Play again?",QMessageBox::AcceptRole);
    msgBox.addButton("Quit",QMessageBox::RejectRole);
    int retVal = msgBox.exec();

    if(retVal==0) //quit
        newGame();
    else
        this->close();

}

void MainWindow::newGame()
{
    player = 1; //red player first
    isComputer = false;

    if(gameType() == 0)
        isComputer=true;

    for(int i=0;i<6;i++)
        for(int j=0;j<7;j++)
            matrix[i][j]=0;

    QLayoutItem *tmp;
    while((tmp=ui->gridLayout->takeAt(0))!=0)
    {
       delete tmp->widget();
       delete tmp;
    }
    ui->testLabel2->setText("");
}

int MainWindow::gameType()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Choose game type");
    msgBox.addButton("With computer?",QMessageBox::AcceptRole);
    msgBox.addButton("With player 2?",QMessageBox::RejectRole);


    int retVal = msgBox.exec();

    if(retVal==0)
        return 0;
    else {
        return 1;
    }
}
void MainWindow::checkIfEqual()
{

    for(int m=0;m<6;m++) {
       for(int k=0;k<7;k++) {
           if(matrix[m][k]==0)
               return;
       }
   }
    endGame(0);

}


void MainWindow::computerPlaying(int tmpY, int tmpX)
{
    /*
    QPixmap kuglica(":/grafika/blue.png");
    QLabel * temp=new QLabel(this);

    temp->setPixmap(kuglica);
    temp->resize(60, 60);




    //AI alghoritm




    ui->gridLayout->addWidget(temp, tmpY, tmpX);
    matrix[tmpY][tmpX]=2;

    if(checkForWinner(tmpY,tmpX,2)){
        ui->testLabel2->setText("Computer wins!");
        endGame(1);
*/
}
