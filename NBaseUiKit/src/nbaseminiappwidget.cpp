#include "nbaseminiappwidget.h"

NBaseMiniAppWidget::NBaseMiniAppWidget(NBaseMoveableWidget *parent) : NBaseMoveableWidget(parent)
{
    setWindowFlags( Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool );
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::NoFocus);
}

void NBaseMiniAppWidget::setPixmap(QPixmap pixmap)
{
    m_Pixmap = pixmap;
    update();
}

void NBaseMiniAppWidget::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    NBaseMoveableWidget::enterEvent(event);
}

void NBaseMiniAppWidget::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
    NBaseMoveableWidget::leaveEvent(event);
}

void NBaseMiniAppWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
    NBaseMoveableWidget::paintEvent(event);
}

void NBaseMiniAppWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit signalMiniIconClicked();
    NBaseMoveableWidget::mouseDoubleClickEvent(event);
}
