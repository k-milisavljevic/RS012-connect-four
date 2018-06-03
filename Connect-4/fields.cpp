#include "fields.h"

fields::fields(QWidget *parent):
    QLabel(parent)
{

}
void fields::mousePressEvent(QMouseEvent *ev)
{
   emit Mouse_pressed();
}

void fields::mouseMoveEvent(QMouseEvent *ev)
{
    this->x=ev->x();
    this->y=ev->y();
    emit Mouse_Pos();
}

void fields::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}

