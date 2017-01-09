#ifndef NBASEMARQUEELABEL_H
#define NBASEMARQUEELABEL_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月11日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QUrl>
#include <QResizeEvent>
#include <QtConcurrent/QtConcurrentRun>
#include <QDesktopServices>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseMarqueeLabel class 跑马灯组件
 */
class NBASEUIKITSHARED_EXPORT NBaseMarqueeLabel : public QLabel
{
    Q_OBJECT
    Q_ENUMS(Direction)

public:
    /**
     * @brief The Direction enum 文字的浮动方向
     */
    enum Direction
    {
        // 从右向左
        RightToLeft = 0,
        // 从下到上
        BottomToTop = 1
    };
public:
    NBaseMarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    NBaseMarqueeLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~NBaseMarqueeLabel();
    int interval() const;
    bool isActive() const;
    Direction direction() const;
    void setAlignment(Qt::Alignment align);

signals:
    void intervalChanged(int mInterval);
    void activeChanged(bool active);
    void directionChanged(Direction direction);

public slots:
    void reset();
    void setActive(bool active);
    void setInterval(int msec);
    void start();
    void stop();
    void setDirection(Direction param_direciton);

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    int marqueeMargin;
    int timerId;
    int mInterval;
    bool active;
    bool mouseIn;
    Direction mDirection;
};
#endif // NBASEMARQUEELABEL_H
