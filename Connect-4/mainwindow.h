#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fields.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Mouse_current_pos();
    void Mouse_pressed();
    void Mouse_left();

private:
    Ui::MainWindow *ui;
    int player;
    bool isComputer;
    // 0 - empty field
    // 1 - red player
    // 2 - blue player
   int matrix[6][7] = {{0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                     };

public slots:
  int  restrictionMove(int,int);
    void insertAtBoard(int, int);
    bool checkForWinner(int,int,int);
    bool checkColumns(int,int);
    bool checkRows(int,int);
    bool checkDiagonal(int,int,int);
    void endGame(int);
    void newGame();
    int gameType();
    void computerPlaying(int, int);
    void checkIfEqual();
};

#endif // MAINWINDOW_H
