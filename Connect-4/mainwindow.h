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

public slots:
    void insertAtBoard(int);
};

#endif // MAINWINDOW_H
