#include "nbasetoastr.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>

void NBaseToastr::setShadow(QWidget *w, qreal blurRadius, qreal dx, qreal dy)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(blurRadius);
    shadow->setColor(QColor(0, 0, 0, 160));
    shadow->setOffset(dx, dy);
    w->setGraphicsEffect(shadow);
}

NBaseToastr::NBaseToastr(QWidget *parent, const QString &message, int w, int h, const QString &style)
    :QLabel(parent)
{
    setText(message);
    setFixedSize(w, h);
    setAlignment(Qt::AlignCenter);
    startx = (parent->width()-width()) / 2;
    starty = parent->height();
    endy = parent->height()*3/4;
    setStyleSheet(style);
    this->setShadow(this);
}

void NBaseToastr::toastr()
{
    QPropertyAnimation *animal= new QPropertyAnimation(this,"pos");
    animal->setDuration(500);
    animal->setStartValue(QPoint(startx,starty));
    animal->setEndValue(QPoint(startx,endy));
    animal->setEasingCurve(QEasingCurve::OutCubic);
    connect(animal, SIGNAL(finished()), this, SLOT(animationFinished()));
    this->show();
    animal->start();
}

void NBaseToastr::animationFinished()
{
    QTimer::singleShot(400, this, SLOT(delSelf()));
}

void NBaseToastr::delSelf()
{
    delete this;
}
