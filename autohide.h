#ifndef AUTOHIDE_H
#define AUTOHIDE_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class AutoHide;
}

enum Direction
{
    Up = 0x0001,
    Left = 0x0010,
    Right = 0x0100
};

class AutoHide : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoHide(QWidget *parent = 0);
    ~AutoHide();

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void moveEvent(QMoveEvent *event);

private:
    void isAutoHide();
    void hideWidget();
    void showWidget();

    bool m_isAutoHide{false};

private:
    Ui::AutoHide *ui;

    Direction m_enDriection;
    int m_nDesktopWidth;
};

#endif // AUTOHIDE_H
