#ifndef NBASESWITCHBUTTON_H
#define NBASESWITCHBUTTON_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月05日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QPainter>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseSwitchButton class switch button
 */
class NBASEUIKITSHARED_EXPORT NBaseSwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit NBaseSwitchButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void drawPressBackground(QPainter *painter);
    void drawPressSlide(QPainter *painter);

private:
    QColor mOffBgcBegin;
    QColor mOffBgcEnd;
    QColor mOnBgcBegin;
    QColor mOnBgcEnd;
    QColor mSlideONCBegin;
    QColor mSlideONCEnd;
    QColor mSlidOFFCBegin;
    QColor mSlidOFFCEnd;
    bool mState;
    bool mMouseDown;
    bool mMouseMove;
    bool mMouseUp;
    QPoint firstPoint;
    QPoint lastPoint;
};

#endif // NBASESWITCHBUTTON_H
