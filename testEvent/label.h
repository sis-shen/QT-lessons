#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>
#include <QDebug>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(QWidget* parent);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
};

#endif // LABEL_H
