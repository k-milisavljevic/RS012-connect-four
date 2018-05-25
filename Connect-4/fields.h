#ifndef FIELDS_H
#define FIELDS_H

#include <QWidget>
#include<QMouseEvent>
#include<QDebug>
#include<QEvent>
#include<QLabel>
class fields : public QLabel
{
    Q_OBJECT
public:
    explicit fields(QWidget *parent=0);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);
    int x,y;
  //  fields();
signals:
    void Mouse_pressed();
    void Mouse_Left();
    void Mouse_Pos();
};

#endif // FIELDS_H
