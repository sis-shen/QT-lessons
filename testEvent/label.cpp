#include "label.h"


Label::Label(QWidget* parent):QLabel(parent)
{

}

void Label::enterEvent(QEvent *event)
{
    (void)event;
    qDebug()<<"enter event";
}

void Label::leaveEvent(QEvent *event)
{
    (void)event;
    qDebug()<<"leave event";
}
