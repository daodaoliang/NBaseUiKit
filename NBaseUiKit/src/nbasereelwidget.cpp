#include "nbasereelwidget.h"
#include <QPainter>


NBaseReelWidget::NBaseReelWidget(QWidget *parent) : NBaseMoveableWidget(parent)
{
    oriSize = QSize(0, 0);
    connect(&animaExpan, SIGNAL(frameChanged(int)), SLOT(onExpansion()));
    animaExpan.setFrameRange(0, 100);
    animaExpan.setDuration(3000);
    bgColorbegin = QColor(255,250,250);
    bgColorEnd = QColor(209,227,219);
    bgCorner = QColor(90,76,76);
    animaExpan.setCurveShape(QTimeLine::LinearCurve);
    setIsDragAble(false);
}

void NBaseReelWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    // 画边框
    QPen p(QColor(209,227,220));
    p.setWidth(2);
    painter.setPen(p);
    // 背景渐变颜色
    QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, rect().height()));
    linearGradient.setColorAt(0, bgColorbegin);
    linearGradient.setColorAt(1, bgColorEnd);
    linearGradient.setSpread(QGradient::PadSpread);
    painter.save();
    QPainterPath path;
    path.addRoundedRect(QRect(rect().topLeft(),QPoint(rect().right(),rect().bottom()-25)),8,8);
    painter.fillPath(path,QBrush(linearGradient));
    painter.drawPath(path);
    painter.restore();
    if(bFinally) { //定格，即最终呈现的时候
        painter.save();
        //因为窗体左下角有一个弧度，还要考虑曲线外留下的空白区域，先“填补”它
        QRect r(0,height()-33,15,16);
        painter.fillRect(r,bgColorEnd);
        painter.drawLine(r.topLeft(), r.bottomLeft());
        painter.restore();
        //用贝塞尔曲线填充
        QPoint startPos(20,height()-25);
        QPoint endPos(20,startPos.y()+25);
        QPainterPath path1(startPos);
        //贝塞尔曲线的两个控制点可能没那么精确，大家可以参考贝塞尔曲线算法做到更精确的控制，我这就不赘述了
        path1.cubicTo(QPoint(0,startPos.y()), QPoint(-15,startPos.y()+8), endPos);
        //闭合曲线区域
        path1.closeSubpath();
        painter.fillPath(path1, bgCorner);
        painter.drawPath(path1);
    }
    else { //动画的时候
        painter.save();
        //同上面一样，先“填补”窗体左下角的空白区域
        /* 注意这里的椭圆高度控制为15，底部给定格的时候留下一定区域
         * 因为定格的时候“卷筒”要展开 */
        QRect r(0,height()-33,20,15);
        painter.fillRect(r,bgColorEnd);
        //画三条边框线
        painter.drawLine(r.topLeft(), r.bottomLeft());
        painter.drawLine(QPoint(20,height()-25), r.bottomRight());
        painter.drawLine(QPoint(10,height()-25), QPoint(20,height()-25));
        painter.restore();
        //用椭圆填充
        QPainterPath path1;
        path1.addEllipse(0,height()-25,20,15);
        painter.fillPath(path1, bgCorner);
        painter.drawPath(path1);
    }
    NBaseMoveableWidget::paintEvent(event);
}

void NBaseReelWidget::setOriPos(const QPoint &p)
{
    move(p);
    this->oriPos = p;
}

void NBaseReelWidget::setOriSize(const QSize &s)
{
    this->oriSize = s;
}

void NBaseReelWidget::showExpan()
{
    bFinally = false;
    resize(20,oriSize.height());
    show();
    animaExpan.stop();
    animaExpan.start();
}

void NBaseReelWidget::onExpansion()
{
    int indexFrame = animaExpan.currentFrame();
    resize(20+(oriSize.width()-20)/100.0*indexFrame, oriSize.height());
    if(indexFrame >= 99) {
        bFinally = true;
    }
}
