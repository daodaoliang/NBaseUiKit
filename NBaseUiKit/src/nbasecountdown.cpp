#include "nbasecountdown.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>

NBaseCountDown::NBaseCountDown(QWidget *parent, int paramCountDown, bool isfill)
    : NBaseMoveableWidget(parent),
      pointX(0),
      pointY(0),
      waveRadius(0),
      timerId(0),
      countDown(paramCountDown),
      isFill(isfill)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground);
    innerAnima = NULL;
    isFlag = true;
    coreRadius = 100;
    changeStep = paramCountDown;
    // 背景波纹默认是绿色
    backColor.setRgb(0, 245, 0);
    // 核心圆开始颜色
    coreColorBegin.setRgb(0, 245, 0);
    // 核心圆中间颜色
    coreColorMid.setRgb(0, 210, 0);
    // 核心圆结束颜色
    coreColorEnd.setRgb(0, 140, 0);
}

void NBaseCountDown::startCountDown()
{
    show();
    timerId = startTimer(1000);
}

qreal NBaseCountDown::getWaveRadius() const
{
    return waveRadius;
}

void NBaseCountDown::setWaveRadius(const qreal &value)
{
    waveRadius = value;
    emit signalWaveRadius(value);
    update();
}

void NBaseCountDown::paintEvent(QPaintEvent *event)
{
    // 波纹
    QPainter tempPainter;
    tempPainter.begin(this);
    tempPainter.setRenderHint(QPainter::Antialiasing);
    QRadialGradient wavwRg(0, 0, waveRadius-4);
    wavwRg.setColorAt(0, backColor);
    QBrush tempBrush(wavwRg);
    tempPainter.setBrush(tempBrush);
    tempPainter.setPen(Qt::NoPen);
    tempPainter.setOpacity(0.4);
    QRectF rectangle(pointX-waveRadius/2, pointY-waveRadius/2, waveRadius, waveRadius);
    tempPainter.drawEllipse(rectangle);
    tempPainter.end();

    // 圆形内核
    coreRadius = 65;
    QPainter painter(this);
    painter.translate(width() / 2, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);

    // 外边框
    QLinearGradient lg1(0, -coreRadius, 0, coreRadius);
    lg1.setColorAt(0, QColor(255, 255, 255));
    lg1.setColorAt(1, QColor(166, 166, 166));
    painter.setBrush(lg1);
    painter.drawEllipse(-coreRadius, -coreRadius, coreRadius << 1, coreRadius << 1);

    // 内边框
    coreRadius -= 13;
    QLinearGradient lg2(0, -coreRadius, 0, coreRadius);
    lg2.setColorAt(0, QColor(155, 155, 155));
    lg2.setColorAt(1, QColor(255, 255, 255));
    painter.setBrush(lg2);
    painter.drawEllipse(-coreRadius, -coreRadius, coreRadius << 1, coreRadius << 1);

    // 内部的圆
    coreRadius -= 4;
    QRadialGradient rg(0, 0, coreRadius);
    // begin
    rg.setColorAt(0, coreColorBegin);
    // mid
    rg.setColorAt(0.6, coreColorMid);
    // end
    rg.setColorAt(1, coreColorEnd);
    painter.setBrush(rg);
    painter.setOpacity(0.3);
    painter.drawEllipse(-coreRadius, -coreRadius, coreRadius << 1, coreRadius << 1);

    // 高光
    coreRadius -= 3;
    QPainterPath path;
    path.addEllipse(-coreRadius, -coreRadius - 2, coreRadius << 1, coreRadius << 1);
    QPainterPath bigEllipse;
    coreRadius *= 2;
    bigEllipse.addEllipse(-coreRadius, -coreRadius + 140, coreRadius << 1, coreRadius << 1);
    path -= bigEllipse;
    painter.drawPath(path);

    // 文字
    QPainter textPainter(this);
    textPainter.setFont(QFont("微软雅黑",30,QFont::Bold));
    QPen tempPen;
    tempPen.setColor(QColor("#625c52"));
    textPainter.setPen(tempPen);
    textPainter.translate(width() / 2, height() / 2);
    textPainter.drawText(QRectF(-50,-50,100,100),Qt::AlignCenter,QString::number(countDown));
    NBaseMoveableWidget::paintEvent(event);
}

void NBaseCountDown::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId){
        innerAnimation(isFlag);
        isFlag = !isFlag;
    }
}

void NBaseCountDown::closeEvent(QCloseEvent *event)
{
    killTimer(timerId);
    NBaseMoveableWidget::closeEvent(event);
}

void NBaseCountDown::innerAnimation(bool isPositive)
{
    pointX = width()/2;
    pointY = height()/2;
    if(!innerAnima){
        innerAnima = new QPropertyAnimation(this, "waveRadius");
    }
    innerAnima->setDuration(800);
    if(isPositive){
        innerAnima->setStartValue(0);
        if(isFill){
            innerAnima->setEndValue((width()>height()?width():height())*2);
        }else {
            innerAnima->setEndValue((width()>height()?height():width()));
        }
    } else {
        if(isFill){
            innerAnima->setStartValue((width()>height()?width():height())*2);
        } else {
            innerAnima->setStartValue((width()>height()?height():width()));
        }
        innerAnima->setEndValue(0);
    }
    innerAnima->start();
    setCountDown(countDown--);
}

int NBaseCountDown::getCountDown() const
{
    return countDown;
}

void NBaseCountDown::setCountDown(int value)
{
    countDown = value;
    // 波纹颜色改变
    int tempWavwRed = backColor.red() + 255/changeStep;
    backColor.setRed(tempWavwRed<255?tempWavwRed:255);
    int tempWaveGreen = backColor.green() - 244/changeStep;
    backColor.setGreen(tempWaveGreen<0?0:tempWaveGreen);
    // 核心圆颜色改变
    int tempRed = coreColorBegin.red() + 245/changeStep;
    coreColorBegin.setRed(tempRed<245?tempRed:245);
    int tempGreen = coreColorBegin.green() - 245/changeStep;
    coreColorBegin.setGreen(tempGreen<0?0:tempGreen);
    tempRed = coreColorMid.red() + 210/changeStep;
    coreColorMid.setRed(tempRed<210?tempRed:210);
    tempGreen = coreColorMid.green() - 210/changeStep;
    coreColorMid.setGreen(tempGreen<0?0:tempGreen);
    tempRed = coreColorEnd.red() + 140/changeStep;
    coreColorEnd.setRed(tempRed<140?tempRed:140);
    tempGreen = coreColorEnd.green() - 140/changeStep;
    coreColorEnd.setGreen(tempGreen<0?0:tempGreen);
    if(countDown-- <= 0){
        close();
    }
}
