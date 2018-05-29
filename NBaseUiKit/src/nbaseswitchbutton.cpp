#include "nbaseswitchbutton.h"
#include <QMouseEvent>

NBaseSwitchButton::NBaseSwitchButton(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //默认OFF背景色
    mOffBgcBegin = QColor(252, 177, 170);
    mOffBgcEnd = QColor(254, 179, 172);

    //默认ON背景色
    mOnBgcBegin = QColor(144, 202, 175);
    mOnBgcEnd = QColor(146,204,177);

    //默认滑块ON背景色
    mSlideONCBegin = QColor(0, 142, 89);
    mSlideONCEnd = QColor(2, 144, 91);

    //默认滑块OFF背景色
    mSlidOFFCBegin = QColor(192,63,60);
    mSlidOFFCEnd = QColor(194,65,62);

    //默认开关状态
    mState = false;
    mMouseDown = false;
    mMouseMove = false;
    mMouseUp = true;
    resize(70,30);
}

void NBaseSwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mMouseDown = true;
        mMouseUp = false;
        firstPoint = event->pos();
    }
}

void NBaseSwitchButton::mouseMoveEvent(QMouseEvent *event)
{
    if(mMouseDown)
    {
        mMouseMove = true;
        lastPoint = event->pos(); //获取当前光标的位置
        repaint();
    }
}

void NBaseSwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(mMouseDown) {
        mMouseDown = false;
        mMouseMove = false;
        mMouseUp = true;
        if (event->pos().x() < width() / 2.0)
        {
            mState = false;
        }
        else
        {
            mState = true;
        }
        repaint();
    }
}

void NBaseSwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); //抗锯齿
    drawPressBackground(&painter);
    if(mMouseMove) {
        QRect sliderect;
        int left;
        int diff = lastPoint.x()-firstPoint.x(); //计算移动差值
        if(mState) {
            //(width() -  height() + 4 - 2) --- 表示滑块右边界值
            left = (width() -  height() + 4 - 2) + diff;
            if(left < 2) {
                sliderect.setLeft(2);
            }
            else if (left > (width() -  height() + 4 - 2)) {
                sliderect.setLeft(width() -  height() + 4 - 2);
            }
            else {
                sliderect.setLeft(width() -  height() + 4 - 2 + diff);
            }
        }
        else {
            left = diff;
            if(left < 2) {
                sliderect.setLeft(2);
            }
            else if (left > (width() -  height() + 4 - 2)) {
                sliderect.setLeft(width() -  height() + 4 - 2);
            }
            else {
                sliderect.setLeft(diff);
            }
        }
        sliderect.setTop(2);
        sliderect.setWidth(height() - 4 );
        sliderect.setHeight(height() - 4);

        painter.setPen(Qt::NoPen);
        QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
        linGrad.setColorAt(0, mSlideONCBegin);
        linGrad.setColorAt(1, mSlideONCEnd);
        linGrad.setSpread(QGradient::PadSpread);
        painter.setBrush(linGrad);

        QRect rrect = sliderect.intersected(rect());
        painter.drawEllipse(rrect);
        //画边框
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QColor(173, 173, 173, 160));
        painter.drawEllipse(rrect);
    }
    else {
        drawPressSlide(&painter);
    }
}

void NBaseSwitchButton::drawPressBackground(QPainter *painter)
{
    QPainterPath path;

    path.moveTo(height() / 2.0, 0);
    path.arcTo(QRectF(0, 0, height(), height()), 90, 180);
    path.lineTo(width() - height() / 2.0, height());
    path.arcTo(QRectF(width() - height(), 0, height(), height()), 270, 180);
    path.lineTo(height() / 2.0, 0);

    QPainterPath pathrect;
    pathrect.moveTo(0, 0);
    pathrect.lineTo(0, height());
    pathrect.lineTo(width(), height());
    pathrect.lineTo(width(), 0);
    pathrect.lineTo(0, 0);

    QPainterPath interpath = path.intersected(pathrect);
    painter->setPen(Qt::NoPen);
    QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
    linGrad.setColorAt(0, mState ? mOnBgcBegin : mOffBgcBegin);
    linGrad.setColorAt(1, mState ? mOnBgcEnd : mOffBgcEnd);
    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);
    painter->drawPath(interpath);

    //画边框
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor(173, 173, 173, 255));
    painter->drawPath(interpath);

    painter->setBrush(Qt::Dense1Pattern);
    painter->setPen(QColor(72,72,72));
    QFont tempFont = QFont("微软雅黑",10,QFont::Bold);
    painter->setFont(tempFont);
    painter->drawText((mState?width()/5*2:width()/5*3) - fontMetrics().width("开")/2,
                      height()/2 + fontMetrics().height()/2,
                      mState?"开":"关");
}

void NBaseSwitchButton::drawPressSlide(QPainter *painter)
{
    QRect sliderect;
    sliderect.setLeft(mState ? width() -  height() + 4 - 2 : 2);
    sliderect.setTop(2);
    sliderect.setWidth(height() - 4 );
    sliderect.setHeight(height() - 4);

    painter->setPen(Qt::NoPen);
    QLinearGradient linGrad(rect().topLeft(), rect().bottomLeft());
    if(mState){
        linGrad.setColorAt(0, mSlideONCBegin);
        linGrad.setColorAt(1, mSlideONCEnd);
    } else {
        linGrad.setColorAt(0, mSlidOFFCBegin);
        linGrad.setColorAt(1, mSlidOFFCEnd);
    }
    linGrad.setSpread(QGradient::PadSpread);
    painter->setBrush(linGrad);
    QRect rrect = sliderect.intersected(rect());
    painter->drawEllipse(rrect);

    //画边框
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QColor(173, 173, 173, 160));
    painter->drawEllipse(rrect);
}
