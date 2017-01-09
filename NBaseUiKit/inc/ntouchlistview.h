#ifndef NTOUCHLISTVIEW_H
#define NTOUCHLISTVIEW_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月06日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QMouseEvent>
#include "nbasetoastr.h"
#include "nbaseuikit_global.h"

/**
 * @brief The NTouchListView class 类似触屏的滑动效果的ListView
 */
class NBASEUIKITSHARED_EXPORT NTouchListView : public QListView
{
    Q_OBJECT
public:
    explicit NTouchListView(QWidget *parent = 0);

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
