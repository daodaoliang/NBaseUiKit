#ifndef NTOUCHLISTVIEW_H
#define NTOUCHLISTVIEW_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月29日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QListWidget>
#include <QMouseEvent>
#include "nbaseuikit_global.h"

/**
 * @brief The NTouchListWidget class 类似触屏的滑动效果的ListWidget
 */
class NBASEUIKITSHARED_EXPORT NTouchListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit NTouchListWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int originPosY;
    int originPosX;
    bool isMoved;
};

#endif // NTOUCHLISTVIEW_H
