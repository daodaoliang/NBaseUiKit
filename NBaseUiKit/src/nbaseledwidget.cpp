#include "nbaseledwidget.h"

NBaseLEDWidget::NBaseLEDWidget(QWidget *parent) : QWidget(parent)
{
    textCol = Qt::green;
    backCol = Qt::black;
    textMsg = "daodaoliang";
    numChar = textMsg.size();
    length = fontMetrics().width(textMsg) + (numChar-1)*fontInfo().pointSize()/4;
    typeEff = sliding;
    on = true;
    textOff = "";
    textOn = textMsg;
    timerVal = 300;
    idTimer = 0;
    timerState = false;
}

void NBaseLEDWidget::paintEvent(QPaintEvent *event)
{
    paintBorder();
    paintText();
    paintGrid();
    QWidget::paintEvent(event);
}

void NBaseLEDWidget::paintBorder()
{
    QPainter painter(this);
    painter.setWindow(0, 0, length, 14);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QRectF border(0, 0, length, 14);
    painter.setBrush(backCol);
    painter.drawRect(border);
}

void NBaseLEDWidget::paintText()
{
    QPainter painter(this);
    painter.setWindow(0, 0, length, 14);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF textR(1, -1, length, 14);
    painter.setPen(QPen(textCol));
    QFont font("Fixed", 10, QFont::Bold);
    QFontMetrics fm (font);
    painter.setFont(font);
    painter.drawText(textR, Qt::AlignVCenter, textMsg);
    emit timeOut();
}

void NBaseLEDWidget::paintGrid()
{
    QPainter painter(this);
    painter.setWindow(0, 0, length, 14);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(60, 60, 60), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    for (int i = 0; i <=length; i++)
    {
        painter.drawLine(1*i, 1, 1*i, 13);
    }
    for (int i = 0; i <=14; i++)
    {
        painter.drawLine(1, 1*i, length-1, 1*i);
    }
}

void NBaseLEDWidget::timerEvent(QTimerEvent *event)
{
    if (timerState == true)
    {
        if (typeEff == sliding)
        {
            int size = textMsg.size();
            QString tmp = textMsg;
            QString rest = tmp.remove(0, 1);
            QString first = textMsg.remove(1, size-1);
            textMsg = rest.append(first);
            update();
        }
        if (typeEff == intermittent)
        {
            on = !on;
            if (on)
            {
                textMsg = textOn;
                update();
            }
            if (!on)
            {
                textMsg = textOff;
                update();
            }
        }
    }
    if (timerState == false)
    {
        textMsg = textOn;
        update();
    }
    QWidget::timerEvent(event);
}

void NBaseLEDWidget::setTextColor(QColor colorTx)
{
    textCol = colorTx;
    update();
}

void NBaseLEDWidget::setBackgroundColor(QColor colorBg)
{
    backCol = colorBg;
    update();
}

void NBaseLEDWidget::setEffect(Effect effect)
{
    typeEff = effect;
    textMsg = textOn;
    update();
}

void NBaseLEDWidget::setText(QString text)
{
    textMsg = text;
    textOn = text;
    numChar = textMsg.size();
    length = fontMetrics().width(textMsg) + (numChar-1)*fontInfo().pointSize()/4;
    update();
}


void NBaseLEDWidget::setTimer(int timer)
{
    killTimer(idTimer);
    timerVal = timer;
    timerState = false;
    update();
}

void NBaseLEDWidget::startEffect(bool start)
{
    timerState = start;

    if (timerState == true)
    {
        idTimer = startTimer(timerVal);
        update();
    }
    if (timerState == false)
    {
        killTimer(idTimer);
        update();
    }
}

QSize NBaseLEDWidget::minimumSizeHint() const
{
    return QSize(length*0.3, 3);
}

QSize NBaseLEDWidget::sizeHint() const
{
    return QSize(length*3, 30);
}

NBaseLEDWidget::Effect NBaseLEDWidget::effect() const
{
    return typeEff;
}

QColor NBaseLEDWidget::colorText() const
{
    return textCol;
}

QColor NBaseLEDWidget::colorBackground() const
{
    return backCol;
}

QString NBaseLEDWidget::text() const
{
    return textOn;
}

int NBaseLEDWidget::timerInterval() const
{
    return timerVal;
}

bool NBaseLEDWidget::isStart() const
{
    return timerState;
}
