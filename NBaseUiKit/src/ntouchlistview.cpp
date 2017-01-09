#include "ntouchlistview.h"
#include <QScrollBar>

NTouchListView::NTouchListView(QWidget *parent)
{
    Q_UNUSED(parent);
    verticalScrollBar()->setVisible(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalScrollBar()->setVisible(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    isMoved = false;
}

void NTouchListView::mousePressEvent(QMouseEvent *event)
{
    originPosY = event->globalY();
    originPosX = event->globalX();
    QListView::mousePressEvent(event);
}

void NTouchListView::mouseMoveEvent(QMouseEvent *event)
{
    int varDiff;
    if(flow() == QListView::TopToBottom){
        varDiff = verticalScrollBar()->sliderPosition() - (event->globalY() - originPosY);
        verticalScrollBar()->setSliderPosition(varDiff);
    } else {
        varDiff = horizontalScrollBar()->sliderPosition() - (event->globalX() - originPosX);
        horizontalScrollBar()->setSliderPosition(varDiff);
    }
    originPosY = event->globalY();
    originPosX = event->globalX();
    isMoved = true;
    QListView::mouseMoveEvent(event);
}

void NTouchListView::mouseReleaseEvent(QMouseEvent *event)
{
    int varDiff;
    if(flow() == QListView::TopToBottom){
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
    QListView::mouseReleaseEvent(event);
}
