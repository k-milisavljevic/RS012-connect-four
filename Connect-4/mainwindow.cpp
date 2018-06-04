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

}

void MainWindow::Mouse_pressed()
{
    insertAtBoard(ui->mouseArea->x, ui->mouseArea->y);
}

void MainWindow::Mouse_left()
{ }



int MainWindow::restrictionMove(int tmpX,int tmpY){

    if (matrix[tmpY][tmpX]!=0){
        ui->testLabel2->setText("Field is full!");
        return 0;

    }

    if(tmpY==5) {
        ui->testLabel2->setText("");
        return 1;
    }
    else {
        if(matrix[tmpY+1][tmpX]==1 || matrix[tmpY+1][tmpX]==2) {
            ui->testLabel2->setText("");
            return 1;
        }
        else{

            ui->testLabel2->setText("Unavailable field!");
            return 0;

        }
    }

}

void MainWindow::insertAtBoard(int x, int y) {

    int tmpX=x/60;
    int tmpY=y/60;


    if( restrictionMove(tmpX, tmpY)) {

        if(player==1) {  //red player

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
                player=2;
            }
        }
        //player 2
        else if(player==2){

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
            if(checkIfEqual())
                endGame(0);
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
    if(pl==1)
        msgBox.setText("Red player wins.\nCongratulations!");
    else if(pl==2) {
        if(isComputer)
            msgBox.setText("Computer wins.\nTry again!");
        else
            msgBox.setText("Blue player wins.\nCongratulations!");
    }

    else msgBox.setText("It's a tie!");

    msgBox.setWindowTitle("End!");
    msgBox.addButton("Play again?",QMessageBox::AcceptRole);
    msgBox.addButton("Quit",QMessageBox::RejectRole);
    int retVal = msgBox.exec();

    if(retVal==0)
        newGame();
    else
        this->close();

}

void MainWindow::newGame()
{
    player = 1; //red player first
    isComputer = false;

    if(gameType() == 0){
        isComputer=true;
        gameLevel();
    }

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

    if(retVal==0){
        // with computer
        return 0;
    }
    else {
        // with player 2
        return 1;
    }
}

bool MainWindow::checkIfEqual()
{

    for(int m=0;m<6;m++) {
        for(int k=0;k<7;k++) {
            if(matrix[m][k]==0)
                return false;
        }
    }
    return true;

}


void MainWindow::computerPlaying(int tmpX, int tmpY)
{

    QPixmap kuglica(":/grafika/blue.png");
    QLabel * temp=new QLabel(this);

    temp->setPixmap(kuglica);
    temp->resize(60, 60);


    //AI alghoritm

    minMaxMax(INT_MIN,INT_MAX,tmpX,tmpY,0);
    //cout <<" Xcor: " << Xcor <<" Ycor: " << Ycor << endl;

    ui->gridLayout->addWidget(temp, Xcor, Ycor);
    matrix[Xcor][Ycor]=2;

    if(checkForWinner(Xcor,Ycor,2)){
        ui->testLabel2->setText("Computer wins!");
        endGame(2);

    }
}

int MainWindow::minMaxMax(int alpha, int beta, int tmpX, int tmpY, int depth)
{
    // mi pobedili
    if(checkForWinner(tmpX,tmpY,1))
        return -1000;
    else if (checkForWinner(tmpX,tmpY,2))
        return 1000;
    else if (checkIfEqual())
        return 0;

    int v = INT_MIN;

    if(depth==maxDepth)
        return countConnected();

    int  best_i = tmpX;
    int  best_j = tmpY;

    for (int i=0;i<6;i++){
        for (int j=0;j<7;j++){
            if (matrix[i][j]==0 && restrictionMove(j,i)!=0){

                matrix[i][j]=2;


                int m = minMaxMin(alpha, beta,i,j,depth+1);


                if (m > v){
                    v = m;
                    best_i = i;
                    best_j = j;
                }
                if (v >= beta){
                    Xcor = best_i;
                    Ycor = best_j;
                    matrix[i][j]=0;
                    return v;
                }
                if (v > alpha)
                    alpha = v;

                matrix[i][j]=0;
            }
        }
    }

    Xcor = best_i;
    Ycor = best_j;

    return v;



}


int MainWindow::minMaxMin(int alpha,int beta,int tmpX,int tmpY,int depth)
{
    // mi pobedili
    if(checkForWinner(tmpX,tmpY,1))
        return -1000;
    else if (checkForWinner(tmpX,tmpY,2))
        return 1000;
    else if (checkIfEqual())
        return 0;

    int v = INT_MAX;

    for (int i=0;i<6;i++){
        for (int j=0;j<7;j++){
            if (matrix[i][j]==0 && restrictionMove(j,i)!=0){
                matrix[i][j]=1;
                int  M = minMaxMax(alpha, beta,i,j,depth+1);
                if (M < v)
                    v = M;

                if (v <= alpha){
                    matrix[i][j]=0;
                    return v;
                }
                if (v <beta){
                    beta= v;
                }
                matrix[i][j]=0;
            }
        }
    }
    return v;

}
int MainWindow::countConnected()
{
    // ideja funkcije preuzeta sa interneta i prilagodjena nasem projektu


    //counting how many are connected

    //blue
    int computerScore=1;
    //total score
    int score=0;
    int zeros = 0;
    int k=0, movesLeft=0;

    for(int i=5;i>=0;--i){
        for(int j=0;j<7;++j){

            if(matrix[i][j]==0 || matrix[i][j]==1)
                continue;
            //right

            if(j<=3){
                for(k=1;k<4;++k){
                    if(matrix[i][j+k]==2)
                        computerScore++;
                    else if(matrix[i][j+k]==1)
                    {
                        computerScore=0;
                        zeros = 0;
                        break;
                    }
                    else
                        zeros++;
                }
//right-down
                movesLeft = 0;
                if(zeros>0)
                    for(int c=1;c<4;++c){
                        int column = j+c;
                        for(int m=i; m<= 5;m++)
                        {
                            if(matrix[m][column]==0)
                                movesLeft++;
                            else break;
                        }
                    }

                if(movesLeft!=0)
                    score += calculateScore(computerScore, movesLeft);
                computerScore=1;
                zeros = 0;
            }
//up
            if(i>=3){
                for(k=1;k<4;++k){
                    if(matrix[i-k][j]==2)
                        computerScore++;
                    else if(matrix[i-k][j]==1)
                    {
                        computerScore=0;
                        break;
                    }
                }
                movesLeft = 0;

                if(computerScore>0){
                    int column = j;
                    for(int m=i-k+1; m<=i-1;m++){
                        if(matrix[m][column]==0)
                            movesLeft++;
                        else
                            break;
                    }
                }
                if(movesLeft!=0) score += calculateScore(computerScore, movesLeft);
                computerScore=1;
                zeros = 0;
            }
//left
            if(j>=3){
                for(k=1;k<4;++k){
                    if(matrix[i][j-k]==2)
                        computerScore++;
                    else if(matrix[i][j-k]==1)
                    {
                        computerScore=0;
                        zeros=0;
                        break;
                    }
                    else zeros++;
                }
//left-down
                movesLeft=0;
                if(zeros>0)
                    for(int c=1;c<4;++c){
                        int column = j- c;
                        for(int m=i; m<= 5;m++){
                            if(matrix[m][column]==0)movesLeft++;
                            else break;
                        }
                    }

                if(movesLeft!=0) score += calculateScore(computerScore, movesLeft);
                computerScore=1;
                zeros = 0;
            }
//upper-right diagonal
            if(j<=3 && i>=3){
                for(k=1;k<4;++k){
                    if(matrix[i-k][j+k]==2)computerScore++;
                    else if(matrix[i-k][j+k]==1)
                    {
                        computerScore=0;
                        zeros=0;
                        break;
                    }
                    else zeros++;
                }
//zeros count
                movesLeft=0;
                if(zeros>0){
                    for(int c=1;c<4;++c){
                        int column = j+c, row = i-c;
                        for(int m=row;m<=5;++m){
                            if(matrix[m][column]==0)movesLeft++;
                            else if(matrix[m][column]==2);
                            else break;
                        }
                    }
                    if(movesLeft!=0) score += calculateScore(computerScore, movesLeft);
                    computerScore=1;
                    zeros = 0;
                }
            }
//upper-left diagonal
            if(i>=3 && j>=3){
                for(k=1;k<4;++k){
                    if(matrix[i-k][j-k]==2)
                        computerScore++;
                    else if(matrix[i-k][j-k]==1)
                    {
                        computerScore=0;
                        zeros=0;
                        break;
                    }
                    else
                        zeros++;
                }
                movesLeft=0;
                if(zeros>0){
                    for(int c=1;c<4;++c){
                        int column = j-c, row = i-c;
                        for(int m=row;m<=5;++m){
                            if(matrix[m][column]==0)
                                movesLeft++;
                            else if(matrix[m][column]==2);
                            else break;
                        }
                    }
                    if(movesLeft!=0) score += calculateScore(computerScore, movesLeft);
                    computerScore=1;
                    zeros = 0;
                }
            }
        }
    }
    return score;

}

int MainWindow::calculateScore(int computerScore, int movesLeft){
    int moveScore = 4 - movesLeft;
    if(computerScore==0)
        return 0;
    else if(computerScore==1)
        return 1*moveScore;
    else if(computerScore==2)
        return 10*moveScore;
    else if(computerScore==3)
        return 100*moveScore;
    else
        return 1000;
}

void MainWindow::gameLevel()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Choose level");
    msgBox.addButton("easy",QMessageBox::AcceptRole);
    msgBox.addButton("medium",QMessageBox::RejectRole);
    msgBox.addButton("hard", QMessageBox::ActionRole);


    int retVal = msgBox.exec();

    if(retVal==0){
        maxDepth = 2;
    }
    else if (retVal == 1){
        maxDepth=6;
    }
    else
        maxDepth=8;

}
