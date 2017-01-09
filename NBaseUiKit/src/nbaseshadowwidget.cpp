#include "nbaseshadowwidget.h"

NBaseShadowWidget::NBaseShadowWidget(NBaseMoveableWidget *parent) : NBaseMoveableWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void NBaseShadowWidget::changeEvent(QEvent *event)
{
    NBaseMoveableWidget::changeEvent(event);
}

void NBaseShadowWidget::paintEvent(QPaintEvent *e)
{
    drawShadowPlanB();
    NBaseMoveableWidget::paintEvent(e);
}

void NBaseShadowWidget::drawShadowPlanA()
{
    // blurRadius 阴影清晰度，越小越清晰
    // dx x方向阴影位置和偏移量，正值在右方，值越大偏移越大
    // dy y方向阴影位置和偏移量，正值在下方，值越大偏移越大
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 160));
    shadow->setOffset(5, 5);
    this->setGraphicsEffect(shadow);
}

void NBaseShadowWidget::drawShadowPlanB()
{
    //画阴影边框方案[B]
    QPainter painter(this);
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/img/shadow_left.png"));
    pixmaps.append(QPixmap(":/img/shadow_right.png"));
    pixmaps.append(QPixmap(":/img/shadow_top.png"));
    pixmaps.append(QPixmap(":/img/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/img/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/img/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/img/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/img/shadow_corner4.png"));
    painter.drawPixmap(0,0,20,20,pixmaps[4]);
    painter.drawPixmap(this->width() - 20,0,20,20,pixmaps[5]);
    painter.drawPixmap(0,this->height() - 20,20,20,pixmaps[6]);
    painter.drawPixmap(this->width() - 20,this->height() - 20,20,20,pixmaps[7]);
    painter.drawPixmap(0,20,20,this->height() - 40,pixmaps[0].scaled(20,this->height() - 40));
    painter.drawPixmap(this->width() - 20,20,20,this->height() - 40,pixmaps[1].scaled(20,this->height() - 40));
    painter.drawPixmap(20,0,this->width() - 40,20,pixmaps[2].scaled(this->width() - 40,20));
    painter.drawPixmap(20,this->height() - 20,this->width() - 40,20,pixmaps[3].scaled(this->width() - 40,20));
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(QRect(18,18,this->width() - 36,this->height() - 36),2.0f,2.0f);
}
