#include "ntouchlistwidget.h"
#include <qdebug.h>
#include <QScrollBar>
#include "nbasetoastr.h"

NTouchListWidget::NTouchListWidget(QWidget *parent)
{
    Q_UNUSED(parent);
    verticalScrollBar()->setVisible(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalScrollBar()->setVisible(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    isMoved = false;
}

void NTouchListWidget::mousePressEvent(QMouseEvent *event)
{
    originPosY = event->globalY();
    originPosX = event->globalX();
    QListWidget::mousePressEvent(event);
}

void NTouchListWidget::mouseMoveEvent(QMouseEvent *event)
{
    int varDiff;
    if(flow() == QListWidget::TopToBottom){
        varDiff = verticalScrollBar()->sliderPosition() - (event->globalY() - originPosY);
        verticalScrollBar()->setSliderPosition(varDiff);
    } else {
        varDiff = horizontalScrollBar()->sliderPosition() - (event->globalX() - originPosX);
        horizontalScrollBar()->setSliderPosition(varDiff);
    }
    originPosY = event->globalY();
    originPosX = event->globalX();
    isMoved = true;
    QListWidget::mouseMoveEvent(event);
}

void NTouchListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int varDiff;
    if(flow() == QListWidget::TopToBottom){
        varDiff = verticalScrollBar()->sliderPosition() - (event->globalY() - originPosY);
        verticalScrollBar()->setSliderPosition(varDiff);
    } else {
        varDiff = horizontalScrollBar()->sliderPosition() - (event->globalX() - originPosX);
        horizontalScrollBar()->setSliderPosition(varDiff);
    }
    if(isMoved){
        if(varDiff<=0){
            NBaseToastr * tempToa = new NBaseToastr(this, "已经到达顶部");
            tempToa->toastr();
        } else if(varDiff >= verticalScrollBar()->maximum()){
            NBaseToastr * tempToa = new NBaseToastr(this, "已经到达底部");
            tempToa->toastr();
        }
    }
    isMoved = false;
    originPosY = event->globalY();
    originPosX = event->globalX();
    QListWidget::mouseReleaseEvent(event);
}
