#include "nbasecircleanimationwidget.h"

NBaseCircleAnimationWidget::NBaseCircleAnimationWidget(NBaseMoveableWidget *parent) : NBaseMoveableWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
}

NBaseCircleAnimationWidget::NBaseCircleAnimationWidget(const QString &icon, const qreal &radius, NBaseMoveableWidget *parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setCircleInfo(icon, radius);
    Q_UNUSED(parent)
}

void NBaseCircleAnimationWidget::setCircleInfo(const QString &icon, const qreal &radius)
{
    m_pix.load(icon);
    m_percent = 0;
    m_radius = radius;
    int pixW = m_pix.width();
    int pixH = m_pix.height();
    m_centerPos.setX(radius);
    m_centerPos.setY(radius);
    m_originPoint.setX(radius*2);
    m_originPoint.setY(radius);
    m_point = m_originPoint;
    this->setFixedSize(pixW + radius*2, pixH + radius*2);
    this->initAnimation();
}

void NBaseCircleAnimationWidget::startAnimation()
{
    m_percentAnimation->start();
}

void NBaseCircleAnimationWidget::stopAnimation()
{
    m_percentAnimation->stop();
    m_point = m_originPoint;
    m_percent = 0;
    update();
}

void NBaseCircleAnimationWidget::setPercent(const qreal &per)
{
    m_percent = per;
    updatePos();
}

const qreal &NBaseCircleAnimationWidget::percent(){return m_percent;}

void NBaseCircleAnimationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(m_point, m_pix);
}

void NBaseCircleAnimationWidget::updatePos()
{
    m_point = mathPoint();
    update();
}

QPoint NBaseCircleAnimationWidget::mathPoint()
{
    return this->mathPoint(m_centerPos, m_percent, m_radius);
}

QPoint NBaseCircleAnimationWidget::mathPoint(const QPoint &centerPos, const qreal &percent, const qreal &radius)
{
    qreal dx = radius * qCos(percent * ( 2 * PI)) + centerPos.x();//计算x坐标
    qreal dy = radius * qSin(percent * ( 2 * PI)) + centerPos.y(); // 计算y坐标
    return QPoint(dx, dy);
}

void NBaseCircleAnimationWidget::initAnimation()
{
    m_percentAnimation = new QPropertyAnimation(this, "percent");
    m_percentAnimation->setDuration(250);
    m_percentAnimation->setStartValue(0.0);
    m_percentAnimation->setEndValue(1.0);
    m_percentAnimation->setLoopCount(-1); //无限循环，只有调用stop才会停止
}
