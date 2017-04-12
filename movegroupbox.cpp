#include "movegroupbox.h"
#include <QMouseEvent>


MoveGroupbox::MoveGroupbox(QWidget *parent):QGroupBox(parent)
{

}

MoveGroupbox::~MoveGroupbox()
{

}

void MoveGroupbox::SetMainWindow(QWidget *mainwindow)
{
    m_mainwindow = mainwindow;
}

void MoveGroupbox::mousePressEvent(QMouseEvent *event)
{
    m_clickPos = event->globalPos() - m_mainwindow->pos();
}

void MoveGroupbox::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
        return;
    m_mainwindow->move(event->globalPos() - m_clickPos);
}
