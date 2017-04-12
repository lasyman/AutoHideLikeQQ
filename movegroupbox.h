#ifndef MOVEGROUPBOX_H
#define MOVEGROUPBOX_H

#include <QGroupBox>
#include <QPoint>


class MoveGroupbox : public QGroupBox
{

    Q_OBJECT
public:
    MoveGroupbox(QWidget *parent = 0);
    ~MoveGroupbox();

    void SetMainWindow(QWidget *mainwindow);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QWidget *m_mainwindow;
    QPoint m_clickPos;
};

#endif // MOVEGROUPBOX_H
