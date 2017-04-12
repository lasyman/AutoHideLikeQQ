#include "autohide.h"
#include "ui_autohide.h"
#include <QPropertyAnimation>
#include <QPoint>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

AutoHide::AutoHide(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoHide)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint|Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_NoSystemBackground, false);

    ui->groupBox->SetMainWindow(this);

    m_nDesktopWidth = 1920;

#if 1   //阴影效果
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(5);
    effect->setColor(Qt::black);
    effect->setOffset(0,0);
    setGraphicsEffect(effect);
#endif
}

AutoHide::~AutoHide()
{
    delete ui;
}

void AutoHide::leaveEvent(QEvent *event)
{
    isAutoHide();
    if(m_isAutoHide)
    {
        hideWidget();
    }
    QWidget::leaveEvent(event);
}

void AutoHide::enterEvent(QEvent *event)
{
    if(m_isAutoHide)
    {
        showWidget();
    }
    QWidget::enterEvent(event);
}

void AutoHide::moveEvent(QMoveEvent *event)
{
    if (qApp->mouseButtons() == Qt::LeftButton)
    {
        if(this->y() < 0)
        {
            m_enDriection = Up;
            move(this->x(), 0);
        }
        if(this->x() < 0)
        {
            m_enDriection = Left;
            move(0, y());
        }
        if(this->x() > m_nDesktopWidth-this->width())
        {
            m_enDriection = Right;
            move(m_nDesktopWidth-this->width(), y());
        }
    }
    QWidget::moveEvent(event);
}

void AutoHide::isAutoHide()
{
    qDebug()<<pos();
    if(m_enDriection & Up)
    {
        if(this->y() <= 0)
        {
            m_isAutoHide = true;
        }
        else
        {
            m_isAutoHide = false;
        }
    }
    else if(m_enDriection & Left)
    {
        if(this->x() <= 0)
        {
            m_isAutoHide = true;
        }
        else
        {
            m_isAutoHide = false;
        }
    }
    else if(m_enDriection & Right)
    {
        if(this->x() >= m_nDesktopWidth-this->width())
        {
            m_isAutoHide = true;
        }
        else
        {
            m_isAutoHide = false;
        }
    }
}

void AutoHide::showWidget()
{
    QPoint pos = this->pos();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(00);
    animation->setStartValue(QRect(pos, this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), 0, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(0, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - this->width(), this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}

void AutoHide::hideWidget()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(this->pos(), this->size()));

    QRect rcEnd;
    if (m_enDriection & Up)
    {
        rcEnd = QRect(this->x(), -this->height() + 2, this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Left)
    {
        rcEnd = QRect(-this->width() + 2, this->y(), this->size().width(), this->rect().height());
    }
    else if (m_enDriection & Right)
    {
        rcEnd = QRect(m_nDesktopWidth - 2, this->y(), this->size().width(), this->rect().height());
    }
    animation->setEndValue(rcEnd);
    animation->start();
}
